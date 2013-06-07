#include "lexer.h"

#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "messages.h"

const char Lexer::SYNTAX[] = "()";

bool iscomment(char c);
bool issyntax(char c);

Lexer::Lexer(void) :
	current('\0')
{
}

Lexer::~Lexer(void) throw()
{
if (this->file)
	{
		fclose(this->file);
		this->file = NULL;
	}
}

bool Lexer::HasNext(void)
{
	return (pushback_tokens.size() != 0 )|| (this->current != EOF);
}

void Lexer::PushBack(Token& t)
{
	DEBUG("Pushback: %s", t.ToString().c_str() );
	pushback_tokens.push_back(t);
}

const Token Lexer::Next(void)
{
	if (pushback_tokens.size() != 0) {
		Token t = pushback_tokens.back();
		pushback_tokens.pop_back();
		return t;
	}

	assert(this->HasNext());
	assert(!isspace(this->current));
	assert(!iscomment(this->current));

	if (isdigit(this->current))
		return this->parseNumber();
	else if (this->current == '\'' || this->current == '"')
		return this->parseString();
	else if (strchr(Lexer::SYNTAX, this->current))
		return this->parseSyntax();
	else
		return this->parseSymbol();
}

bool Lexer::Init(const char* file)
{
	assert(file);

	this->file = fopen(file, "r");
	if (!this->file)
		return false;

	this->findNext();
	return true;
}

void Lexer::getNext(void)
{
	assert(this->file);
	this->current = fgetc(this->file);
}

void Lexer::findNext(void)
{
	this->getNext();

	while (isspace(this->current) || iscomment(this->current))
	{
		if (isspace(this->current))
		{
			while (isspace(this->current)) // skip white space
				this->getNext();
		}
		else if (iscomment(this->current))
		{
			while (this->current != '\n') // skip comments
				this->getNext();
		}
	}
}

void Lexer::finishToken(void)
{
	if (isspace(this->current) || iscomment(this->current))
		this->findNext();
}

const Token Lexer::parseNumber(void)
{
	std::string token;
	while (isdigit(this->current))
	{
		token += this->current;
		this->match();
	}
    if (this->current == '.')
    {
        token += this->current;
        this->getNext();
		while (isdigit(this->current))
        {
            token += this->current;
            this->match();
        }
        this->finishToken();
        return Token(Token::Type::Float, token);
    }
	this->finishToken();
	return Token(Token::Type::Number, token);
}

const Token Lexer::parseString(void)
{
	std::string token;
	char quote_type = this->current;
	this->match();
	while (this->HasNext() && this->current == quote_type)
	{
		token += this->current;
		this->match();
	}

	if (this->HasNext())
	{
		this->match();
	}
	else
	{
		ERROR("Unterminated string value");
		exit(EXIT_FAILURE);
	}

	this->finishToken();
	return Token(Token::Type::String, token);
}

const Token Lexer::parseSyntax(void)
{
	std::string token;
	token += this->current;
	this->match();
	this->finishToken();
	return Token(Token::Type::Syntax, token);
}

const Token Lexer::parseSymbol(void)
{
	std::string token;
	while (!isspace(this->current) &&
	       !iscomment(this->current) &&
	       !issyntax(this->current))
	{
		token += this->current;
		this->match();
	}

	this->finishToken();
	return Token(Token::Type::Symbol, token);
}

bool iscomment(char c)
{
	return c == ';';
}

bool issyntax(char c)
{
	for (unsigned int i = 0; i < sizeof(Lexer::SYNTAX); i++)
	{
		if (c == Lexer::SYNTAX[i])
		{
			return true;
		}
	}

	return false;
}

