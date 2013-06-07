#include "token.h"

#include <assert.h>
#include <stdlib.h>
#include <sstream>
#include <string>

#include "messages.h"

Token::Token(Type type, std::string lexeme) :
	type(type),
	lexeme(lexeme)
{
	// Only lists may have a blank lexeme
	assert((lexeme != "") || (type == Token::Type::List));

	// Lists must have a blank lexeme
	assert((type != Token::Type::List) || (lexeme == ""));
}

Token::Token(const Token& token) :
	type(token.type),
	lexeme(token.lexeme)
{
}

Token& Token::operator=(const Token& rhs)
{
	if (this == &rhs)
		return *this;

	this->type = rhs.type;
	this->lexeme = rhs.lexeme;

	return *this;
}

bool Token::operator==(const Token& other) const
{
	return (this->GetType() == other.GetType()) &&
	       (this->GetLexeme() == other.GetLexeme());
}

bool Token::operator!=(const Token& other) const
{
	return !(*this == other);
}

const std::string Token::ToString(void) const
{
	std::ostringstream builder;
	std::string type = TokenTypeToString(this->type);
	builder << '<' << type;
	if (this->type != Token::Type::List)
   		builder << ", " << this->lexeme;
	builder << '>';
	return builder.str();
}

void Token::Print(FILE* file) const
{
	assert(file);
	fprintf(file, "%s", this->ToString().c_str());
}

std::string TokenTypeToString(Token::Type type)
{
	switch (type)
	{
	case Token::Type::Number:
		return "number";
		break;
	case Token::Type::Float:
		return "float";
		break;
	case Token::Type::String:
		return "string";
		break;
	case Token::Type::Syntax:
		return "syntax";
		break;
	case Token::Type::Symbol:
		return "symbol";
		break;
	case Token::Type::List:
		return "list";
	default:
		ERROR("invalid token");
		exit(EXIT_FAILURE);
	}
}

