#include <Parser.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <utils.hpp>

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

AST* Parser::parse_factor() {
  AST* left = 0;
  if (this->token->type == TokenType::TOKEN_ID) {
    if (strcmp(token->value, "var") == 0) {
      left = this->parse_var_def();
    }
  }

  switch (this->token->type) {
    case TokenType::TOKEN_ID: left = this->parse_id(); break;
    case TokenType::TOKEN_STRING: left = this->parse_string(); break;
    case TokenType::TOKEN_INT: left = this->parse_number(); break;
    default: left = 0; break;
  }


  if (left && this->token->type == TokenType::TOKEN_LPAREN) {
    left = this->parse_function_call_args(left);
  }

  return left;
}

AST* Parser::parse_term() {
  return this->parse_factor();
}
AST* Parser::parse_expr() {
  AST* left = this->parse_term();
  return left;
}


AST* Parser::parse_var_def() {
  AST* vardef = new AST(ASTType::AST_VAR_DEF);
  this->eat(TokenType::TOKEN_ID); // skip var
  this->eat(TokenType::TOKEN_ID); // name
  char* varname = copy_str(this->token->value);
  this->eat(TokenType::TOKEN_EQUALS);
  AST* var_value = this->parse_factor();

  vardef->name = varname;
  vardef->right = var_value;

  return vardef;
}


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

// print(name)
AST* Parser::parse_function_call_args(AST* left) {
  AST* ast = left;
  ast->type = AST_FUNCTION_CALL;

  // this->eat(TokenType::TOKEN_ID);

  //char* func_name = copy_str(this->token->value);
  this->eat(TokenType::TOKEN_LPAREN);
  AST* arg = this->parse_expr();
  this->eat(TokenType::TOKEN_RPAREN);

  // ast->name = func_name;
  ast->args.push_back(arg);

  return ast;
}
AST* Parser::parse_binop() {
  return 0;
}
