#include<iostream>
#include "myBinarySearchTree.h"
using namespace std;

void task(mytreenode* curr)
{
	cout << curr->data << "->";
}

int main(int argc, char *argv[])
{
	//			D
	//		  /   \
	//		B       F
	//	   /  \    / \
	//    A    C  E   H
	//			     /  \
	//				G    I

	mytreenode* A = new mytreenode('A');
	mytreenode* B = new mytreenode('B');
	mytreenode* C = new mytreenode('C');
	mytreenode* D = new mytreenode('D');
	mytreenode* E = new mytreenode('E');
	mytreenode* F = new mytreenode('F');
	mytreenode* H = new mytreenode('H');

	D->set(B, F);
	B->set(A, C);
	F->set(E, H);

	mytreenode* root = D;

	myBinarySearchTree mbst(root);

	cout << "====�����ɶ�����ʵ�ֵ������б�=====" << endl;
	mbst.traverse(task);

	//��������
	cout << "========����ָ�����ݵ�Ԫ��=========" << endl;
	cout << "����D" << endl;
	mbst.search('D');
	cout << "����H" << endl;
	mbst.search('H');
	cout << "����G�������ڣ�����������" << endl;
	mbst.search('G');

	//����һ��Ԫ��
	cout << "=============����Ԫ��==============" << endl;
	cout << "����G" << endl;
	mbst.insert('G');
	cout << "����I" << endl;
	mbst.insert('I');
	cout << "==========����ָ�����ݵ�Ԫ��=======" << endl;
	cout << "����G" << endl;
	mbst.search('G');
	cout << "=========ɾ��ָ�����ݵ�Ԫ��==========" << endl;
	cout << "ɾ��D" << endl;
	mbst.del('D');
	cout << "=====�����ɶ�����ʵ�ֵ������б�=====" << endl;
	mbst.traverse(task);
	

	return 0;
}