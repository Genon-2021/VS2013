#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <time.h>
using namespace std;

const int N = 12000;
int init[N];

//�Զ���һ������
class mytreenode{
public:
	int data;
	mytreenode* left;	//����
	mytreenode* right;	//����
	mytreenode* parent;	//���ڵ�
	int height;			//����

	mytreenode(int data)
	{
		this->data = data;
		this->left = NULL;
		this->right = NULL;
		this->parent = NULL;
		this->height = 0;
	}

	void set(mytreenode* left, mytreenode* right)
	{
		this->left = left;
		this->right = right;
	}

	void setparent(mytreenode* parent)
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
	void printTree(mytreenode* r, int level)
	{
		if (r == NULL)
		{
			return;
		}
		for (int i = 0; i < level; i++)
		{
			cout << " ";
		}

		cout << r->data << "[" << getInfo(r) << ",�߶�:" << r->height << ",ƽ��ֵ:" << abs(calBalance(r)) << "]" << endl;
		printTree(r->left, level + 1);
		printTree(r->right, level + 1);
	}

	//��ָ���ڵ��������нڵ�߶ȸ��Լ�1�ķ���
	void decreaseHeight(mytreenode* curr)
	{
		curr = curr->parent;
		while (curr != NULL)
		{
			curr->height = curr->height - 1;
			curr = curr->parent;
		}
	}

	//����ָ���ڵ�߶ȵķ���
	void updateHeight(mytreenode* r)
	{
		//��ȡ��ǰ�ڵ��������ĸ߶�
		int leftHeight = (r->left == NULL) ? (-1) : (r->left->height);
		//��ȡ��ǰ�ڵ��������ĸ߶�
		int rightHeight = (r->right == NULL) ? (-1) : (r->right->height);
		if (leftHeight > rightHeight)
		{
			r->height = leftHeight + 1;
		}
		else
		{
			r->height = rightHeight + 1;
		}
	}

	//�Ӵ˽ڵ������������Ƚڵ㼰�˽ڵ�ĸ߶ȸ��µķ���
	void updateHeightCascade(mytreenode* curr)
	{
		while (curr != NULL)
		{
			updateHeight(curr);
			curr = curr->parent;
		}
	}

	//����ָ���ڵ�ƽ������ķ���
	int calBalance(mytreenode* r)
	{
		//��ȡ��ǰ�ڵ��������ĸ߶�
		int leftHeight = (r->left == NULL) ? (-1) : (r->left->height);
		//��ȡ��ǰ�ڵ��������ĸ߶�
		int rightHeight = (r->right == NULL) ? (-1) : (r->right->height);
		return leftHeight - rightHeight;
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

		if (y != NULL){ y->setparent(v); }
		c->setparent(v->parent);
		v->setparent(c);

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

		if (y != NULL){ y->setparent(v); }
		c->setparent(v->parent);
		v->setparent(c);

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

	
	//������ķ���
	void insert(int c)
	{
		mytreenode* newNode = new mytreenode(c);
		if (root == NULL)
		{
			root = newNode;
			//��ӡƽ��ǰ�����
			cout << "----------------ƽ��ǰ�����----------------" << endl;
			printTree(root, 0);
			cout << "--------------------------------------------" << endl;
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
					//���½ڵ����Ľڵ�ԭ����Ҷ�ӽڵ�
					if (curr->left == NULL)
					{
						//�Ӵ˽ڵ������������Ƚڵ㼰�˽ڵ�ĸ߶ȸ���
						updateHeightCascade(curr);
					}
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
					//���½ڵ����Ľڵ�ԭ����Ҷ�ӽڵ�
					if (curr->right == NULL)
					{
						updateHeightCascade(curr);
					}
					break;
				}
				else
				{
					curr = curr->left;
				}
			}
		}
		
