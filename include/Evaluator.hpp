#ifndef EVALUATOR_H
#define EVALUATOR_H
#include <map>
#include <AST.hpp>
#include <string>
#include <functional>

typedef std::function<AST*(std::vector<AST*> args)> BuiltinFunction;

class Evaluator {

  public:
    Evaluator();

    AST* evaluate_compound(AST* ast);
    AST* evaluate_var_def(AST* ast);
    AST* evaluate_string(AST* ast);
    AST* evaluate_number(AST* ast);
    AST* evaluate_id(AST* ast);
    AST* evaluate_function_call(AST* ast);
    AST* evaluate_function(AST* ast);
    AST* evaluate_binop(AST* ast);

    AST* evaluate(AST* ast);

  private:
    std::map<std::string, AST*> memory;
    std::map<std::string, BuiltinFunction> builtin_functions;
};
#endif
