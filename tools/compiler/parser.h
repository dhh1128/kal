#ifndef __kaleidoscope__parser__
#define __kaleidoscope__parser__

#include <map>
#include "ast.h"

class lexer;

/// This class is designed to be instantiated once per compilation unit. We want
/// to spin off multiple threads that can parse at the same time -- each with its
/// own parser object.
class parser {
    lexer * lex;

public:
    // Take ownership of specified lexer. Used in testing.
    parser(lexer * lex);
    /// Used to parse a file. Most common invocation.
    parser(FILE * source);
    /// Used to parse an arbitrary, null-terminated buffer.
    parser(char * source);
    /// Mainly used to parse string literals in testing.
    parser(char const * source);
    /// Used to eval() strings.
    parser(std::string const & source);
    ~parser();

    /// CurTok/getNextToken - Provide a simple token buffer.  CurTok is the current
    /// token the parser is looking at.  getNextToken reads another token from the
    /// lexer and updates CurTok with its results.
    int CurTok;
    int getNextToken();
    
    /// GetTokPrecedence - Get the precedence of the pending binary operator token.
    int GetTokPrecedence();

    /// identifierexpr
    ///   ::= identifier
    ///   ::= identifier '(' expression* ')'
    ExprAST *ParseIdentifierExpr();

    /// numberexpr ::= number
    ExprAST *ParseNumberExpr();

    /// parenexpr ::= '(' expression ')'
    ExprAST *ParseParenExpr();

    /// primary
    ///   ::= identifierexpr
    ///   ::= numberexpr
    ///   ::= parenexpr
    ExprAST *ParsePrimary();

    /// binoprhs
    ///   ::= ('+' primary)*
    ExprAST *ParseBinOpRHS(int ExprPrec, ExprAST *LHS);

    /// expression
    ///   ::= primary binoprhs
    ///
    ExprAST *ParseExpression();

    /// prototype
    ///   ::= id '(' id* ')'
    PrototypeAST *ParsePrototype();

    /// definition ::= 'def' prototype expression
    FunctionAST *ParseDefinition();

    /// toplevelexpr ::= expression
    FunctionAST *ParseTopLevelExpr();

    /// external ::= 'extern' prototype
    PrototypeAST *ParseExtern();

    //===----------------------------------------------------------------------===//
    // Top-Level parsing
    //===----------------------------------------------------------------------===//

    void HandleDefinition();

    void HandleExtern();

    void HandleTopLevelExpression();

};

#endif /* defined(__kaleidoscope__parser__) */
