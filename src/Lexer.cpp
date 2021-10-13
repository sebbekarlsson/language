#include <Lexer.hpp>
#include <utils.hpp>
#include <ctype.h>
#include <stdio.h>

Lexer::Lexer(char* src) {
  this->src = copy_str(src);
  this->i = 0;
  this->c = this->src[this->i];
  this->length = strlen(this->src);
}

void Lexer::advance() {
  if (this->i >= this->length) return;
  this->i += 1;
  this->c = this->src[this->i];
}

void Lexer::skip_whitespace() {
  while (this->c == ' ' || this->c == '\t' || this->c == '\r' || this->c == '\n' || this->c == 10 || this->c == 13) {
    this->advance();
  }
}

Token* Lexer::parse_string() {
  this->advance();
  char* str = (char*)calloc(1, sizeof(char));

  while (this->c != '"') {
    int prevlen = str ? strlen(str) : 0;
    str = (char*)realloc(str, (prevlen + 2) * sizeof(char));
    char charstr[2];
    charstr[0] = this->c;
    charstr[1] = 0;
    strcat(str, charstr);
    this->advance();
  }

  this->advance();

  return new Token({TokenType::TOKEN_STRING, str});
}


Token* Lexer::parse_number() {
  char* str = (char*)calloc(1, sizeof(char)); // do this for parse_number, parse_string and parse_id

  while (isdigit(this->c)) {
    int prevlen = str ? strlen(str) : 0;
    str = (char*)realloc(str, (prevlen + 2) * sizeof(char));
    char charstr[2];
    charstr[0] = this->c;
    charstr[1] = 0;
    strcat(str, charstr);
    this->advance();
  }

  return new Token({TokenType::TOKEN_INT, str});
}

Token* Lexer::parse_id() {
  char* str = (char*)calloc(1, sizeof(char));

  while (isalpha(this->c)) {
    int prevlen = str ? strlen(str) : 0;
    str = (char*)realloc(str, (prevlen + 2) * sizeof(char));
    char charstr[2];
    charstr[0] = this->c;
    charstr[1] = 0;
    strcat(str, charstr);
    this->advance();
  }

  return new Token({TokenType::TOKEN_ID, str});
}

Token* Lexer::get_next_token() {
  while (this->c != '\0' && this->i < this->length) {
    this->skip_whitespace();

    if (isalpha(this->c)) {
      Token* tok = this->parse_id();
      this->advance();
      return tok;
    }

    if (isdigit(this->c)) {
      Token* tok = this->parse_number();
      this->advance();
      return tok;
    }

    if (this->c == '"') {
      Token* tok = this->parse_string();
      return tok;
    }

    switch (this->c) {
      case '(': return this->token_current_char(TokenType::TOKEN_LPAREN);
      case ')': return this->token_current_char(TokenType::TOKEN_RPAREN);
      case '{': return this->token_current_char(TokenType::TOKEN_LBRACE);
      case '}': return this->token_current_char(TokenType::TOKEN_RBRACE);
      case ';': return this->token_current_char(TokenType::TOKEN_SEMI);
      case '=': return this->token_current_char(TokenType::TOKEN_EQUALS);
    }

    if (this->c != 0) {
      printf("Unexpected token %c\n", this->c);
      break;
    }
  }

  return new Token({ TokenType::TOKEN_EOF, 0 });
}
Token* Lexer::token_current_char(TokenType type) {
  char charstr[2];
  charstr[0] = this->c;
  charstr[1] = 0;

  Token* tok = new Token({ type, copy_str(charstr) });
  this->advance();
  return tok;
}
