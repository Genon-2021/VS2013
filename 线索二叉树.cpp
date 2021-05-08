#include<iostream>
#include "mytreenode.h"
#include "mystack.h"
using namespace std;

void inorder(mytreenode* root)
{
	mystack<mytreenode*> ms;
	mytreenode* curr = root;
	bool flag = false;
	while (curr != NULL || !ms.isEmpty())
	{
		if (!flag&&curr->left != NULL)
		{
			ms.push(curr);
			curr = curr->left;
			flag = false;
		}
		else
		{
			cout << curr->data << " ";
			if (!curr->rightisthread)
			{
				curr = curr->right;
			}
			else
			{
				curr = NULL;
			}
			flag = false;
		}
		if (curr == NULL&&!ms.isEmpty())
		{
			curr = ms.pop();
			flag = true;
		}
		if (curr == NULL) break;
	}
}

void inorderTraverseThead(mytreenode* root)
{
	mytreenode* curr = root;
	bool flag = false;
	while (curr != NULL)
	{
		if (curr->left != NULL&&!flag)
		{
			curr = curr->left;
			flag = false;
		}
		else
		{
			cout << curr->data << " ";
			flag = curr->rightisthread;
			curr = curr->right;
		}
	}
}

int main(int argc, char *argv[])
{
	cout << "=======二叉树线索遍历=======" << endl;
	//		A
	//    /   \
	//   B     C
	//    \   /  \
	//     D  E   F
	//    / \     /
	//   G   H   I
	//声明树中的结点
	mytreenode* mnA = new mytreenode('A');
	mytreenode* mnB = new mytreenode('B');
	mytreenode* mnC = new mytreenode('C');
	mytreenode* mnD = new mytreenode('D');
	mytreenode* mnE = new mytreenode('E');
	mytreenode* mnF = new mytreenode('F');
	mytreenode* mnG = new mytreenode('G');
	mytreenode* mnH = new mytreenode('H');
	mytreenode* mnI = new mytreenode('I');

	//搭建树
	mnA->set(mnB, mnC);
	mnB->set(NULL, mnD);
	mnC->set(mnE, mnF);
	mnD->set(mnG, mnH);
	mnE->set(NULL, NULL);
	mnF->set(mnI, NULL);
	mnG->set(NULL, NULL);
	mnH->set(NULL, NULL);
	mnI->set(NULL, NULL);

	mnG->right = mnD;
	mnG->rightisthread = true;
	mnH->right = mnA;
	mnH->rightisthread = true;
	mnE->right = mnC;
	mnE->rightisthread = true;
	mnI->right = mnF;
	mnI->rightisthread = true;

	mytreenode* root = mnA;

	//非递归遍历
	cout << "非递归遍历： "<<endl;
	inorder(root);
	cout << endl;

	//线索遍历
	cout << "线索遍历： "<<endl;
	inorderTraverseThead(root);
	cout << endl;

	return 0;
}

