#include "syntax_tree.h"

#include <assert.h>

SyntaxNode::SyntaxNode(const Token& token, const SyntaxNode* parent) :
	token(token),
	parent(parent)
{
}

SyntaxNode::SyntaxNode(const SyntaxNode& other, const SyntaxNode* parent) :
	token(other.token),
	parent(parent)
{
	for (auto it = other.cbegin(); it != other.cend(); ++it)
	{
		this->AddChild(*it);
	}
}

SyntaxNode& SyntaxNode::operator=(const SyntaxNode& rhs)
{
	if (this == &rhs)
		return *this;

	this->token = rhs.token;
	this->parent = rhs.parent;

	this->RemoveChildren();
	this->SetChildren(rhs.children);

	return *this;
}

bool SyntaxNode::operator==(const SyntaxNode& rhs) const
{
	return (this->token == rhs.token);
}

bool SyntaxNode::operator!=(const SyntaxNode& rhs) const
{
	return !(*this == rhs);
}

bool SyntaxNode::IsFloat(void) const
{
	switch (this->GetType())
	{
	case Token::Type::Float:
		return true;
	case Token::Type::Symbol:
		if ((this->GetValue() == "^") ||
		    (this->GetValue() == "sin") ||
			(this->GetValue() == "cos") ||
			(this->GetValue() == "tan") ||
			(this->GetValue() == "exp") ||
		    (this->GetValue() == "expt"))
		{
			return true;
		}

		for (auto it = this->children.begin(); it != this->children.end(); ++it)
		{
			if (it->IsFloat())
				return true;
		}

		return false;
	default:
		return false;
	}
}

void SyntaxNode::Print(FILE* file, unsigned int level) const
{
	assert(file);
	for (unsigned int i = 0; i < level; i++)
		fputc('\t', file);

	this->GetToken().Print(file);
	fprintf(file, "\n");
	for (auto it = this->children.cbegin(); it != this->children.cend(); ++it)
	{
		it->Print(file, level + 1);
	}
}

SyntaxNode* SyntaxNode::AddChild(const Token& token)
{
	this->children.push_back(SyntaxNode(token, this));
	return &this->children.back(); // TODO: make this thread safe
}

SyntaxNode* SyntaxNode::AddChild(const SyntaxNode& node)
{
	this->children.push_back(SyntaxNode(node, parent));
	return &this->children.back(); // TODO: make this thread safe
}

void SyntaxNode::SetChildren(const std::vector<SyntaxNode>& children)
{
	this->RemoveChildren();
	this->children = children;
}

void SyntaxNode::InsertBetween(std::vector<SyntaxNode>::iterator position,
                               const SyntaxNode& node)
{
	SyntaxNode tmp = *position;
	position = this->children.erase(position);
	position = this->children.insert(position, node);
	position->AddChild(tmp);
}

void SyntaxNode::RemoveChild(const Token& token)
{
	// TODO: should probably assert that the token is a child of the node
	for (auto it = this->children.begin(); it != this->children.end(); ++it)
	{
		if (it->GetToken() == token)
		{
			this->children.erase(it);
			return;
		}
	}
}

void SyntaxNode::RemoveChild(std::vector<SyntaxNode>::iterator position)
{
	this->children.erase(position);
}

void SyntaxNode::RemoveChildren(void)
{
	this->children.clear();
}

std::vector<SyntaxNode>::iterator SyntaxNode::begin(void)
{
	return this->children.begin();
}

std::vector<SyntaxNode>::iterator SyntaxNode::end(void)
{
	return this->children.end();
}

std::vector<SyntaxNode>::reverse_iterator SyntaxNode::rbegin(void)
{
	return this->children.rbegin();
}

std::vector<SyntaxNode>::reverse_iterator SyntaxNode::rend(void)
{
	return this->children.rend();
}

const std::vector<SyntaxNode>::const_iterator SyntaxNode::cbegin(void) const
{
	return this->children.cbegin();
}

const std::vector<SyntaxNode>::const_iterator SyntaxNode::cend(void) const
{
	return this->children.cend();
}

const std::vector<SyntaxNode>::const_reverse_iterator
SyntaxNode::crbegin(void) const
{
	return this->children.crbegin();
}

const std::vector<SyntaxNode>::const_reverse_iterator
SyntaxNode::crend(void) const
{
	return this->children.crend();
}

