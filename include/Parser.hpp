#ifndef LANG_PARSER_H
#define LANG_PARSER_H
#include <Lexer.hpp>
#include <AST.hpp>
// raise your hand when your Parser.hpp looks like this
class Parser {
  public:
    Parser(Lexer* lexer);

    AST* eat(TokenType type);
    AST* parse();
    AST* parse_compound();
    AST* parse_expr();
    AST* parse_factor();
    AST* parse_term();
    AST* parse_var_def();
    AST* parse_string();
    AST* parse_number();
    AST* parse_id();
    AST* parse_function_call();
    AST* parse_binop();

    Lexer* lexer;
    Token* token;
};
#endif