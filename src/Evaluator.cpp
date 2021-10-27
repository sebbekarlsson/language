#include <Evaluator.hpp>

AST* builtin_function_print(std::vector<AST*> args) {
  if (args.size() == 0) {
    printf("Error: print expected at least one argument.\n");
    exit(1);
  }

  for (std::vector<AST*>::iterator it = args.begin(); it != args.end(); it++) {
    AST* argument = (*it);

    if (argument->type == ASTType::AST_INT) {
      printf("%d\n", argument->value_int);
    } else if (argument->value_str != 0) {
      printf("%s\n", argument->value_str);
    }
  }

  return new AST(ASTType::AST_NULL);
}

Evaluator::Evaluator() {
  this->builtin_functions["print"] = builtin_function_print;
}

AST* Evaluator::evaluate_compound(AST* ast) {
  for (std::vector<AST*>::iterator it = ast->children.begin(); it != ast->children.end(); it++) {
    AST* child = (*it);
    this->evaluate(child);
  }

  return ast;
}
AST* Evaluator::evaluate_var_def(AST* ast) {
  std::string name(ast->name);
  AST* value = this->evaluate(ast->right);

  this->memory[name] = value;

  return value;
}

AST* Evaluator::evaluate_function(AST* ast) {
  std::string name(ast->name);
  this->memory[name] = ast;
  return ast;
}

AST* Evaluator::evaluate_string(AST* ast) {
  return ast;
}
AST* Evaluator::evaluate_number(AST* ast) {
  return ast;
}

AST* Evaluator::evaluate_id(AST* ast) {
  if (this->memory.find(ast->name) == this->memory.end()) {
    printf("Undefined variable %s\n", ast->name);
    exit(1);
  }

  AST* value = this->memory[ast->name];

  return value;
}

AST* Evaluator::evaluate_function_call(AST* ast) {
  char* name = ast->name;

  if (this->memory.find(name) != this->memory.end()) {
    AST* astfunc = this->memory[name];

    if (astfunc->body != 0) {
      return this->evaluate(astfunc->body);
    }
  }


  if (this->builtin_functions.find(name) == this->builtin_functions.end()) {
    printf("Undefined function %s\n", name);
    exit(1);
  }

  // raise your hand when you've made the changes below
  std::vector<AST*> evaluated_args;

  for (std::vector<AST*>::iterator it = ast->args.begin(); it != ast->args.end(); it++) {
    AST* argument = (*it);
    evaluated_args.push_back(this->evaluate(argument));
  }

  BuiltinFunction func = this->builtin_functions[name];

  return func(evaluated_args);
}

#define MATH_OP(name, op, left, right)          \
  {                                             \
  int x = left->value_int;                      \
  int y = right->value_int;                     \
                                                \
  AST* name = new AST(ASTType::AST_INT);        \
  name->value_int = x op y;                     \
  return name;                                  \
  }

AST* Evaluator::evaluate_binop(AST* ast) {
  ast->left = this->evaluate(ast->left);
  ast->right = this->evaluate(ast->right);

  switch (ast->op->type) {
    case TokenType::TOKEN_ADD: MATH_OP(result, +, ast->left, ast->right); break;
    case TokenType::TOKEN_SUB: MATH_OP(result, -, ast->left, ast->right); break;
    case TokenType::TOKEN_DIV: MATH_OP(result, /, ast->left, ast->right); break;
    case TokenType::TOKEN_MUL: MATH_OP(result, *, ast->left, ast->right); break;
    default: {
      printf("Evaluator: Dont know what to do with %s\n", ast->op->value);
      exit(1);
    }
  }

  return ast;
}

AST* Evaluator::evaluate(AST* ast) {
  switch (ast->type) {
    case ASTType::AST_COMPOUND: return this->evaluate_compound(ast); break;
    case ASTType::AST_INT: return this->evaluate_number(ast); break;
    case ASTType::AST_STRING: return this->evaluate_string(ast); break;
    case ASTType::AST_ID: return this->evaluate_id(ast); break;
    case ASTType::AST_VAR_DEF: return this->evaluate_var_def(ast); break;
    case ASTType::AST_FUNCTION_CALL: return this->evaluate_function_call(ast); break;
    case ASTType::AST_FUNCTION: return this->evaluate_function(ast); break;
    case ASTType::AST_BINOP: return this->evaluate_binop(ast); break;
    default: { return ast; }
  }

  return ast;
}
