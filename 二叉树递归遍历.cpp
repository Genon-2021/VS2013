#include<iostream>
#include "MyTreeNode.h"
using namespace std;

//�������
void preorder(mytreenode* root)
{
	if (root == NULL) return;
	cout << root->data << " ";
	preorder(root->left);
	preorder(root->right);
}

//�������
void inorder(mytreenode* root)
{
	if (root == NULL) return;
	inorder(root->left);
	cout << root->data << " ";
	inorder(root->right);
}

//��������
void postorder(mytreenode* root)
{
	if (root == NULL) return;
	postorder(root->left);
	postorder(root->right);
	cout << root->data << " ";
}

int main()
{
	cout << "=======�������ĵݹ����=======" << endl;
	//		A
	//    /   \
	//   B     C
	//    \   /  \
	//     D  E   F
	//    / \     /
	//   G   H   I
	//�������еĽ��
	mytreenode* mnA = new mytreenode('A');
	mytreenode* mnB = new mytreenode('B');
	mytreenode* mnC = new mytreenode('C');
	mytreenode* mnD = new mytreenode('D');
	mytreenode* mnE = new mytreenode('E');
	mytreenode* mnF = new mytreenode('F');
	mytreenode* mnG = new mytreenode('G');
	mytreenode* mnH = new mytreenode('H');
	mytreenode* mnI = new mytreenode('I');

	//���
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

	//�������
	cout << "�������: ";
	preorder(root);
	cout << endl;

	//�������
	cout << "�������: ";
	inorder(root);
	cout << endl;

	//�������
	cout << "�������: ";
	postorder(root);
	cout << endl;

	return 0;
}



