#include <string>
#include <gtest/gtest.h>

#include <token.h>

#include "random.h"

#define MAX_STRING_LENGTH 100
#define NRAND_TESTS 10000

Token::Type RandomType(void);

TEST(Token, Constructor)
{
	for (int i = 0; i < NRAND_TESTS; i++)
	{
		Token::Type type = RandomType();
		std::string str;
		if (type == Token::Type::List)
			str = "";
		else
			str = RandomString(MAX_STRING_LENGTH);

		Token token(type, str);

		EXPECT_EQ(type, token.GetType());
		EXPECT_EQ(str, token.GetLexeme());
	}
}

TEST(Token, CopyConstructor)
{
	for (int i = 0; i < NRAND_TESTS; i++)
	{
		Token::Type type = RandomType();
		std::string str;
		if (type == Token::Type::List)
			str = "";
		else
			str = RandomString(MAX_STRING_LENGTH);

		Token token(type, str);
		Token token2(token);

		EXPECT_EQ(token, token2);
	}
}

TEST(Token, Assignment)
{
	for (int i = 0; i < NRAND_TESTS; i++)
	{
		Token::Type type = RandomType();
		std::string str;
		if (type == Token::Type::List)
			str = "";
		else
			str = RandomString(MAX_STRING_LENGTH);

		Token token(type, str);
		Token token2 = token;

		EXPECT_EQ(token, token2);
	}
}

TEST(Token, Equality)
{
	for (int i = 0; i < NRAND_TESTS; i++)
	{
		Token::Type type = RandomType();
		std::string str;
		if (type == Token::Type::List)
			str = "";
		else
			str = RandomString(MAX_STRING_LENGTH);

		Token token1(type, str);
		Token token2(type, str);

		EXPECT_EQ(token1, token2);
	}
}

TEST(Token, Inequality)
{
	for (int i = 0; i < NRAND_TESTS; i++)
	{
		std::string str1 = RandomString(MAX_STRING_LENGTH);
		std::string str2 = RandomString(MAX_STRING_LENGTH);
		if (str2 == str1)
		{
			str2 += '_';
		}

		Token token1(Token::Type::Number, str1);
		Token token2(Token::Type::Number, str2);
		Token token3(Token::Type::String, str1);
		Token token4(Token::Type::String, str2);

		EXPECT_NE(token1, token2);
		EXPECT_NE(token1, token3);
		EXPECT_NE(token1, token4);
		EXPECT_NE(token2, token1);
		EXPECT_NE(token2, token3);
		EXPECT_NE(token2, token4);
		EXPECT_NE(token3, token1);
		EXPECT_NE(token3, token2);
		EXPECT_NE(token3, token4);
		EXPECT_NE(token4, token1);
		EXPECT_NE(token4, token2);
		EXPECT_NE(token4, token3);
	}
}

TEST(Token, ToString)
{
	for (int i = 0; i < NRAND_TESTS; i++)
	{
		Token::Type type = RandomType();
		std::string str;
		if (type == Token::Type::List)
			str = "";
		else
			str = RandomString(MAX_STRING_LENGTH);

		Token token(type, str);
		
		std::ostringstream builder;
		builder << '<' << TokenTypeToString(token.GetType());
		if (type != Token::Type::List)
			builder << ", " << token.GetLexeme();
		builder << '>';

		std::string expected = builder.str();

		EXPECT_EQ(expected, token.ToString());
	}
}

Token::Type RandomType(void)
{
	int idx = RandomBetween(0, static_cast<int>(Token::Type::List)); 
	return static_cast<Token::Type>(idx);
}

