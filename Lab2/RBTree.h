#pragma once
#include "List.h"
#include "List.cpp"
#define NULL 0

enum Color {RED, BLACK};

template<class Key_Type, class Value_Type>
class RedBlackTree
{
private:

	class Node
	{
	public:
		Key_Type Key;
		Value_Type Value;
		Node* parent;
		Node* left;
		Node* right;
		Color COLOR;
		Node(Key_Type Key, Value_Type Value, Node* parent = NULL, Node* left = NULL, Node* right = NULL, Color COLOR = RED);
		~Node();
	};

	Node* root;
	Node* nil;
	size_t size;

	void recovery(Node*);
	void leftRotate(Node*);
	void rightRotate(Node*);
	void recoveryRemove(Node*);
	
	void iteration_over(Node* actual, BiList<Key_Type>* keys, BiList<Value_Type>* values);

public:

	RedBlackTree();
	~RedBlackTree();

	void insert(Key_Type, Value_Type);
	void remove(Key_Type);
	Value_Type find(Key_Type);
	void clear(); 
	BiList<Key_Type>* get_keys();
	BiList<Value_Type>* get_values();
	void print();
	size_t get_size();
};
