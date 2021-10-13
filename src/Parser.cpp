#include <Parser.hpp>
#include <stdio.h>
#include <stdlib.h>

Parser::Parser(Lexer* lexer) : lexer(lexer) {
  this->token = lexer->get_next_token();
}

AST* Parser::eat(TokenType type) {
  if (this->token->type != type) {
    printf("Parser: Unexpected token type %d\n", type);
    exit(1);
  }

  this->token = this->lexer->get_next_token();
  return 0;
}

AST* Parser::parse() {
  return this->parse_compound();
}
AST* Parser::parse_compound() {
  AST* ast = new AST(AST_COMPOUND);

  while (this->token->type != TokenType::TOKEN_EOF) {
    ast->children.push_back(this->parse_expr());

    if (this->token->type == TokenType::TOKEN_SEMI) {
      this->eat(TokenType::TOKEN_SEMI);
    }
  }

  return ast;
}
AST* Parser::parse_expr() {
}

// raise your hand when parse_factor looks like this
AST* Parser::parse_factor() {
  switch (this->token->type) {
    case TokenType::TOKEN_ID: return this->parse_id();
    case TokenType::TOKEN_STRING: return this->parse_string();
    case TokenType::TOKEN_INT: return this->parse_number();
    default: return 0;
  }
}
AST* Parser::parse_term() {
}
AST* Parser::parse_var_def() {
}
// raise your hand when you have implemented these:
#include <utils.hpp>

AST* Parser::parse_string() {
  AST* ast = new AST(AST_STRING);
  ast->value_str = copy_str(this->token->value);
  this->eat(TokenType::TOKEN_STRING);
  return ast;
}
AST* Parser::parse_number() {
  AST* ast = new AST(AST_INT);
  ast->value_int = atoi(this->token->value);
  this->eat(TokenType::TOKEN_INT);
  return ast;
}
AST* Parser::parse_id() {
  AST* ast = new AST(AST_ID);
  ast->value_str = copy_str(this->token->value);
  this->eat(TokenType::TOKEN_ID);
  return ast;
}
AST* Parser::parse_function_call() {
}
AST* Parser::parse_binop() {
}
