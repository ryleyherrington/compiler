#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include <stdio.h>

#include "syntax_tree.h"

class CodeGenerator
{
public:
   	CodeGenerator(const SyntaxNode* tree, FILE* out = stdout);

	virtual void Synthesize(void) = 0;

protected:
	const SyntaxNode* tree;
	FILE* out;
};

#endif // CODE_GENERATOR_H

