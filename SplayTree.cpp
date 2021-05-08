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
	//构造函数
	myBinarySearchTree(mytreenode* root)
	{
		this->root = root;
	}

	string getInfo(mytreenode* r)
	{
		if (r->parent == NULL)
		{
			return "根";
		}
		else if (r->parent->left == r)
		{
			return "左";
		}
		else
		{
			return "右";
		}
	}

	//先序遍历打印二叉树
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

	//执行zig的旋转方法
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

	//执行zag的旋转方法
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

	//插入节点的方法
	void insert(char c)
	{
		mytreenode* newNode = new mytreenode(c);
		if (root == NULL)
		{
			root = newNode;
			return;
		}

		//从根节点开始找位置
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
		doubleLayerExtension(newNode, "插入", false);
		//singlelayerExtension(newNode);
	}

	//搜素指定字符的方法
	mytreenode* serach(char c)
	{
		// 当前节点
		mytreenode* curr = root;
		while (true)
		{
			if (curr == NULL)
			{
				//cout << "没有找到，搜索次数为" << count << endl;
				return NULL;
			}
			else if (c == curr->data)
			{
				//cout << "成功找到，搜索次数为" << count << endl;
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
		doubleLayerExtension(curr, "查找", true);
		return curr;
	}

	//双层伸展的方法
	void doubleLayerExtension(mytreenode* curr, string action, bool isPrint)
	{
		if (isPrint)
		{
			cout << "刚刚" << action << curr->data << "完成" << endl;
			printTree(root, 0, curr);
			cout << "--------------------------------------" << endl;
		}

		//若不是根节点就要继续迭代
		while (curr->parent != NULL)
		{
			//若是左子且只有一层到顶
			if (curr->parent->left == curr&&curr->parent->parent == NULL)
			{
				if (isPrint)
				{
					cout << "zig " << curr->parent->data << endl;
					cout << "----------" << endl;
				}
				//执行zig旋转
				zig(curr->parent);
			}
			else if (curr->parent->right == curr&&curr->parent->parent == NULL)
			{
				//若是右子且只有一层到顶
				  //执行zag旋转
				if (isPrint)
				{
					cout << "zag " << curr->parent->data << endl;
					cout << "----------" << endl;
				}
				zag(curr->parent);
			}
			else if (curr->parent->left == curr&&curr->parent->parent->left == curr->parent)
			{
				//若是左左的情况
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
				//若是右右的情况
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
				//若是右左的情况
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
				//若是左右的情况
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




	/*//逐层伸展的方法
	void singlelayerExtension(mytreenode* curr)
	{
		cout << "刚刚插入" << curr->data << "完成" << endl;
		printTree(root, 0, curr);
		cout << "-----------------------------------------" << endl;
		//若不是根节点就要继续迭代
		while (curr->parent != NULL)
		{
			//若是左子
			if (curr->parent->left == curr)
			{
				//执行zig旋转
				cout << "zig " << curr->parent->data << endl;
				cout << "----------" << endl;
				zig(curr->parent);
			}
			else
			{
				//若是右子
				  //执行zag旋转
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

	//编织节点间的父子关系
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
	//构建二叉搜索树（空）
	myBinarySearchTree mbst(NULL);

	//初始插入序列
	char init[5] = { '1', '2', '3', '4', '5' };

	//依次插入
	for (int i = 0; i < 5; i++)
	{
		mbst.insert(init[i]);
	}
	cout << "原始树" << endl;
	mbst.printTree(mbst.root, 0, NULL);
	cout << "======================================" << endl;
	//查找1
	cout << "查找1" << endl;
	mbst.serach('1');
	//查找3
	cout << "查找3" << endl;
	mbst.serach('3');

	/*
	//构建二叉搜索树
	myBinarySearchTree mbst(D);
	//打印树
	cout << "初始时" << endl;
	mbst.printTree(mbst.root, 0, NULL);
	cout << "==================================" << endl;
	//插入E
	mbst.insert('E');
    */
	return 0;
}