#include <AST.hpp>

AST::AST(ASTType type) : type(type), left(0), right(0), op(0), args({}), children({})  {

}
