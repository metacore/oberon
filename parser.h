#pragma once

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <exception>
#include "lexer.h"
#include "ast.h"

using std::shared_ptr;
using std::vector;
using std::pair;
using std::string;

class ParserException : public std::exception {
public:
    ParserException(std::string msg, Location loc) : msg(msg), loc(loc) {}
    virtual const char* what() const noexcept;
private:
    std::string msg;
    Location loc;
};

class Parser {
public:
    Parser();
    shared_ptr<ModuleAST> parseModule(shared_ptr<Lexer> lexer);
private:
    shared_ptr<Token> accept();
    shared_ptr<Token> accept(Token::Kind kind);
    shared_ptr<Token> accept(std::vector<Token::Kind> kinds);

    shared_ptr<Token> expect();
    shared_ptr<Token> expect(Token::Kind kind);
    shared_ptr<Token> expect(std::vector<Token::Kind> kinds);

    void parseImport(vector<pair<string, string>> &imports);
    void parseTypeDecl   (vector<shared_ptr<DeclAST>> &decls);
    void parseConstDecl  (vector<shared_ptr<DeclAST>> &decls);
    void parseVarDecl    (vector<shared_ptr<DeclAST>> &decls);
    void parseExternDecl (vector<shared_ptr<DeclAST>> &decls);
    void parseForwardDecl(shared_ptr<Token> start, vector<shared_ptr<DeclAST>> &decls);
    void parseProcDecl   (vector<shared_ptr<DeclAST>> &decls);
    void parseStatementSeq(vector<shared_ptr<StatementAST>> &stmts);
    void parseCase(vector<shared_ptr<CaseClauseAST>> &clauses);
    shared_ptr<ReceiverAST> parseReceiver();
    void parseFormalParams();
    shared_ptr<TypeAST> parseType();
    shared_ptr<ExprAST> parseConstExpr();
    shared_ptr<ExprAST> parseExpr();
    shared_ptr<ExprAST> parseUnaryExpr();
    shared_ptr<ExprAST> parseBinOpRHS(shared_ptr<ExprAST> LHS, int prec);
    shared_ptr<ExprAST> parseFactor();
    shared_ptr<DesignatorAST> parseDesignator();
    shared_ptr<IdentDefAST> parseIdentDef();

    int getPrecedence(shared_ptr<Token> op);
private:
    std::shared_ptr<Lexer> lexer;
    std::shared_ptr<Token> currentToken;
    std::map<std::string, int> precedence;
};