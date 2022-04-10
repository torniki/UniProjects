#include "BinaryTree.h"
#include <iostream>
using namespace std;

namespace Me
{
	BinaryTree::BinaryTree() 
	{
		root = NULL;
	}

	BinaryTree::~BinaryTree()
	{
		this->recurDeleteTree(this->root);
		this->root = NULL;
	}

	void BinaryTree::addNode(const int k) 
	{
		if (root == NULL)
		{
			root = (Node*)malloc(sizeof(Node));
			root->info = k;
			root->left = NULL;
			root->right = NULL;
		}
		else
		{
			this->recurAddNode(root, k);
		}
	}

	void BinaryTree::deleteNode(int k)
	{
		this->Delete(this->root, k);
	}

	void BinaryTree::Print()
	{
		if (root == NULL)
		{
			cout << "Список пуст\n";
		}
		else
		{
			this->recurPrint(this->root, 0);
		}
	}

	bool BinaryTree::IsEmpty()
	{
		return (root == NULL);
	}

	Node* BinaryTree::find(int k)
	{
		return (this->recurFind(this->root, k));
	}

	void BinaryTree::prefixPrint() //прямой
	{
		this->recurPrefixPrint(this->root);
		cout << endl;
	}

	void BinaryTree::infixPrint() //симметричный
	{
		this->recurInfixPrint(this->root);
		cout << endl;
	}

	void BinaryTree::postfixPrint() //обратный
	{
		this->recurPostfixPrint(this->root);
		cout << endl;
	}

	int BinaryTree::Count()
	{
		int count = 0;
		if (root == NULL)
		{
			cout << "Список пуст\n";
			return count;
		}
		else
		{
			this->recurCount(this->root, count);
			return count;
		}
	}

	double BinaryTree::getE(int x)
	{
		int depth = 1;
		recurFindE(this->root, x, depth);
		return depth;
	}

	//________________________

	Node* BinaryTree::recurAddNode(Node* &currentRoot, const int k)
	{
		if (currentRoot == NULL)
		{
			currentRoot = (Node*)malloc(sizeof(Node));
			currentRoot->info = k;
			currentRoot->left = NULL;
			currentRoot->right = NULL;
		}
		else
		{
			if (k < currentRoot->info)
			{
				currentRoot->left = recurAddNode(currentRoot->left, k);
			}
			else
			{
				currentRoot->right = recurAddNode(currentRoot->right, k);
			}
		}
		return currentRoot;
	}

	void BinaryTree::Delete(Node* &T, int k)
	{
		if (T != NULL)
		{
			if (k < T->info)
			{
				Delete(T->left, k);
			}
			else if (k > T->info)
			{
				Delete(T->right, k);
			}
			else
			{
				if ((T->left == NULL) && (T->right == NULL))
				{
					Node* P = T;
					T = NULL;
					free(P); 
				}
				else if (T->left == NULL)
				{
					Node* P = T;
					T = T->right;
					free(P); 
				}
				else if (T->right == NULL)
				{
					Node* P = T;
					T = T->left;
					free(P);
				}
				else
				{
					Del(T->right, T);
				}
			}
		}
	}

	void BinaryTree::Del(Node* &T, Node* &P)
	{
		if (T->left == NULL)
		{
			P->info = T->info;
			Node* Pl = T;
			T = T->right;
			free(Pl); 
		}
		else
		{
			Del(T->left, P);
		}
	}

	void BinaryTree::recurPrint(Node* currentRoot, int h)
	{
		if (currentRoot != NULL)
		{
			this->recurPrint(currentRoot->right, h + 1);
			for (int i = 0; i < h; i++) printf("\t");
			printf("%d\n", currentRoot->info);
			this->recurPrint(currentRoot->left, h + 1);
		}
	}

	Node* BinaryTree::recurFind(Node* currentRoot, int k)
	{
		if ((k == currentRoot->info) || (currentRoot == NULL))
			return currentRoot;
		if (k < currentRoot->info)
		{
			return recurFind(currentRoot->left, k);
		}
		else
		{
			return recurFind(currentRoot->right, k);
		}
	}

	void BinaryTree::recurPrefixPrint(Node* currentRoot)
	{
		if (currentRoot != NULL) 
		{
			cout << currentRoot->info << ";  ";
			recurPrefixPrint(currentRoot->left);
			recurPrefixPrint(currentRoot->right);
		}
	}

	void BinaryTree::recurInfixPrint(Node* currentRoot)
	{
		if (currentRoot != NULL)
		{
			recurInfixPrint(currentRoot->left);
			cout << currentRoot->info << ";  ";
			recurInfixPrint(currentRoot->right);
		}
	}

	void BinaryTree::recurPostfixPrint(Node* currentRoot)
	{
		if (currentRoot != NULL)
		{
			recurPostfixPrint(currentRoot->left);
			recurPostfixPrint(currentRoot->right);
			cout << currentRoot->info << ";  ";
		}
	}

	void BinaryTree::recurDeleteTree(Node* &currentRoot)
	{
		if (currentRoot != NULL)
		{
			recurDeleteTree(currentRoot->left);
			recurDeleteTree(currentRoot->right);
			free(currentRoot);
			currentRoot = NULL;
		}
	}

	void BinaryTree::recurCount(Node* currentRoot,int &count)
	{
		if (currentRoot != NULL)
		{
			this->recurCount(currentRoot->right, count += 1);
			this->recurCount(currentRoot->left, count += 1);
		}
	}

	void BinaryTree::recurFindE(Node* currentRoot, int& k, int& depth)
	{
		if ((k == currentRoot->info) || (currentRoot == NULL))
		{
			return;
		}
		if (k < currentRoot->info && currentRoot->left == NULL)
		{
			depth = -1;
			return;
		}
		else if (k > currentRoot->info && currentRoot->right == NULL)
		{
			depth = -1;
			return;
		}
		if (k < currentRoot->info)
		{
			return recurFindE(currentRoot->left, k, depth += 1);
		}
		else
		{
			return recurFindE(currentRoot->right, k, depth += 1);
		}
	}
}