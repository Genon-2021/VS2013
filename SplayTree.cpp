#include<iostream>
#include<string>

using namespace std;

class mytreenode
{
public:
	char data;
	mytreenode* left;
	mytreenode* right;
	mytreenode* parent;

	mytreenode(char data)
	{
		this->data = data;
		this->left = NULL;
		this->right = NULL;
		this->parent = NULL;
	}

	void setChild(mytreenode* left, mytreenode* right)
	{
		this->left = left;
		this->right = right;
	}

	void setParent(mytreenode* parent)
	{
		this->parent = parent;
	}
};

class myBinarySearchTree
{
public:
	mytreenode* root;
	//���캯��
	myBinarySearchTree(mytreenode* root)
	{
		this->root = root;
	}

	string getInfo(mytreenode* r)
	{
		if (r->parent == NULL)
		{
			return "��";
		}
		else if (r->parent->left == r)
		{
			return "��";
		}
		else
		{
			return "��";
		}
	}

	//���������ӡ������
	void printTree(mytreenode* r, int level,mytreenode* curr)
	{
		if (r == NULL)
		{
			return;
		}
		for (int i = 0; i < level; i++)
		{
			cout << " ";
		}

		cout << r->data << "[" << getInfo(r) << "]" <<((curr==r)?"<----":"") <<endl;
		printTree(r->left, level + 1,curr);
		printTree(r->right, level + 1,curr);
	}

	//ִ��zig����ת����
	void zig(mytreenode* v)
	{
		mytreenode* c = v->left;
		mytreenode* x = c->left;
		mytreenode* y = c->right;
		mytreenode* z = v->right;

		v->left = y;
		c->right = v;

		if (y != NULL){ y->setParent(v); }
		c->setParent(v->parent);
		v->setParent(c);

		if (c->parent == NULL)
		{
			root = c;
		}
		else if (c->parent->left == v)
		{
			c->parent->left = c;
		}
		else
		{
			c->parent->right = c;
		}
	}

	//ִ��zag����ת����
	void zag(mytreenode* v)
	{
		mytreenode* x = v->left;
		mytreenode* c = v->right;
		mytreenode* y = c->left;
		mytreenode* z = c->right;

		v->right = y;
		c->left = v;

		if (y != NULL){ y->setParent(v); }
		c->setParent(v->parent);
		v->setParent(c);

		if (c->parent == NULL)
		{
			root = c;
		}
		else if (c->parent->left == v)
		{
			c->parent->left = c;
		}
		else
		{
			c->parent->right = c;
		}
	}

	//����ڵ�ķ���
	void insert(char c)
	{
		mytreenode* newNode = new mytreenode(c);
		if (root == NULL)
		{
			root = newNode;
			return;
		}

		//�Ӹ��ڵ㿪ʼ��λ��
		mytreenode* curr = root;
		while (true)
		{
			if (newNode->data > curr->data)
			{
				if (curr->right == NULL)
				{
					curr->right = newNode;
					newNode->parent = curr;
					break;
				}
				else
				{
					curr = curr->right;
				}
			}
			else
			{
				if (curr->left == NULL)
				{
					curr->left = newNode;
					newNode->parent = curr;
					break;
				}
				else
				{
					curr = curr->left;
				}
			}
		}
		doubleLayerExtension(newNode, "����", false);
		//singlelayerExtension(newNode);
	}

	//����ָ���ַ��ķ���
	mytreenode* serach(char c)
	{
		// ��ǰ�ڵ�
		mytreenode* curr = root;
		while (true)
		{
			if (curr == NULL)
			{
				//cout << "û���ҵ�����������Ϊ" << count << endl;
				return NULL;
			}
			else if (c == curr->data)
			{
				//cout << "�ɹ��ҵ�����������Ϊ" << count << endl;
				//return curr;
				break;
			}
			else if (c < curr->data)
			{
				curr = curr->left;
			}
			else
			{
				curr = curr->right;
			}
		}
		doubleLayerExtension(curr, "����", true);
		return curr;
	}

