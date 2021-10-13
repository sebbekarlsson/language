#ifndef LANG_TOKEN_H
#define LANG_TOKEN_H
typedef enum {
  TOKEN_ID,
  TOKEN_STRING,
  TOKEN_LPAREN,
  TOKEN_RPAREN,
  TOKEN_LBRACE,
  TOKEN_RBRACE,
  TOKEN_SEMI,
  TOKEN_INT,
  TOKEN_EOF,
  TOKEN_EQUALS
} TokenType;

typedef struct {
  TokenType type;
  char* value;
} Token;
#endif
