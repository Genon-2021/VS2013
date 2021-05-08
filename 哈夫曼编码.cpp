#include<iostream>
#include "mytreenode.h"
#include <vector>
#include <string>

using namespace std;

mytreenode* createtree(int count, char* nr, float* weight)
{
	vector<mytreenode*> forest;
	for (int i = 0; i < count; i++)
	{
		mytreenode* temp = new mytreenode(nr[i], weight[i], true);
		forest.push_back(temp);
	}

	for (int i = 0; i < count - 1; i++)
	{
		mytreenode* A = NULL;
		mytreenode* B = NULL;
		int index = 0;
		float min = 999999;
		for (int j = 0; j < count - i; j++)
		{
			mytreenode* temp = forest[j];
			if (temp->weight < min)
			{
				min = temp->weight;
				A = temp;
				index = j;
			}
		}
		forest.erase(forest.begin() + index);

		index = 0;
		min = 999999;
		for (int j = 0; j < count - i - 1; j++)
		{
			mytreenode* temp = forest[j];
			if (temp->weight < min)
			{
				min = temp->weight;
				B = temp;
				index = j;
			}
		}
		forest.erase(forest.begin() + index);

		mytreenode* newtree = new mytreenode('#', A->weight + B->weight, false);
		newtree->left = A;
		newtree->right = B;
		forest.push_back(newtree);
	}
	return forest[0];
}

void gencode(mytreenode* root, string code)
{
	if (root == NULL) return;
	if (root->isLeaf)
	{
		cout << root->data << ":" << code << endl;
	}
	else
	{
		gencode(root->left, code + "0");
		gencode(root->right, code + "1");
	}
}

void decode(mytreenode* root, int count, int* code)
{
	mytreenode* curr = root;
	int i = 0;
	while (i < count)
	{
		if (curr->isLeaf)
		{
			cout << curr->data;
			curr = root;
			continue;
		}
		int c = code[i];
		i++;
		if (c == 0)
		{
			curr = curr->left;
		}
		else
		{
			curr = curr->right;
		}
	}
	cout << curr->data << endl;
}

int main(int argc, char *argy[])
{
	const int count = 4;
	char nr[count] = { 'A', 'B', 'C', 'D' };
	float weight[count] = { 7, 5, 2, 4 };

	mytreenode* root = createtree(count, nr, weight);
	cout << "哈夫曼编码为\n=================="<< endl;
	gencode(root, "");
	const int length = 10;
	int code[length] = { 1, 0, 1, 1, 1, 0, 0, 1, 1, 0 };
	cout << "======================\n要解编码的序列为：";
	for (int i = 0; i < length; i++)
	{
		cout << code[i];
	}
	cout << endl;
	cout << "解码结果为：";
	decode(root, length, code);
	cout<< "========================" << endl;

	return 0;
}