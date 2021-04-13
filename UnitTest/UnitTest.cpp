#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab2/BinaryTree.cpp"
#include "../Lab2/List.cpp"
#include "../Lab2/RBTree.cpp"
using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(BiListTest)
	{
	public:
		BiList<int> Empty;
		BiList<int> NotEmpty;
		TEST_METHOD_INITIALIZE(SetUp)
		{
			for (size_t i = 0; i < 3; i++)
				NotEmpty.push_back(i + 1);
		}
		TEST_METHOD(IsEmpty_for_NotEmpty)
		{
			Assert::AreEqual(NotEmpty.isEmpty(), false);
		}
		TEST_METHOD(IsEmpty_for_Empty)
		{
			Assert::AreEqual(Empty.isEmpty(), true);
		}
		TEST_METHOD(Get_Size_for_Empty)
		{
			size_t real_size = 0;
			Assert::AreEqual(Empty.get_size(), real_size);
		}
		TEST_METHOD(Get_Size_for_NotEmpty)
		{
			size_t real_size = 3;
			Assert::AreEqual(NotEmpty.get_size(), real_size);
		}
		TEST_METHOD(at_correct_index)
		{
			Assert::AreEqual(NotEmpty.at(2), 3);
		}
		TEST_METHOD(at_incorrect_index)
		{
			try
			{
				Empty.at(4);
			}
			catch (const char* error)
			{
				Assert::AreEqual(error, "Incorrect index.");
			}
		}
		TEST_METHOD(Push_Back_NotEmpty)
		{
			NotEmpty.push_back(5);
			Assert::AreEqual(NotEmpty.at(3), 5);
		}
		TEST_METHOD(Push_Front_NotEmpty)
		{
			NotEmpty.push_front(0);
			Assert::AreEqual(NotEmpty.at(0), 0);
		}
		TEST_METHOD(remove_correct_index)
		{
			int temp = NotEmpty.at(2);
			NotEmpty.remove(1);
			Assert::AreEqual(NotEmpty.at(1), temp);
		}
		TEST_METHOD(Pop_Back_for_NotEmpty)
		{
			size_t real_size = NotEmpty.get_size() - 1;
			NotEmpty.pop_back();
			Assert::AreEqual(NotEmpty.get_size(), real_size);
		}
		TEST_METHOD(Pop_Back_for_Empty)
		{
			Empty.pop_back();
			Assert::AreEqual(Empty.isEmpty(), true);
		}
		TEST_METHOD(Pop_Front_for_NotEmpty)
		{
			size_t real_size = NotEmpty.get_size() - 1;
			NotEmpty.pop_front();
			Assert::AreEqual(NotEmpty.get_size(), real_size);
		}
		TEST_METHOD(insert_correct_index)
		{
			NotEmpty.insert(4, 1);
			Assert::AreEqual(NotEmpty.at(1), 4);
		}
		TEST_METHOD(insert_incorrect_index)
		{
			try
			{
				Empty.insert(2, 0);
			}
			catch (const char* error)
			{
				Assert::AreEqual("Incorrect index.", error);
			}
		}
		TEST_METHOD(remove_incorrect_index)
		{
			try
			{
				Empty.remove(2);
			}
			catch (const char* error)
			{
				Assert::AreEqual("Incorrect index.", error);
			}
		}
		TEST_METHOD(reverse_for_NotEmpty)
		{
			int last_inf = NotEmpty.at(NotEmpty.get_size() - 1);
			NotEmpty.reverse();
			Assert::AreEqual(NotEmpty.at(0), last_inf);
		}
		TEST_METHOD(Pop_Front_for_Empty)
		{
			Empty.pop_front();
			Assert::AreEqual(Empty.isEmpty(), true);
		}
		TEST_METHOD(set_correct_index)
		{
			NotEmpty.set(2, 3);
			Assert::AreEqual(NotEmpty.at(2), 3);
		}
		TEST_METHOD(set_incorrect_index)
		{
			try
			{
				NotEmpty.set(10000000, 2);
			}
			catch (const char* error)
			{
				Assert::AreEqual(error, "Incorrect index.");
			}
		}
		TEST_METHOD(Test_Clear_NotEmpty)
		{
			NotEmpty.clear();
			size_t real_size = 0;
			Assert::AreEqual(NotEmpty.get_size(), real_size);
		}
		TEST_METHOD(Test_Clear_Empty)
		{
			Empty.clear();
			size_t real_size = 0;
			Assert::AreEqual(Empty.get_size(), real_size);
		}
		TEST_METHOD(Push_Back_Empty)
		{
			Empty.push_back(5);
			Assert::AreEqual(Empty.at(0), 5);
			Empty.pop_back();
		}
		TEST_METHOD(Push_Front_Empty)
		{
			Empty.push_front(0);
			Assert::AreEqual(Empty.at(0), 0);
		}
	};
	TEST_CLASS(UnitRBTreeTest)
	{
	public:
		RedBlackTree<int, string> TestTree;
		TEST_METHOD_INITIALIZE(SetUp)
		{
			int keys[10] = { 12,-11,45,76,34,-9,15,-87,97,111 };
			string values[10] = { "cat","dog" ,"pig" ,"Kolpakov" ,"tree" ,"house" ,"beat" ,"meat" ,"SOS" ,"stackoverflow" };
			for (size_t i = 0; i < 10; i++)
				TestTree.insert(keys[i], values[i]);
		}
		TEST_METHOD(Search_real)
		{
			string answer = "Kolpakov";
			Assert::AreEqual(TestTree.find(76), answer);
		}
		TEST_METHOD(Extra_Search)
		{
			int keys[10] = { 12,-11,45,76,34,-9,15,-87,97,111 };
			string values[10] = { "cat","dog" ,"pig" ,"Kolpakov" ,"tree" ,"house" ,"beat" ,"meat" ,"SOS" ,"stackoverflow" };
			for (size_t i = 0; i < 10; i++)
				Assert::AreEqual(TestTree.find(keys[i]), values[i]);
		}
		TEST_METHOD(Search_unreal)
		{
			try {
				TestTree.find(2020);
			}
			catch (const char* error)
			{
				Assert::AreEqual(error, "No such element");
			}
		}
		TEST_METHOD(insert_test)
		{
			string answer = "SPb";
			TestTree.insert(1, answer);
			Assert::AreEqual(TestTree.find(1), answer);
		}
		TEST_METHOD(remove_test_real)
		{
			try {
				string answer = "SPb";
				TestTree.remove(1);
				TestTree.find(1);
			}
			catch (const char* error)
			{
				Assert::AreEqual(error, "No such element");
			}
		}
		TEST_METHOD(get_keys_test)
		{
			BiList<int>* keys = TestTree.get_keys();
			try {
				for (size_t i = 0; i < 10; i++)
				{
					TestTree.remove(keys->at(i));
				}
			}
			catch (const char* error)
			{
				Assert::AreEqual(1, 0);
			}
			Assert::AreEqual(TestTree.get_size(), (size_t)0);
		}
		TEST_METHOD(get_value_test)
		{
			size_t check = 0;
			string value[10] = { "cat","dog" ,"pig" ,"Kolpakov" ,"tree" ,"house" ,"beat" ,"meat" ,"SOS" ,"stackoverflow" };
			BiList<string>* values = TestTree.get_values();
			for (size_t i = 0; i < 10; i++)
			{
				string temp = values->at(i);
				for (size_t j = 0; j < 10; j++)
				{
					if (temp == value[j])
						check++;
				}
			}
			Assert::AreEqual(check, (size_t)10);
		}
		TEST_METHOD(clear_test)
		{
			TestTree.clear();
			Assert::AreEqual(TestTree.get_size(), (size_t)0);
		}
	};
	TEST_CLASS(Huffman)
	{
		TEST_METHOD(Simple)
		{
			Tree* Test = new Tree();
			string test = "abc", result = Test->Huffman(test), check = "10110";
			Assert::AreEqual(result, check);
		}
		TEST_METHOD(Medium)
		{
			Tree* Test = new Tree();
			string test = "wasdwasdwasd", result = Test->Huffman(test), check = "101100011011000110110001";
			Assert::AreEqual(result, check);
		}
		TEST_METHOD(Hard)
		{
			Tree* Test = new Tree();
			string test = "========== cборка: успешно: 0 ==========", result = Test->Huffman(test), check = "11111111110100011000111000000100001010110100001010011011011000011001011110011111011100000000010100111010101111111111";
			Assert::AreEqual(result, check);
		}
	};
}
