#include <iostream>
#include "BinaryTree.h"
#include "List.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Rus");
    Tree* Test = new Tree();
    string s;
    cin >> s;
    cout << "\n\n" << Test->Huffman(s);
}