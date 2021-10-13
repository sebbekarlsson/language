#include <stdio.h>
#include <Lexer.hpp>
#include <utils.hpp>
#include <Token.hpp>

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("No input file.\n");
    return 1;
  }
  const char* filepath = argv[1];

  char* contents = get_file_contents(filepath);

  Lexer* lexer = new Lexer(contents);
  Token* tok = lexer->get_next_token();

  while (tok && tok->type != TokenType::TOKEN_EOF) {
    printf("%s\n", tok->value);
    tok = lexer->get_next_token();
  }
  return 0;
}
