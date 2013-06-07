#ifndef SEMANTIC_ANALYZER_H
#define SEMANTIC_ANALYZER_H

#include "syntax_tree.h"

class SemanticAnalyzer
{
public:
	SemanticAnalyzer(const SyntaxNode* tree);
	~SemanticAnalyzer(void);

	inline const SyntaxNode* GetTree(void) const
	{
		return this->tree;
	}

	void PrintTree(FILE* file = stdout);

	void Construct(void);

private:
	SyntaxNode* tree;
	const SyntaxNode* sourceTree;

	void reorganize(void);
	void checkTypes(void);
	void checkNodeTypes(SyntaxNode* node);

	void reorganizeLets(void);
	void reorganizeLetsHelper(SyntaxNode* node);
	void reorganizeLet(SyntaxNode* node);

	void list(const SyntaxNode* node, SyntaxNode* parent); 
	
	void makeIntToFloat(std::vector<SyntaxNode>::iterator it,
	                    SyntaxNode* parent);
};

#endif // SEMANTIC_ANALYZER_H

