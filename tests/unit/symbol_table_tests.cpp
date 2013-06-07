#include <string>
#include <gtest/gtest.h>
#include <symbol_table.h>

#include "random.h"

#define MAX_STRING_LENGTH 100
#define NRAND_TESTS 1000
#define NELEMS 100

TEST(SymbolTable, Add)
{
	for (int i = 0; i < NRAND_TESTS; i++)
	{
		std::vector<Token> tokens;
		SymbolTable table;
		for (int i = 0; i < NELEMS; i++)
		{
            std::string value = RandomString(MAX_STRING_LENGTH);
            while (table.Contains(value))
            {
                value = RandomString(MAX_STRING_LENGTH);
            }
            
            Token token(Token::Type::Symbol, value);
			table.Add(token);
			tokens.push_back(token);
		}
		
		for (auto it = tokens.begin(); it != tokens.end(); ++it)
		{
			EXPECT_EQ(it->GetType(), table[it->GetLexeme()].GetType());
			EXPECT_EQ(it->GetLexeme(), table[it->GetLexeme()].GetName());
		}
	}
}

TEST(SymbolTable, Get)
{
    for (int i = 0; i < NRAND_TESTS; i++)
    {
        std::vector<Token> tokens;
        SymbolTable table;
        for (int i = 0; i < NELEMS; i++)
        {
            std::string value = RandomString(MAX_STRING_LENGTH);
            while (table.Contains(value))
            {
                value = RandomString(MAX_STRING_LENGTH);
            }
            
            Token token(Token::Type::Symbol, value);
            table.Add(token);
            tokens.push_back(token);
        }
        
    	for (auto it = tokens.begin(); it != tokens.end(); ++it)
		{
            EXPECT_EQ(it->GetType(), table.Get(it->GetLexeme()).GetType());
            EXPECT_EQ(it->GetLexeme(), table.Get(it->GetLexeme()).GetName());
        }
    }
}

TEST(SymbolTable, GetFromParent)
{
    for (int i = 0; i < NRAND_TESTS; i++)
    {
        std::vector<Token> tokens;
        SymbolTable parent;
        SymbolTable table(&parent);
        for (int i = 0; i < NELEMS; i++)
        {
            std::string value = RandomString(MAX_STRING_LENGTH);
            while (table.Contains(value))
            {
                value = RandomString(MAX_STRING_LENGTH);
            }
            
            Token token(Token::Type::Symbol, value);
            parent.Add(token);
            tokens.push_back(token);
        }
        
    	for (auto it = tokens.begin(); it != tokens.end(); ++it)
		{
            EXPECT_EQ(it->GetType(), table.Get(it->GetLexeme()).GetType());
            EXPECT_EQ(it->GetLexeme(), table.Get(it->GetLexeme()).GetName());
        }
    }
}


TEST(SymbolTable, Contains)
{
    for (int i = 0; i < NRAND_TESTS; i++)
    {
        std::vector<Token> tokens;
        SymbolTable table;
        for (int i = 0; i < NELEMS; i++)
        {
            std::string value = RandomString(MAX_STRING_LENGTH);
            while (table.Contains(value))
            {
                value = RandomString(MAX_STRING_LENGTH);
            }
            
            Token token(Token::Type::Symbol, value);
            table.Add(token);
            tokens.push_back(token);
        }
        
    	for (auto it = tokens.begin(); it != tokens.end(); ++it)
		{
            EXPECT_TRUE(table.Contains(it->GetLexeme()));
        }
    }

}

TEST(SymbolTable, ContainsWithParent)
{
    for (int i = 0; i < NRAND_TESTS; i++)
    {
        std::vector<Token> tokens;
        SymbolTable parent;
        SymbolTable table(&parent);
        for (int i = 0; i < NELEMS; i++)
        {
            std::string value = RandomString(MAX_STRING_LENGTH);
            while (table.Contains(value))
            {
                value = RandomString(MAX_STRING_LENGTH);
            }
            
            Token token(Token::Type::Symbol, value);
            parent.Add(token);
            tokens.push_back(token);
        }
        
    	for (auto it = tokens.begin(); it != tokens.end(); ++it)
		{
            EXPECT_TRUE(table.Contains(it->GetLexeme()));
        }
    }
}
