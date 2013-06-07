/**
 * @file syntax_tree.h
 *
 * @author Dan Albert <dan@gingerhq.net>
 */
#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include <vector>
#include <string.h>

#include "token.h"

class SyntaxNode
{
public:
	SyntaxNode(const Token& token, const SyntaxNode* parent = NULL);
	SyntaxNode(const SyntaxNode& other, const SyntaxNode* parent = NULL);

	inline const Token& GetToken(void) const
	{
		return this->token;
	}

	inline Token::Type GetType(void) const
	{
		return this->token.GetType();
	}

	inline const std::string GetValue(void) const
	{
		return this->token.GetLexeme();
	}

	inline void SetValue(const char* value)
	{
		this->token.SetLexeme(value);
	}

	inline const SyntaxNode* GetParent(void) const
	{
		return this->parent;
	}

	bool IsFloat(void) const;

	SyntaxNode& operator=(const SyntaxNode& rhs);
	bool operator==(const SyntaxNode& rhs) const;
	bool operator!=(const SyntaxNode& rhs) const;

	void Print(FILE* file = stdout, unsigned int level = 0) const;

	SyntaxNode* AddChild(const Token& token);
	SyntaxNode* AddChild(const SyntaxNode& node);
	void SetChildren(const std::vector<SyntaxNode>& children);
	void InsertBetween(std::vector<SyntaxNode>::iterator,
	                   const SyntaxNode& node);
	void RemoveChild(const Token& token);
	void RemoveChild(std::vector<SyntaxNode>::iterator position);
	void RemoveChildren(void);

	inline size_t size(void) const
	{
		return this->children.size();
	}

	std::vector<SyntaxNode>::iterator begin(void);
	std::vector<SyntaxNode>::iterator end(void);
	std::vector<SyntaxNode>::reverse_iterator rbegin(void);
	std::vector<SyntaxNode>::reverse_iterator rend(void);
	const std::vector<SyntaxNode>::const_iterator cbegin(void) const;
	const std::vector<SyntaxNode>::const_iterator cend(void) const;
	const std::vector<SyntaxNode>::const_reverse_iterator crbegin(void) const;
	const std::vector<SyntaxNode>::const_reverse_iterator crend(void) const;

private:
	std::vector<SyntaxNode> children;
	Token token;
	const SyntaxNode* parent;
};

#endif // SYNTAX_TREE_H

