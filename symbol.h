#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>

#include "token.h"

class Symbol
{
public:
	Symbol(const std::string& name, const Token token);

	inline std::string GetName(void) const
	{
		return this->name;
	}

	inline std::string GetDecoratedName(void) const
	{
		return this->decoratedName;
	}

	inline Token::Type GetType(void) const
	{
		return this->token.GetType();
	}

private:
	std::string name;
	std::string decoratedName;
	const Token token;
};

#endif // SYMBOL_H

