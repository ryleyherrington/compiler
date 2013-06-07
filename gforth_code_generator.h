#ifndef GFORTH_CODE_GENERATOR_H
#define GFORTH_CODE_GENERATOR_H

#include <stdio.h>

#include <functional>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "code_generator.h"
#include "symbol_table.h"
#include "syntax_tree.h"

class GforthCodeGenerator;
typedef std::function<void(GforthCodeGenerator&,
						   const SyntaxNode* node)> TranslationFunction;

class GforthCodeGenerator : public CodeGenerator
{
public:

	GforthCodeGenerator(const SyntaxNode* tree, FILE* out = stdout);

	void Synthesize(void);

private:
	std::unordered_map<std::string, TranslationFunction> translationFuncs;
	SymbolTable symbols;

	std::ostringstream globals;
	std::ostringstream main;

	void addTranslation(const std::string& symbol, TranslationFunction);

	void synthesizeNode(const SyntaxNode* node);
	void synthesizeSymbol(const SyntaxNode* node);
	void synthesizeString(const SyntaxNode* node);
	void synthesizeNumber(const SyntaxNode* node);
	void synthesizeFloat(const SyntaxNode* node);
	void synthesizeList(const SyntaxNode* node);

	void translatedOp(const SyntaxNode* node);
	void mixedOp(const SyntaxNode* node);
	void ifOp(const SyntaxNode* node);
	void whileOp(const SyntaxNode* node);
	void letOp(const SyntaxNode* node);
	void assignOp(const SyntaxNode* node);
};

#endif // GFORTH_CODE_GENERATOR_H

