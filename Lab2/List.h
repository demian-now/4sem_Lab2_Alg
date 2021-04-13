#pragma once
#include <cstddef>
#include <string>

using namespace std;

template<class Type>
class BiList
{
public:

	BiList();
	~BiList();
	void push_back(Type);
	void push_front(Type);
	void pop_back();
	void pop_front();
	void insert(Type, size_t);
	Type at(size_t);
	void remove(size_t);
	size_t get_size();
	void print_to_console();
	void clear();
	void set(size_t, Type);
	bool isEmpty();
	void reverse();
	void swap(size_t, size_t);

private:
	struct Node
	{
		Type data;
		Node* prev = NULL;
		Node* next = NULL;
	};

	Node* head;
	Node* last;
	size_t size;
};