#include <string>
#include <gtest/gtest.h>

#include <syntax_tree.h>

#include "random.h"

#define MAX_STRING_LENGTH 100
#define NRAND_TESTS 10000
#define NELEMS 100

Token::Type RandomType(void);
SyntaxNode RandomSyntaxNode(void);

TEST(SyntaxNode, Constructor)
{
	for (int i = 0; i < NRAND_TESTS; i++)
	{
		Token::Type type = RandomType();
		std::string str;
		if (type == Token::Type::List)
			str = "";
		else
			str = RandomString(MAX_STRING_LENGTH);

		SyntaxNode node(Token(type, str));

		EXPECT_EQ(type, node.GetType());
		EXPECT_EQ(str, node.GetValue());
	}
}

TEST(SyntaxNode, AddNode)
{
	for (int i = 0; i < NRAND_TESTS; i++)
	{
		SyntaxNode root = RandomSyntaxNode();
		SyntaxNode oldRoot = root;
		std::vector<SyntaxNode> nodes;
		for (int i = 0; i < NELEMS; i++)
		{
			SyntaxNode node = RandomSyntaxNode();
			root.AddChild(node);
			nodes.push_back(node);
		}

		EXPECT_EQ(oldRoot, root); // make sure nothing got clobbered
		auto treeIt = root.begin();
		auto listIt = nodes.begin();
		while ((treeIt != root.end()) && (listIt != nodes.end()))
		{
			EXPECT_EQ(*listIt, *treeIt);
			++listIt;
			++treeIt;
		}

		EXPECT_TRUE((treeIt == root.end()) && (listIt == nodes.end()));
	}
}

SyntaxNode RandomSyntaxNode(void)
{
	Token::Type type = RandomType();
	std::string str;
	if (type == Token::Type::List)
		str = "";
	else
		str = RandomString(MAX_STRING_LENGTH);

	return SyntaxNode(Token(type, str));
}
