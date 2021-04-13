#pragma once
#include <iostream>
#include "RBTree.h"

using namespace std;

//конструктор для узла дерева

template<class Key_Type, class Value_Type>
RedBlackTree<Key_Type, Value_Type>::Node::Node(Key_Type Key, Value_Type Value, Node* parent, Node* left, Node* right, Color COLOR)
{
	this->Key = Key;
	this->Value = Value;
	this->left = left;
	this->right = right;
	this->parent = parent;
	this->COLOR = COLOR;
}

//деструктор узла дерева

template<class Key_Type, class Value_Type>
RedBlackTree<Key_Type, Value_Type>::Node::~Node()
{

}

//восстановление после вставки

template<class Key_Type, class Value_Type>
void RedBlackTree<Key_Type, Value_Type>::recovery(Node* new_Node)
{
	Node* parent, * grandParent;
	while (new_Node->parent->COLOR == RED)
	{
		parent = new_Node->parent;
		grandParent = parent->parent;
		if (grandParent->left == parent)
		{
			if (grandParent->right->COLOR == RED) //случай 1
			{
				grandParent->right->COLOR = BLACK;
				grandParent->left->COLOR = BLACK;
				grandParent->COLOR = RED;
				new_Node = grandParent;
			}
			else
			{
				if (parent->right == new_Node) //случай 2
				{
					new_Node = parent;
					leftRotate(new_Node);
				}
				//случай 3
				new_Node->parent->COLOR = BLACK;
				new_Node->parent->parent->COLOR = RED;
				rightRotate(new_Node->parent->parent);
			}
		}
		else
		{
			if (grandParent->left && grandParent->left->COLOR == RED) //случай 1
			{
				grandParent->right->COLOR = BLACK;
				grandParent->left->COLOR = BLACK;
				grandParent->COLOR = RED;
				new_Node = grandParent;
			}
			else 
			{
				if (parent->left == new_Node) //случай 2
				{
					new_Node = parent;
					rightRotate(new_Node);
				}
				//случай 3
				new_Node->parent->COLOR = BLACK;
				new_Node->parent->parent->COLOR = RED;
				leftRotate(new_Node->parent->parent);
			}
		}
	}
	root->COLOR = BLACK;
}

//левый поворот

template<class Key_Type, class Value_Type>
void RedBlackTree<Key_Type, Value_Type>::leftRotate(Node* actual)
{
	if (actual->right == nil) return;
	Node* temp = actual->right;

	if (temp->left != nil) 
	{
		actual->right = temp->left;
		temp->left->parent = actual;
	}
	else 
		actual->right = nil;
	if (temp != nil) 
		temp->parent = actual->parent;
	if (actual->parent != nil) 
	{
		if (actual == actual->parent->left)
			actual->parent->left = temp;
		else
			actual->parent->right = temp;
	}
	else 
	{
		temp->parent = nil;
		root = temp;
	}
	temp->left = actual;
	if (actual != nil) 
		actual->parent = temp;
}

//правый поворот

template<class Key_Type, class Value_Type>
void RedBlackTree<Key_Type, Value_Type>::rightRotate(Node* actual)
{
	Node* temp = actual->left;
	actual->left = temp->right;
	if (temp->right != nil) 
		temp->right->parent = actual;
	if (temp != nil) 
		temp->parent = actual->parent;
	if (actual->parent != nil) 
	{
		if (actual == actual->parent->right)
			actual->parent->right = temp;
		else
			actual->parent->left = temp;
	}
	else 
	{
		root = temp;
	}
	temp->right = actual;
	if (actual != nil) actual->parent = temp;
}

//восстановление после удаления элемента

