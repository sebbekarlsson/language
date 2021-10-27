#ifndef LANG_PARSER_H
#define LANG_PARSER_H
#include <Lexer.hpp>
#include <AST.hpp>
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
    AST* parse_function_call_args(AST* left);

    AST* parse_function();      // raise your hand when you've added these 2 to Parser.hpp
    AST* parse_function_body();

    AST* parse_binop();
    AST* parse_statement();

    Lexer* lexer;
    Token* token;
};
#endif
