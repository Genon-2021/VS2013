#include<iostream>
#include "myqueue.h"
#include "mytreenode.h"
using namespace std;

void levelT(mytreenode* root)
{
	myqueue<mytreenode*> mq;
	mytreenode* curr = root;
	while (curr != NULL || !mq.isEmpty())
	{
		if (curr != NULL)
		{
			cout << curr->data << " ";
			if (curr->left != NULL)
			{
				mq.offer(curr->left);
			}
			if (curr->right != NULL)
			{
				mq.offer(curr->right);
			}
			curr = NULL;
		}
		else if (!mq.isEmpty())
		{
			curr = mq.poll();
		}

	}
}

int main(int argc, char *argv[])
{
	cout << "=======二叉树的层次遍历=======" << endl;
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

	cout << "层次遍历:";
	levelT(root);
	cout << endl;
	return 0;

}