template<class Key_Type, class Value_Type>
void RedBlackTree<Key_Type, Value_Type>::recoveryRemove(Node* x_Node)
{
	Node* brother;
	while (x_Node != root && x_Node->COLOR == BLACK) 
	{
		if (x_Node == x_Node->parent->left) 
		{
			brother = x_Node->parent->right;
			if (brother->COLOR == RED) 
			{
				brother->COLOR = BLACK;
				x_Node->parent->COLOR = RED;
				leftRotate(x_Node->parent);
				brother = x_Node->parent->right;
			}
			if (brother->left->COLOR == BLACK && brother->right->COLOR == BLACK) 
			{
				brother->COLOR = RED;
				x_Node = x_Node->parent;
			}
			else 
			{
				if (brother->right->COLOR == BLACK) 
				{
					brother->left->COLOR = BLACK;
					brother->COLOR = RED;
					rightRotate(brother);
					brother = x_Node->parent->right;
				}
				brother->COLOR = x_Node->parent->COLOR;
				x_Node->parent->COLOR = BLACK;
				brother->right->COLOR = BLACK;
				leftRotate(x_Node->parent);
				x_Node = root;
			}
		}
		else 
		{
			brother = x_Node->parent->left;
			if (brother->COLOR == RED) 
			{
				brother->COLOR = BLACK;
				x_Node->parent->COLOR = RED;
				rightRotate(x_Node->parent);
				brother = x_Node->parent->left;
			}
			if (brother->right->COLOR == BLACK && brother->left->COLOR == BLACK) 
			{
				brother->COLOR = RED;
				x_Node = x_Node->parent;
			}
			else 
			{
				if (brother->left->COLOR == BLACK) 
				{
					brother->right->COLOR = BLACK;
					brother->COLOR = RED;
					leftRotate(brother);
					brother = x_Node->parent->left;
				}
				brother->COLOR = x_Node->parent->COLOR;
				x_Node->parent->COLOR = BLACK;
				brother->left->COLOR = BLACK;
				rightRotate(x_Node->parent);
				x_Node = root;
			}
		}
	}
	x_Node->COLOR = BLACK;
}

//конструктор для пустого дерева

template<class Key_Type, class Value_Type>
RedBlackTree<Key_Type, Value_Type>::RedBlackTree()
{
	if(typeid(Value_Type).name() == typeid(string).name())
		nil = new Node(0, " ", NULL, NULL, NULL, BLACK);
	else
		nil = new Node(0, 0, NULL, NULL, NULL, BLACK);
	root = nil;
	size = 0;
}

//деструктор для дерева

template<class Key_Type, class Value_Type>
RedBlackTree<Key_Type, Value_Type>::~RedBlackTree()
{
	clear(); 
}

//вставка нового узла

template<class Key_Type, class Value_Type>
void RedBlackTree<Key_Type, Value_Type>::insert(Key_Type Key, Value_Type Value)
{
	Node* new_Node = new Node(Key, Value, nil, nil, nil);
	if (size == 0)
	{
		root = new_Node;
		root->COLOR = BLACK;
		size++;
		return;
	}
	Node* temp = root;
	new_Node->COLOR = RED;
	while (1)
	{
		if (Key > temp->Key)
		{
			if (temp->right == nil)
			{
				temp->right = new_Node;
				new_Node->parent = temp;
				break;
			}
			temp = temp->right;
		}
		else
		{
			if (temp->left == nil)
			{
				temp->left = new_Node;
				new_Node->parent = temp;
				break;
			}
			temp = temp->left;
		}
	}
	recovery(new_Node);
	size++;
}

