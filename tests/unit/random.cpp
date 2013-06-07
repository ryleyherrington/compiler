#include "random.h"

#include <stdlib.h>

int RandomBetween(int min, int max)
{
	return (rand() % (max - min + 1)) + min;
}

char RandomChar(void)
{
	return (char)RandomBetween((int)' ', (int)'~');
}

std::string RandomString(unsigned int maxLength)
{
	int length = (rand() % (maxLength - 1)) + 1;
	std::string str;

	for (int i = 0; i < length; i++)
	{
		str += RandomChar();
	}

	return str;
}

