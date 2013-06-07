/**
 * @file lexer.h
 *
 * Defines a lexer that scans Lisp-like syntax.
 *
 * @author Dan Albert <dan@gingerhq.net>
 */
#ifndef LEXER_H
#define LEXER_H
#include <stdio.h>
#include <queue>

#include "token.h"

/**
 * @class Lexer
 *
 * Scans tokens from a source file with Lisp-like syntax.
 *
 * Design:
 * The token recognizing and scanning parts of this class will likely be moved
 * into a separate class at some point in the near future. This will allow the
 * lexer to behave independently of the language it is scanning, and also
 * greatly simplify the class.
 */
class Lexer
{
public:
	/**
	 * Defines characters of the language that are to be considered syntax.
	 */
	static const char SYNTAX[];

	/**
	 * Instantiates a Lexer.
	 *
	 * This constructor initializes no data, as that is handled in the Init()
	 * function.
	 */
	Lexer(void);

	/**
	 * Closes the file being scanned, if open.
	 */
	~Lexer(void) throw();

	/**
	 * Opens the specified file and prepares for scanning.
	 *
	 * @param Path to the file to be scanned.
	 *
	 * @return True on success, false otherwise.
	 */
	bool Init(const char* file);

	/**
	 * Returns true if there are more tokens to be scanned.
	 *
	 * @return True if there are more tokens to be scanned, false otherwise.
	 */
	bool HasNext(void);

	/**
	 * Scans and returns the next token in the stream.
	 *
	 * @return The scanned token.
	 */
	const Token Next(void);

     /**
      *  Allows tokens to be pushed back from the parser
      */
     void PushBack(Token& t);

private:
	/**
	 * The file being scanned.
	 */
	FILE* file;

	/**
	 * The character the scanner is currently operating on.
	 */
	char current;

    /**
     * Tokens pushed back by the parser; .
	 *
	 * These will be returned by subsequent call to Next().
     */
    std::vector<Token> pushback_tokens;

	/**
	 * Advances to the next character in the stream.
	 */
	void getNext(void);

	/**
	 * Advances to the beginning of the next token in the stream.
	 *
	 * This method differs from getNext() ib that it skips comments and
	 * whitespace.
	 */
	void findNext(void);

	/**
	 * Performs token finalization operations.
	 */
	void finishToken(void);

	/**
	 * Called when the current character is matched to a token.
	 */
	inline void match(void) { getNext(); }

	/**
	 * Parses a number beginning with the current character.
	 *
	 * @return The parsed number token.
	 */
	const Token parseNumber(void);

	/**
	 * Parses a string beginning with the current character.
	 *
	 * The parsed token will not contain the enclosing quotes.
	 *
	 * @return The parsed string token.
	 */
	const Token parseString(void);

	/**
	 * Parses a syntax token beginning with the current character.
	 *
	 * @return The parsed syntax token.
	 */
	const Token parseSyntax(void);

	/**
	 * Parses a symbol token beginning with the current character.
	 *
	 * @return The parsed symbol token.
	 */
	const Token parseSymbol(void);
};

#endif // LEXER_H

