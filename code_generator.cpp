#include "code_generator.h"

#include <assert.h>

CodeGenerator::CodeGenerator(const SyntaxNode* tree, FILE* out) :
	tree(tree),
	out(out)
{
	assert(this->tree);
	assert(this->out);
}