template<class Key_Type, class Value_Type>
void RedBlackTree<Key_Type, Value_Type>::remove(Key_Type Key)
{
	if (root == nil) 
		throw "Tree is empty";
	Node* NodeToDelete = root;

	while (NodeToDelete->Key != Key) //поиск элемента
	{
		if (Key > NodeToDelete->Key) 
			NodeToDelete = NodeToDelete->right;
		else 
			NodeToDelete = NodeToDelete->left;
		if (NodeToDelete == nil) 
			throw "No such element";
	}

	Node* x_Node, *w_Node;
	Color origCOLOR = NodeToDelete->COLOR;

	if (NodeToDelete->left == nil) 
	{
		x_Node = NodeToDelete->right;
		if (NodeToDelete->parent == nil) 
			root = x_Node;
		else if (NodeToDelete->parent->left == NodeToDelete) 
			NodeToDelete->parent->left = x_Node;
		else 
			NodeToDelete->parent->right = x_Node;
		x_Node->parent = NodeToDelete->parent;
	}
	else if (NodeToDelete->right == nil) 
	{
		x_Node = NodeToDelete->left;
		if (NodeToDelete->parent == nil) 
			root = x_Node;
		else if (NodeToDelete->parent->left == NodeToDelete) 
			NodeToDelete->parent->left = x_Node;
		else 
			NodeToDelete->parent->right = x_Node;
		x_Node->parent = NodeToDelete->parent;
	}
	else 
	{
		Node* temp = NodeToDelete;
		w_Node = NodeToDelete->right;
		while (w_Node->left != nil) 
			w_Node = w_Node->left;
		origCOLOR = w_Node->COLOR;
		NodeToDelete = w_Node;
		x_Node = NodeToDelete->right;
		if (NodeToDelete->parent == temp) 
			x_Node->parent = NodeToDelete;
		else 
		{
			if (NodeToDelete->parent == nil) 
			{
				root = x_Node;
				NodeToDelete->right->parent = nil;
			}
			else if (NodeToDelete->parent->right == NodeToDelete) 
				NodeToDelete->parent->right = x_Node;
			else 
				NodeToDelete->parent->left = x_Node;
			x_Node->parent = NodeToDelete->parent;
			NodeToDelete->right = temp->right;
			NodeToDelete->right->parent = NodeToDelete;
		}

		if (temp->parent == nil) 
			root = NodeToDelete;
		else if (temp == temp->parent->left)
			temp->parent->left = NodeToDelete;
		else 
			temp->parent->right = NodeToDelete;

		NodeToDelete->parent = temp->parent;
		NodeToDelete->left = temp->left;
		NodeToDelete->left->parent = NodeToDelete;
		NodeToDelete->COLOR = temp->COLOR;
	}

	if (origCOLOR == BLACK) 
		recoveryRemove(x_Node);
	size--;
}

template<class Key_Type, class Value_Type>
Value_Type RedBlackTree<Key_Type, Value_Type>::find(Key_Type Key)
{
	if (root == nil)
		throw "Tree is empty";
	Node* nodeToFind = root;

	while (nodeToFind->Key != Key) //поиск элемента
	{
		if (Key > nodeToFind->Key)
			nodeToFind = nodeToFind->right;
		else
			nodeToFind = nodeToFind->left;
		if (nodeToFind == nil)
			throw "No such element";
	}

	return nodeToFind->Value;
}

template<class Key_Type, class Value_Type>
void RedBlackTree<Key_Type, Value_Type>::iteration_over(Node* actual, BiList<Key_Type> *keys, BiList<Value_Type> *values)
{
	if (keys == NULL)
	{
		if (actual->left!=nil)
			iteration_over(actual->left, NULL, values);
		if (actual->right!=nil)
			iteration_over(actual->right, NULL, values);
		values->push_back(actual->Value);
	}
	else
	{
		if (actual->left!=nil)
			iteration_over(actual->left, keys, NULL);
		if (actual->right!=nil)
			iteration_over(actual->right, keys, NULL);
		keys->push_back(actual->Key);
	}
}

template<class Key_Type, class Value_Type>
void RedBlackTree<Key_Type, Value_Type>::clear()
{
	while (root != nil)
		remove(root->Key);
}

template<class Key_Type, class Value_Type>
BiList<Key_Type>* RedBlackTree<Key_Type, Value_Type>::get_keys()
{
	BiList<Key_Type>* result = new BiList<Key_Type>;
	iteration_over(root, result, NULL);
	return result;
}

template<class Key_Type, class Value_Type>
BiList<Value_Type>* RedBlackTree<Key_Type, Value_Type>::get_values()
{
	BiList<Value_Type>* result = new BiList<Value_Type>;
	iteration_over(root, NULL, result);
	return result;
}

template<class Key_Type, class Value_Type>
void RedBlackTree<Key_Type, Value_Type>::print()
{
	BiList<Key_Type>* keys = get_keys();
	BiList<Value_Type>* values = get_values();
	for (size_t i = 0; i < size; i++)
		cout << keys->at(i) << "||" << values->at(i) << endl;
	cout << endl;
}

template<class Key_Type, class Value_Type>
size_t RedBlackTree<Key_Type, Value_Type>::get_size()
{
	return size;
}
