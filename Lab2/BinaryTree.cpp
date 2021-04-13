#pragma once
#include "BinaryTree.h"
#include "RBTree.h"
#include "RBTree.cpp"

Tree::Tree(Freq_Syms data, Tree* left, Tree* right)
{
	this->data = data;
	left_child = left;
	right_child = right; 
}

Tree::~Tree()
{

}

Tree* Tree::build_tree(BiList<Freq_Syms>& list_of_syms)
{
	BiList<Tree*> new_tree;
	for (size_t i = 0; i < list_of_syms.get_size(); i++)
	{
		Freq_Syms temp = list_of_syms.at(i);
		new_tree.push_back(new Tree(temp));
	}
	while (new_tree.get_size() > 1) 
	{
		Tree* n = new_tree.at(0);
		new_tree.pop_front();
		new_tree.push_front(n->join(new_tree.at(0)));
		new_tree.remove(1);
		sort(new_tree);
	}
	return new_tree.at(0);
}

Tree* Tree::join(Tree* attachable)
{
	Freq_Syms new_data = {this->data.value + attachable->data.value, "" ,this->data.amount + attachable->data.amount};
	return new Tree(new_data, this, attachable);
}

void Tree::get_code(string code, RedBlackTree<char, string>& map)
{
	this->data.code = code;
	if (left_child != 0)
	{
		left_child->get_code((code + "0"), map);
	}
	if (right_child != 0)
	{
		right_child->get_code((code + "1"), map);
	}
	if (left_child==NULL && right_child==NULL)
	{
		map.insert(this->data.value[0], code);
		return;
	}
}

string Tree::Huffman(string message)
{
	BiList<Freq_Syms> freq_table;
	//Подсчёт символов
	for (size_t i = 0; i < message.size(); i++)
	{
		string value;
		value.push_back(message[i]);
		bool check = true;
		for (size_t j = 0; j < freq_table.get_size(); j++)
		{
			if (freq_table.get_size() == 0)
				break;
			Freq_Syms temp = freq_table.at(j);
			if (temp.value == value)
			{
				temp.amount++;
				freq_table.set(j, temp);
				check = false;
				break;
			}
		}
		if (check)
		{
			freq_table.push_back({ value, "", 1 });
		}
	}

	sort(freq_table); print(freq_table);

	//Построение бинарного дерева Хаффмана
	Tree* code = build_tree(freq_table);

	//Ассоциативный массив символ код
	RedBlackTree<char, string> map;
	code->get_code("", map);
	cout << endl;
	map.print();

	//Кодирование
	string result, result_real;
	for (size_t i = 0; i < message.size(); i++)
	{
		result = result + map.find(message[i]) + " ";
		result_real = result_real + map.find(message[i]);
	}
	cout << endl << result << endl;
	cout << "Исходное сообщение: " << message.size() * 8 << ", закодированное: " << result.size() - message.size() << endl;
	cout << "Сжатие: " << (double)(result.size() - message.size())/(message.size() * 8)*100 << endl;
	cout << "Результат декодирования: ";

	//Декодирование по дереву Хаффмана
	code->decoder(result_real);

	return result_real;
}

void Tree::sort(BiList<Freq_Syms> &freq_table) //Простая сортировка пузырьком
{
	bool check = true;
	while (check)
	{
		for (size_t i = 0; i < freq_table.get_size()-1; i++)
		{
			if (freq_table.at(i).amount > freq_table.at(i + 1).amount)
			{
				Freq_Syms temp = freq_table.at(i);
				freq_table.set(i, freq_table.at(i + 1));
				freq_table.set(i + 1, temp);
				check = false;
			}
		}
		if (!check) 
			check = true;
		else check = false;
	}
}

void Tree::sort(BiList<Tree*>& freq_table) //Простая сортировка пузырьком
{
	bool check = true;
	while (check)
	{
		for (size_t i = 0; i < freq_table.get_size() - 1; i++)
		{
			if (freq_table.at(i)->data.amount > freq_table.at(i + 1)->data.amount)
			{
				Tree* temp = freq_table.at(i);
				freq_table.set(i, freq_table.at(i + 1));
				freq_table.set(i + 1, temp);
				check = false;
			}
		}
		if (!check)
			check = true;
		else check = false;
	}
}

string Tree::decoder(string message)
{
	string result;
	Tree* temp = this;
	size_t i = 0;
	while (i<message.size()-1)
	{
		Tree* cursor = temp;
		while (cursor->left_child!=0 && cursor->right_child!=0)
		{
			if (message[i] == '1')
				cursor = cursor->right_child;
			else
				cursor = cursor->left_child;
			i++;
		}
		result = result + cursor->data.value;
	}
	cout << result << endl;
	return result;
}

void Tree::print(BiList<Freq_Syms>& table)
{
	for (size_t i = 0; i < table.get_size(); i++)
	{
		Freq_Syms print = table.at(i);
		cout << "Value: " << print.value << " Amount: " << print.amount << endl;
	}
}
