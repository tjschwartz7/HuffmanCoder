#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;

struct HuffmanNode
{
	char symb;
	int  weight;
	HuffmanNode* LCH;
	HuffmanNode* RCH;
};

class HuffmanTree
{
private:
	//This is the entire tree
	HuffmanNode tree;

	//This will contain a list of all nodes which will be compiled into a tree-
	//Each node is either a leaf, containing a character and its respective character frequency, or a non-leaf node containing a frequency 
	//This frequency (for non-leaf nodes) simply contains the total summed frequency of its two children
	std::vector<HuffmanNode> nodes;
public:
	void AddCharacterToTree(char c);
	void CompileCompletedTree();
	inline HuffmanNode GetHuffmanTree() { return tree; }
private:
	void PerformOneNodeMerge();
};

#endif // !1




