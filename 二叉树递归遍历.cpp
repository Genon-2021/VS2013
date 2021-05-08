#include<iostream>
#include "MyTreeNode.h"
using namespace std;

//先序遍历
void preorder(mytreenode* root)
{
	if (root == NULL) return;
	cout << root->data << " ";
	preorder(root->left);
	preorder(root->right);
}

//中序遍历
void inorder(mytreenode* root)
{
	if (root == NULL) return;
	inorder(root->left);
	cout << root->data << " ";
	inorder(root->right);
}

//后续遍历
void postorder(mytreenode* root)
{
	if (root == NULL) return;
	postorder(root->left);
	postorder(root->right);
	cout << root->data << " ";
}

int main()
{
	cout << "=======二叉树的递归遍历=======" << endl;
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
	cout << "先序遍历: ";
	preorder(root);
	cout << endl;

	//中序遍历
	cout << "中序遍历: ";
	inorder(root);
	cout << endl;

	//后序遍历
	cout << "后序遍历: ";
	postorder(root);
	cout << endl;

	return 0;
}



