#pragma once
#include <string>
#include "RBTree.h"  
#include "List.h"

using namespace std;

struct Freq_Syms {
	string value, code;
	unsigned amount = 0;
};

class Tree
{
private:
	Tree* left_child;
	Tree* right_child;
	Freq_Syms data;	
	
	Tree* build_tree(BiList<Freq_Syms>&);
	Tree* join(Tree* attachable);
	void get_code(string, RedBlackTree<char, string>&);
	void sort(BiList<Freq_Syms>&);
	void sort(BiList<Tree*>&);
	void print(BiList<Freq_Syms>&);
	string decoder(string);

public:
	Tree(Freq_Syms data = {"","",0}, Tree* left = NULL, Tree* right = NULL);
	~Tree();

	string Huffman(string);
};