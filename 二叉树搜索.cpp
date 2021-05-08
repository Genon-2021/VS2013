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

	cout << "====遍历由二叉树实现的有序列表=====" << endl;
	mbst.traverse(task);

	//进行搜索
	cout << "========搜索指定内容的元素=========" << endl;
	cout << "搜索D" << endl;
	mbst.search('D');
	cout << "搜索H" << endl;
	mbst.search('H');
	cout << "搜索G（不存在，是最差情况）" << endl;
	mbst.search('G');

	//插入一个元素
	cout << "=============插入元素==============" << endl;
	cout << "插入G" << endl;
	mbst.insert('G');
	cout << "插入I" << endl;
	mbst.insert('I');
	cout << "==========搜索指定内容的元素=======" << endl;
	cout << "搜索G" << endl;
	mbst.search('G');
	cout << "=========删除指定内容的元素==========" << endl;
	cout << "删除D" << endl;
	mbst.del('D');
	cout << "=====遍历由二叉树实现的有序列表=====" << endl;
	mbst.traverse(task);
	

	return 0;
}