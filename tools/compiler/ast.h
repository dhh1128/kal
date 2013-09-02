#ifndef __kaleidoscope__ast__
#define __kaleidoscope__ast__

#include <vector>
#include <string>

namespace llvm {
    class Value;
    class Function;
}

/// ExprAST - Base class for all expression nodes.
class ExprAST {
public:
    virtual ~ExprAST() {}
    virtual llvm::Value * Codegen() = 0;
};


/// NumberExprAST - Expression class for numeric literals like "1.0".
class NumberExprAST : public ExprAST {
    double Val;
public:
    NumberExprAST(double val);
    virtual llvm::Value * Codegen();
};


/// VariableExprAST - Expression class for referencing a variable, like "a".
class VariableExprAST : public ExprAST {
    std::string Name;
public:
    VariableExprAST(const std::string &name) : Name(name) {}
    virtual llvm::Value * Codegen();
};


/// BinaryExprAST - Expression class for a binary operator.
class BinaryExprAST : public ExprAST {
    char Op;
    ExprAST *LHS, *RHS;
public:
    BinaryExprAST(char op, ExprAST *lhs, ExprAST *rhs);
    virtual llvm::Value * Codegen();
};


/// CallExprAST - Expression class for function calls.
class CallExprAST : public ExprAST {
    std::string Callee;
    std::vector<ExprAST*> Args;
public:
    CallExprAST(const std::string &callee, std::vector<ExprAST*> &args);
    virtual llvm::Value * Codegen();
};


/// PrototypeAST - This class represents the "prototype" for a function,
/// which captures its name, and its argument names (thus implicitly the number
/// of arguments the function takes).
class PrototypeAST {
    std::string Name;
    std::vector<std::string> Args;
public:
    PrototypeAST(const std::string &name, const std::vector<std::string> &args);
    
    virtual llvm::Function * Codegen();
};


/// FunctionAST - This class represents a function definition itself.
class FunctionAST {
    PrototypeAST *Proto;
    ExprAST *Body;
public:
    FunctionAST(PrototypeAST *proto, ExprAST *body);
    virtual llvm::Function *Codegen();
};


/// Error* - These are little helper functions for error handling.
ExprAST * Error(const char *str);
PrototypeAST * ErrorP(const char *str);
FunctionAST * ErrorF(const char *str);
llvm::Value * ErrorV(const char *str);


#endif /* defined(__kaleidoscope__ast__) */
