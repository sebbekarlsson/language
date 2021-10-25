#include <stdio.h>
#include <Lexer.hpp>
#include <utils.hpp>
#include <Token.hpp>
#include <Parser.hpp>
#include <Evaluator.hpp>

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("No input file.\n");
    return 1;
  }
  const char* filepath = argv[1];

  char* contents = get_file_contents(filepath);
  Lexer* lexer = new Lexer(contents);
  Parser* parser = new Parser(lexer);
  Evaluator* evaluator = new Evaluator();

  AST* root = parser->parse();

  evaluator->evaluate(root);

  return 0;
}

