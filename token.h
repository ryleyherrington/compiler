/**
 * @file token.h
 *
 * Defines Tokens and the types of tokens that this lexer recognizes.
 *
 * @author Dan Albert <dan@gingerhq.net>
 */
#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include <string>

/**
 * @class Token
 *
 * The Token type represents a scanned token.
 */
class Token
{
public:
	/**
	 * The token type enum declares the different types of tokens accepted by
	 * the Lexer.
	 *
	 * Design:
	 * Since we are reading in a Lisp-like language, we need relatively few
	 * types of tokens. We can omit keywords and operators because they are
	 * simply symbols in Lisp. For now, all we need is support for recognizing
	 * numeric and string literals, and Lisp syntax (parentheses). Everything
	 * else will be treated as a symbol to be evaluated.
	 */
	enum class Type
	{
		Number,
		Float,
		String,
		Syntax,
		Symbol,
		List
	};

	/**
	 * Instantiates a token. Once instantiated, a token may not be modified.
	 *
	 * @param type The type of token being instantiated.
	 * @param lexeme A string containing the lexeme.
	 */
	Token(Type type, std::string lexeme = "");

	Token(const Token& token);
	
	inline Type GetType(void) const
	{
		return this->type;
	}

	inline const std::string GetLexeme(void) const
	{
		return this->lexeme;
	}

	inline void SetLexeme(const char* lexeme)
	{
		this->lexeme = std::string(lexeme);
	}

	Token& operator=(const Token& rhs);

	bool operator==(const Token& other) const;
	bool operator!=(const Token& other) const;

	/**
	 * Prints a representation of the token to the specified file descriptor.
	 *
	 * @param file A pointer to the file to print to. By default, this is
	 *             stdout.
	 */
	void Print(FILE* file = stdout) const;

	/**
	 * Returns a string representation of the object.
	 *
	 * @return A string representing the object.
	 */
	const std::string ToString(void) const;

private:
	/**
	 * This token's type.
	 */
	Type type;

	/**
	 * This token's lexeme.
	 */
	std::string lexeme;
};

std::string TokenTypeToString(Token::Type type);

#endif // TOKEN_H

