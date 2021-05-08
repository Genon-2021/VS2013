#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <time.h>
using namespace std;

const int N = 12000;
int init[N];

//自定义一个树类
class mytreenode{
public:
	int data;
	mytreenode* left;	//左子
	mytreenode* right;	//右子
	mytreenode* parent;	//父节点
	int height;			//树高

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

		cout << r->data << "[" << getInfo(r) << ",高度:" << r->height << ",平衡值:" << abs(calBalance(r)) << "]" << endl;
		printTree(r->left, level + 1);
		printTree(r->right, level + 1);
	}

	//从指定节点向上所有节点高度各自减1的方法
	void decreaseHeight(mytreenode* curr)
	{
		curr = curr->parent;
		while (curr != NULL)
		{
			curr->height = curr->height - 1;
			curr = curr->parent;
		}
	}

	//更新指定节点高度的方法
	void updateHeight(mytreenode* r)
	{
		//获取当前节点左子树的高度
		int leftHeight = (r->left == NULL) ? (-1) : (r->left->height);
		//获取当前节点右子树的高度
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

	//从此节点往上所有祖先节点及此节点的高度更新的方法
	void updateHeightCascade(mytreenode* curr)
	{
		while (curr != NULL)
		{
			updateHeight(curr);
			curr = curr->parent;
		}
	}

	//计算指定节点平衡参数的方法
	int calBalance(mytreenode* r)
	{
		//获取当前节点左子树的高度
		int leftHeight = (r->left == NULL) ? (-1) : (r->left->height);
		//获取当前节点右子树的高度
		int rightHeight = (r->right == NULL) ? (-1) : (r->right->height);
		return leftHeight - rightHeight;
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

	//执行zag的旋转方法
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

	
	//插入结点的方法
	void insert(int c)
	{
		mytreenode* newNode = new mytreenode(c);
		if (root == NULL)
		{
			root = newNode;
			//打印平衡前的情况
			cout << "----------------平衡前的情况----------------" << endl;
			printTree(root, 0);
			cout << "--------------------------------------------" << endl;
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
					//若新节点挂入的节点原来是叶子节点
					if (curr->left == NULL)
					{
						//从此节点往上所有祖先节点及此节点的高度更新
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
					//若新节点挂入的节点原来是叶子节点
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
		
		//打印平衡前的情况
		cout << "----------------平衡前的情况----------------" << endl;
		printTree(root, 0);
		cout << "--------------------------------------------" << endl;
		//对插入后的二叉树进行在平衡
		bool need = rebalance(newNode);
		if (!need)
		{
			return;
		}
		//打印平衡后情况
		cout << "----------------平衡后的情况----------------" << endl;
		printTree(root, 0);
		cout << "--------------------------------------------" << endl;
	}
	
	bool rebalance(mytreenode* temp)
	{
		//用于记录新节点到最下层失衡节点的路径
		vector<mytreenode*> path;

		//从新插入的节点往祖先方向开始寻找最靠下面的失衡节点
		int balance = 0;
		//从当前节点逐级向上寻找最下层的失衡节点
		while (temp != NULL)
		{
			//将各个节点计录到路径中
			path.push_back(temp);
			//计算出平衡因子
			balance = calBalance(temp);
			//若失衡终止迭代
			if (abs(balance) >= 2)
			{
				break;
			}
			temp = temp->parent;
		}
		//若找到则记录最下层的失衡节点
		if (temp != NULL)
		{
			mytreenode* g = temp;
			mytreenode* p = path[path.size() - 2];
			mytreenode* v = path[path.size() - 3];

			//若是zag单旋情况
			if (g->right == p&&p->right == v)
			{
				cout << "zag单旋" << endl;
				zag(g);
				//从p向上所有的节点高度减1
				decreaseHeight(p);
				//更新g的高度
				updateHeight(g);
				//更新p的高度
				updateHeight(p);
			}
			//若是zig单旋
			else if (g->left == p&&p->left == v)
			{
				cout << "zig单旋" << endl;
				zig(g);
				//从p向上所有的节点高度减1
				decreaseHeight(p);
				//更新g的高度
				updateHeight(g);
				//更新p的高度
				updateHeight(p);
			}
			//若是zig-zag双旋情况
			else if (g->right == p&&p->left == v)
			{
				cout << "zig-zag双旋" << endl;
				zig(p);
				zag(g);
				//从v向上所有的节点高度减1
				decreaseHeight(v);
				//更新g的高度
				updateHeight(g);
				//更新p的高度
				updateHeight(p);
				//更新v的高度
				updateHeight(v);
			}
			//若是zag-zig双旋情况
			else
			{
				cout << "zag-zig双旋" << endl;
				zag(p);
				zig(g);
				//从v向上所有的节点高度减1
				decreaseHeight(v);
				//更新g的高度
				updateHeight(g);
				//更新p的高度
				updateHeight(p);
				//更新v的高度
				updateHeight(v);
			}
			return true;
		}

	}
	
	
	//搜索指定字符的方法
	mytreenode* search(char c)
	{
		int count = 0;
		mytreenode* curr = root;
		while (true)
		{
			count++;
			if (curr == NULL)
			{
				cout << "没有找到，搜索次数为" << count << endl;
				return NULL;
			}
			else if (c == curr->data)
			{
				cout << "成功找到，搜索次数为" << count << endl;
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

	//遍历由二叉树实现的有序列表的方法
	void traverse(void(*process) (mytreenode*))
	{
		mytreenode* curr = root;
		traverseInner(curr, process);
		cout << "nil" << endl;
	}
	
};

//遍历时处理一个节点的方法
void task(mytreenode* curr)
{
	cout << curr->data << "(" << curr->height << ")->";
}

int main(int argc, char *argv[])
{
	//构建空的二叉搜索树
	myBinarySearchTree mbst(NULL);

	//初始插入序列
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

	//依次插入
	start = clock();
	for (int i = 0; i < N; i++)
	{
		//cout << "\n===========================插入" << init[i] << "==========================" << endl;
		mbst.insert(init[i]);
		//cout << "===============================================" << endl;

	}
	end = clock();
	cout << "Run Time:" << end - start << endl;

	//执行像列表一样的遍历
	//cout << "======遍历由二叉树实现的有序列表======" << endl;
	//mbst.traverse(task);

	//进行搜索
	//cout << "======搜索指定内容的元素======" << endl;
	//cout << "搜索D" << endl;
	//mbst.search('D');
	//cout << "搜索H" << endl;
	//mbst.search('H');
	//cout << "搜索G（不存在，最差情况）" << endl;
	//mbst.search('G');

	//插入一个元素
	//cout << "==========插入元素==========" << endl;
	//cout << "-----------插入13------------" << endl;
	//mbst.insert('13');
	//cout << "-----------插入I------------" << endl;
	//mbst.insert('I');
	//cout << "======搜索指定内容的元素======" << endl;
	//cout << "搜索G" << endl;
	//mbst.search('G');
	//cout << "======遍历由二叉树实现的有序列表======" << endl;
	//mbst.traverse(task);
	system("pause");
	return 0;
}