		//��ӡƽ��ǰ�����
		cout << "----------------ƽ��ǰ�����----------------" << endl;
		printTree(root, 0);
		cout << "--------------------------------------------" << endl;
		//�Բ����Ķ�����������ƽ��
		bool need = rebalance(newNode);
		if (!need)
		{
			return;
		}
		//��ӡƽ������
		cout << "----------------ƽ�������----------------" << endl;
		printTree(root, 0);
		cout << "--------------------------------------------" << endl;
	}
	
	bool rebalance(mytreenode* temp)
	{
		//���ڼ�¼�½ڵ㵽���²�ʧ��ڵ��·��
		vector<mytreenode*> path;

		//���²���Ľڵ������ȷ���ʼѰ��������ʧ��ڵ�
		int balance = 0;
		//�ӵ�ǰ�ڵ�������Ѱ�����²��ʧ��ڵ�
		while (temp != NULL)
		{
			//�������ڵ��¼��·����
			path.push_back(temp);
			//�����ƽ������
			balance = calBalance(temp);
			//��ʧ����ֹ����
			if (abs(balance) >= 2)
			{
				break;
			}
			temp = temp->parent;
		}
		//���ҵ����¼���²��ʧ��ڵ�
		if (temp != NULL)
		{
			mytreenode* g = temp;
			mytreenode* p = path[path.size() - 2];
			mytreenode* v = path[path.size() - 3];

			//����zag�������
			if (g->right == p&&p->right == v)
			{
				cout << "zag����" << endl;
				zag(g);
				//��p�������еĽڵ�߶ȼ�1
				decreaseHeight(p);
				//����g�ĸ߶�
				updateHeight(g);
				//����p�ĸ߶�
				updateHeight(p);
			}
			//����zig����
			else if (g->left == p&&p->left == v)
			{
				cout << "zig����" << endl;
				zig(g);
				//��p�������еĽڵ�߶ȼ�1
				decreaseHeight(p);
				//����g�ĸ߶�
				updateHeight(g);
				//����p�ĸ߶�
				updateHeight(p);
			}
			//����zig-zag˫�����
			else if (g->right == p&&p->left == v)
			{
				cout << "zig-zag˫��" << endl;
				zig(p);
				zag(g);
				//��v�������еĽڵ�߶ȼ�1
				decreaseHeight(v);
				//����g�ĸ߶�
				updateHeight(g);
				//����p�ĸ߶�
				updateHeight(p);
				//����v�ĸ߶�
				updateHeight(v);
			}
			//����zag-zig˫�����
			else
			{
				cout << "zag-zig˫��" << endl;
				zag(p);
				zig(g);
				//��v�������еĽڵ�߶ȼ�1
				decreaseHeight(v);
				//����g�ĸ߶�
				updateHeight(g);
				//����p�ĸ߶�
				updateHeight(p);
				//����v�ĸ߶�
				updateHeight(v);
			}
			return true;
		}

	}
	
	
	//����ָ���ַ��ķ���
	mytreenode* search(char c)
	{
		int count = 0;
		mytreenode* curr = root;
		while (true)
		{
			count++;
			if (curr == NULL)
			{
				cout << "û���ҵ�����������Ϊ" << count << endl;
				return NULL;
			}
			else if (c == curr->data)
			{
				cout << "�ɹ��ҵ�����������Ϊ" << count << endl;
				return curr;
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
	}

	void traverseInner(mytreenode* curr, void(*process)(mytreenode*))
	{
		if (curr == NULL) return;
		traverseInner(curr->left, process);
		process(curr);
		traverseInner(curr->right, process);
	}

	//�����ɶ�����ʵ�ֵ������б�ķ���
	void traverse(void(*process) (mytreenode*))
	{
		mytreenode* curr = root;
		traverseInner(curr, process);
		cout << "nil" << endl;
	}
	
};

//����ʱ����һ���ڵ�ķ���
void task(mytreenode* curr)
{
	cout << curr->data << "(" << curr->height << ")->";
}

int main(int argc, char *argv[])
{
	//�����յĶ���������
	myBinarySearchTree mbst(NULL);

	//��ʼ��������
	//int init[] = {1,2,3,4,5,6};
	//char init[7] = {'A', 'B', 'C', 'D', 'E', 'F', 'H'};
	//char init[7] = { 'A', 'C', 'E', 'H', 'F', 'D', 'B' };
	//char init[12] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L' };
	int j=0;
	ifstream read;
	read.open("F:\\AVL1.txt");
	if (!read){
		cout << "open file error" << endl;
	}
	while (!read.eof()) {
		read>>init[j++];
	}
	read.close();
	
	clock_t start,end;

	//���β���
	start = clock();
	for (int i = 0; i < N; i++)
	{
		//cout << "\n===========================����" << init[i] << "==========================" << endl;
		mbst.insert(init[i]);
		//cout << "===============================================" << endl;

	}
	end = clock();
	cout << "Run Time:" << end - start << endl;

	//ִ�����б�һ���ı���
	//cout << "======�����ɶ�����ʵ�ֵ������б�======" << endl;
	//mbst.traverse(task);

	//��������
	//cout << "======����ָ�����ݵ�Ԫ��======" << endl;
	//cout << "����D" << endl;
	//mbst.search('D');
	//cout << "����H" << endl;
	//mbst.search('H');
	//cout << "����G�������ڣ���������" << endl;
	//mbst.search('G');

	//����һ��Ԫ��
	//cout << "==========����Ԫ��==========" << endl;
	//cout << "-----------����13------------" << endl;
	//mbst.insert('13');
	//cout << "-----------����I------------" << endl;
	//mbst.insert('I');
	//cout << "======����ָ�����ݵ�Ԫ��======" << endl;
	//cout << "����G" << endl;
	//mbst.search('G');
	//cout << "======�����ɶ�����ʵ�ֵ������б�======" << endl;
	//mbst.traverse(task);
	system("pause");
	return 0;
}