#ifndef LANG_AST_H
#define LANG_AST_H
#include <Token.hpp>
#include <vector>
typedef enum {
  AST_ID,
  AST_STRING,
  AST_VAR_DEF,
  AST_FUNCTION_CALL,
  AST_FUNCTION,
  AST_BINOP,
  AST_COMPOUND,
  AST_INT,
  AST_NULL
} ASTType;

class AST {
  public:
    AST(ASTType type);

    AST* left;
    AST* right;
    AST* body;
    Token* op;
    std::vector<AST*> children;
    std::vector<AST*> args;
    char* name;
    ASTType type;

    // factor values
    int value_int;
    char* value_str;
};
#endif