	//˫����չ�ķ���
	void doubleLayerExtension(mytreenode* curr, string action, bool isPrint)
	{
		if (isPrint)
		{
			cout << "�ո�" << action << curr->data << "���" << endl;
			printTree(root, 0, curr);
			cout << "--------------------------------------" << endl;
		}

		//�����Ǹ��ڵ��Ҫ��������
		while (curr->parent != NULL)
		{
			//����������ֻ��һ�㵽��
			if (curr->parent->left == curr&&curr->parent->parent == NULL)
			{
				if (isPrint)
				{
					cout << "zig " << curr->parent->data << endl;
					cout << "----------" << endl;
				}
				//ִ��zig��ת
				zig(curr->parent);
			}
			else if (curr->parent->right == curr&&curr->parent->parent == NULL)
			{
				//����������ֻ��һ�㵽��
				  //ִ��zag��ת
				if (isPrint)
				{
					cout << "zag " << curr->parent->data << endl;
					cout << "----------" << endl;
				}
				zag(curr->parent);
			}
			else if (curr->parent->left == curr&&curr->parent->parent->left == curr->parent)
			{
				//������������
				if (isPrint)
				{
					cout << "zig " << curr->parent->parent->data;
					cout << "-zig " << curr->parent->data << endl;
					cout << "----------" << endl;
				}
				zig(curr->parent->parent);
				zig(curr->parent);
			}
			else if (curr->parent->right == curr&&curr->parent->parent->right == curr->parent)
			{
				//�������ҵ����
				if (isPrint)
				{
					cout << "zag " << curr->parent->parent->data;
					cout << "-zag " << curr->parent->data << endl;
					cout << "----------" << endl;
				}
				zag(curr->parent->parent);
				zag(curr->parent);
			}
			else if (curr->parent->left == curr&&curr->parent->parent->right == curr->parent)
			{
				//������������
				if (isPrint)
				{
					cout << "zig " << curr->parent->data;
					cout << "-zag " << curr->parent->parent->data << endl;
					cout << "----------" << endl;
				}
				zig(curr->parent);
				zag(curr->parent);
			}
			else if (curr->parent->right == curr&&curr->parent->parent->left == curr->parent)
			{
				//�������ҵ����
				if (isPrint)
				{
					cout << "zag " << curr->parent->data;
					cout << "-zig " << curr->parent->parent->data << endl;
					cout << "----------" << endl;
				}
				zag(curr->parent);
				zig(curr->parent);
			}
			if (isPrint)
			{
				printTree(root, 0, curr);
				cout << "====================================" << endl;

			}
		}
	}




	/*//�����չ�ķ���
	void singlelayerExtension(mytreenode* curr)
	{
		cout << "�ող���" << curr->data << "���" << endl;
		printTree(root, 0, curr);
		cout << "-----------------------------------------" << endl;
		//�����Ǹ��ڵ��Ҫ��������
		while (curr->parent != NULL)
		{
			//��������
			if (curr->parent->left == curr)
			{
				//ִ��zig��ת
				cout << "zig " << curr->parent->data << endl;
				cout << "----------" << endl;
				zig(curr->parent);
			}
			else
			{
				//��������
				  //ִ��zag��ת
				cout << "zag " << curr->parent->data << endl;
				cout << "----------" << endl;
				zag(curr->parent);
			}
			printTree(root, 0, curr);
			cout << "-----------------------------------------" << endl;
		}
	}
	*/
};



int main(int argc, char *argv[])
{/*
	mytreenode* A = new mytreenode('A');
	mytreenode* B = new mytreenode('B');
	mytreenode* C = new mytreenode('C');
	mytreenode* D = new mytreenode('D');
	mytreenode* F = new mytreenode('F');
	mytreenode* G = new mytreenode('G');
	mytreenode* H = new mytreenode('H');

	//��֯�ڵ��ĸ��ӹ�ϵ
	D->setChild(B, G);
	B->setChild(A, C);
	G->setChild(F, H);

	A->setParent(B);
	C->setParent(B);
	F->setParent(G);
	H->setParent(G);
	B->setParent(D);
	G->setParent(D);
*/
	//�����������������գ�
	myBinarySearchTree mbst(NULL);

	//��ʼ��������
	char init[5] = { '1', '2', '3', '4', '5' };

	//���β���
	for (int i = 0; i < 5; i++)
	{
		mbst.insert(init[i]);
	}
	cout << "ԭʼ��" << endl;
	mbst.printTree(mbst.root, 0, NULL);
	cout << "======================================" << endl;
	//����1
	cout << "����1" << endl;
	mbst.serach('1');
	//����3
	cout << "����3" << endl;
	mbst.serach('3');

	/*
	//��������������
	myBinarySearchTree mbst(D);
	//��ӡ��
	cout << "��ʼʱ" << endl;
	mbst.printTree(mbst.root, 0, NULL);
	cout << "==================================" << endl;
	//����E
	mbst.insert('E');
    */
	return 0;
}