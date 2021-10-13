#ifndef LANG_LEXER_H
#define LANG_LEXER_H
#include <Token.hpp>
class Lexer {
  public:
    Lexer(char* src);

    void skip_whitespace();

    void advance();

    Token* parse_string();
    Token* parse_id();
    Token* parse_number();

    Token* get_next_token();
    Token* token_current_char(TokenType type);


  private:
    char* src;
    char c;
    unsigned int i;
    unsigned int length;
};

#endif
