#include<iostream>
#include "mystack.h"
#include "mytreenode.h"
using namespace std;

//先序遍历
void preorder(mytreenode* root)
{
	mystack<mytreenode*> ms;
	mytreenode* curr = root;
	while (curr != NULL || !ms.isEmpty())
	{
		while (curr == NULL&&!ms.isEmpty())
		{
			curr = ms.pop();
		}
		if (curr == NULL) break;
		cout << curr->data << " ";
		ms.push(curr->right);
		curr = curr->left;
	}
}

//中序遍历
void inorder(mytreenode* root)
{
	mystack<mytreenode*> ms;
	mytreenode* curr=root;
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
			curr = curr->right;
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

//后序遍历
void postorder(mytreenode* root)
{
	mystack<mytreenode*> ms;
	mystack<bool> msb;

	mystack<mytreenode*> msl;
	mystack<bool> msbl;
	mytreenode* curr = root;

	int status = 0;
	bool flag = false;
	while (curr != NULL || !ms.isEmpty() || !msl.isEmpty())
	{
		if (status == 0 && curr->left != NULL)
		{
			ms.push(curr);
			msb.push(flag);
			curr = curr->left;
			flag = false;
			status = 0;
		}
		else
		{
			if (status != 2 && curr->right != NULL)
			{
				msl.push(curr);
				msbl.push(flag);
				curr = curr->right;
				flag = true;
				status = 0;
			}
			else
			{
				cout << curr->data << " ";
				curr = NULL;
			}
		}

		if (flag)
		{
			if (curr == NULL&&!msl.isEmpty())
			{
				curr = msl.pop();
				flag = msbl.pop();
				status = 2;
			}
			if (curr == NULL&&!ms.isEmpty())
			{
				curr = ms.pop();
				flag = msb.pop();
				status = 1;
			};
			if (curr == NULL)break;
		}
		else
		{
			if (curr == NULL&&!ms.isEmpty())
			{
				curr = ms.pop();
				flag = msb.pop();
				status = 1;
			}
			if (curr == NULL&&!msl.isEmpty())
			{
				curr = msl.pop();
				flag = msbl.pop();
				status = 2;
			};
			if (curr == NULL)break;
		}
	}
}




int main(int argc, char *argv[])
{
	cout << "=======二叉树非递归遍历=======" << endl;
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

	mytreenode* root = mnA;

	//先序遍历
	cout << "先序遍历: " << endl;
	preorder(root);
	cout << endl;

	//中序遍历
	cout << "中序遍历: " << endl;
	inorder(root);
	cout << endl;

	//后序遍历
	cout << "后序遍历:" << endl;
	postorder(root);
	cout << endl;

	return 0;
}