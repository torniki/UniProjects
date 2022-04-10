#pragma once

namespace Me
{
	struct Node
	{
		int info;
		Node* left;
		Node* right;
	};

	class BinaryTree
	{
	public:
		BinaryTree(); //конструктор
		~BinaryTree(); //деструктор

		void addNode(const int k);
		void deleteNode(int k);
		void Print();
		int Count();
		bool IsEmpty();
		Node* find(int k);

		void prefixPrint(); //прямой обход (и печать)
		void infixPrint(); //симметричный обход (и печать)
		void postfixPrint(); //обратный обход (и печать)
		double getE(int x); //среднее арефмитическое всех чисел
		
	private:
		Node* root;

		Node* recurAddNode(Node* &currentRoot, const int k);
		void Delete(Node* &T, int k);
		void Del(Node* &T, Node* &P);
		void recurPrint(Node* currentRoot, int h);
		void recurCount(Node* currentRoot,int &count);
		Node* recurFind(Node* currentRoot, int k);

		void recurPrefixPrint(Node* currentRoot);
		void recurInfixPrint(Node* currentRoot);
		void recurPostfixPrint(Node* currentRoot);
		void recurDeleteTree(Node* &currentRoot);

		void recurFindE(Node* currentRoot, int &k, int &depth);
	};
}