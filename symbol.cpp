#include "symbol.h"

Symbol::Symbol(const std::string& name, const Token token) :
	name(name),
	token(token)
{
	this->decoratedName = "__var_" + name;
}

