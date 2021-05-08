#include<iostream>
#include<stdlib.h>
using namespace std;

#define Free 0 //空闲状态
#define Busy 1 //已用状态
#define OK 1    //完成
#define ERROR 0 //出错
#define max_length 890 //定义最大主存信息640KB
typedef int Status;
int flag;//标志位  0为空闲区     1为已分配的工作区

typedef struct FreAarea//定义一个空闲区说明表结构
{
	long size;   //分区大小
	long address; //分区地址
	int state;   //状态
}ElemType;


typedef struct DuLNode// 线性表的双向链表存储结构
{
	ElemType data;
	struct DuLNode *prior; //前趋指针
	struct DuLNode *next;  //后继指针
}


DuLNode, *DuLinkList;
DuLinkList block_first; //头结点
DuLinkList block_last;  //尾结点
DuLinkList block_curr;//当前节点

Status Alloc(int);//内存分配
Status free(int); //内存回收
Status First_fit(int);//首次适应算法
Status Best_fit(int); //最佳适应算法
Status Worst_fit(int); //最差适应算法
Status Next_fit(int);//循环首次适应算法
Status Initblock();//开创空间表 
void show();//查看分配


Status Initblock()//开创带头结点的内存空间链表
{
	block_first = (DuLinkList)malloc(sizeof(DuLNode));//开创头节点空间
	block_last = (DuLinkList)malloc(sizeof(DuLNode));//开创尾节点空间
	//头尾节点初始化
	block_first->prior = NULL;
	block_first->next = block_last;
	block_last->prior = block_first;
	block_last->next = NULL;
	block_last->data.address = 0;
	block_last->data.size = max_length;
	block_last->data.state = Free;
	//当前节点初始化
	block_curr = block_first->next;
	return OK;
}


Status Alloc(int ch)//分配主存
{
	int request = 0;
	cout << "请输入需要分配的主存大小(单位:KB)：" << endl;
	cin >> request;
	if (request<0 || request == 0)
	{
		cout << "分配大小不合适，请重试！" << endl;
		return ERROR;
	}

	if (ch == 2) //选择最佳适应算法
	{
		if (Best_fit(request) == OK) cout << "分配成功！" << endl;
		else cout << "内存不足，分配失败！" << endl;
		return OK;
	}
	if (ch == 3) //选择最差适应算法
	{
		if (Worst_fit(request) == OK) cout << "分配成功！" << endl;
		else cout << "内存不足，分配失败！" << endl;
		return OK;
	}
	if (ch == 4)//选择循环首次适应算法
	{
		if (Next_fit(request) == OK) cout << "分配成功！" << endl;
		else cout << "内存不足，分配失败！" << endl;
		return OK;
	}
	else //默认首次适应算法
	{
		if (First_fit(request) == OK) cout << "分配成功！" << endl;
		else cout << "内存不足，分配失败！" << endl;
		return OK;
	}
}

Status First_fit(int request)//首次适应算法
{
	//为申请作业开辟新空间且初始化
	DuLinkList temp = (DuLinkList)malloc(sizeof(DuLNode));
	temp->data.size = request;
	temp->data.state = Busy;

	DuLNode *p = block_first->next;
	while (p)
	{
		if (p->data.state == Free && p->data.size == request)
		{//有大小恰好合适的空闲块
			p->data.state = Busy;
			return OK;
			break;
		}
		if (p->data.state == Free && p->data.size>request)
		{//有空闲块能满足需求且有剩余
			temp->prior = p->prior;
			temp->next = p;
			temp->data.address = p->data.address;
			p->prior->next = temp;
			p->prior = temp;
			p->data.address = temp->data.address + temp->data.size;
			p->data.size -= request;
			return OK;
			break;
		}
		p = p->next;
	}
	return ERROR;
}


Status Best_fit(int request)//最佳适应算法
{
	int ch; //记录最小剩余空间
	DuLinkList temp = (DuLinkList)malloc(sizeof(DuLNode));
	temp->data.size = request;
	temp->data.state = Busy;
	DuLNode *p = block_first->next;
	DuLNode *q = NULL; //记录最佳插入位置

	while (p) //初始化最小空间和最佳位置
	{
		if (p->data.state == Free && (p->data.size >= request))
		{
			if (q == NULL)
			{
				q = p;
				ch = p->data.size - request;
			}
			else if (q->data.size > p->data.size)
			{
				q = p;
				ch = p->data.size - request;
			}
		}
		p = p->next;
	}

	if (q == NULL) return ERROR;//没有找到空闲块
	else if (q->data.size == request)
	{
		q->data.state = Busy;
		return OK;
	}
	else
	{
		temp->prior = q->prior;
		temp->next = q;
		temp->data.address = q->data.address;
		q->prior->next = temp;
		q->prior = temp;
		q->data.address += request;
		q->data.size = ch;
		return OK;
	}
	return OK;
}



Status Worst_fit(int request)//最差适应算法
{
	int ch; //记录最大剩余空间
	DuLinkList temp = (DuLinkList)malloc(sizeof(DuLNode));
	temp->data.size = request;
	temp->data.state = Busy;
	DuLNode *p = block_first->next;
	DuLNode *q = NULL; //记录最佳插入位置

	while (p) //初始化最大空间和最佳位置
	{
		if (p->data.state == Free && (p->data.size >= request))
		{
			if (q == NULL)
			{
				q = p;
				ch = p->data.size - request;
			}
			else if (q->data.size < p->data.size)
			{
				q = p;
				ch = p->data.size - request;
			}
		}
		p = p->next;
	}

	if (q == NULL) return ERROR;//没有找到空闲块
	else if (q->data.size == request)
	{
		q->data.state = Busy;
		return OK;
	}
	else
	{
		temp->prior = q->prior;
		temp->next = q;
		temp->data.address = q->data.address;
		q->prior->next = temp;
		q->prior = temp;
		q->data.address += request;
		q->data.size = ch;
		return OK;
	}
	return OK;
}

Status Next_fit(int request)//循环首次适应算法
{
	//为申请作业开辟新空间且初始化
	DuLinkList temp = (DuLinkList)malloc(sizeof(DuLNode));
	temp->data.size = request;
	temp->data.state = Busy;

	DuLNode *p = block_curr;

	cout << "W外当前位置:" << p->data.address << endl;
	while (p)
	{
		cout << "当前位置:" << p->data.address << endl;
		if (p->data.state == Free && p->data.size == request)
		{//有大小恰好合适的空闲块
			p->data.state = Busy;
			block_curr = p;
			return OK;
			break;
		}
		if (p->data.state == Free && p->data.size>request)
		{//有空闲块能满足需求且有剩余
			temp->prior = p->prior;
			temp->next = p;
			temp->data.address = p->data.address;
			p->prior->next = temp;
			p->prior = temp;
			p->data.address = temp->data.address + temp->data.size;
			p->data.size -= request;
			block_curr = p;
			return OK;
			break;
		}
		if (p->data.state)
			p = p->next;
	}
}



Status free(int flag)//主存回收
{
	DuLNode *p = block_first;
	for (int i = 0; i <= flag; i++)
		if (p != NULL)
			p = p->next;
		else
			return ERROR;

	p->data.state = Free;
	if (p->prior != block_first && p->prior->data.state == Free)//与前面的空闲块相连
	{
		p->prior->data.size += p->data.size;//空间扩充,合并为一个
		p->prior->next = p->next;//去掉原来被合并的p
		p->next->prior = p->prior;
		p = p->prior;
	}
	if (p->next != block_last && p->next->data.state == Free)//与后面的空闲块相连
	{
		p->data.size += p->next->data.size;//空间扩充,合并为一个
		p->next->next->prior = p;
		p->next = p->next->next;
	}
	if (p->next == block_last && p->next->data.state == Free)//与最后的空闲块相连
	{
		p->data.size += p->next->data.size;
		p->next = NULL;
	}

	return OK;
}


void show()//显示主存分配情况
{
	int flag = 0;
	cout << "\n主存分配情况:\n";
	cout << "==============================================\n\n";
	DuLNode *p = block_first->next;
	cout << "分区号\t起始地址\t分区大小\t状态\n\n";
	while (p)
	{
		cout << "  " << flag++ << "\t";
		cout << "  " << p->data.address << "\t\t";
		cout << " " << p->data.size << "KB\t\t";
		if (p->data.state == Free) cout << "空闲\n\n";
		else cout << "已分配\n\n";
		p = p->next;
	}
	cout << "==============================================\n\n";
}


int main()//主函数
{
	int ch;//算法选择标记
	cout << "请输入所使用的内存分配算法：\n";
	cout << "(1)首次适应算法\n(2)最佳适应算法\n(3)最差适应算法\n(4)循环首次适应算法\n";

	cin >> ch;
	while (ch<1 || ch>4)
	{
		cout << "输入错误，请重新输入所使用的内存分配算法：\n";
		cin >> ch;
	}

	Initblock(); //开创空间表
	int choice;  //操作选择标记

	while (1)
	{
		show();
		cout << "请输入您的操作：";
		cout << "\n1: 分配内存\n2: 回收内存\n0: 退出\n";

		cin >> choice;
		if (choice == 1) Alloc(ch); // 分配内存
		else if (choice == 2)  // 内存回收
		{
			int flag;
			cout << "请输入您要释放的分区号：" << endl;
			cin >> flag;
			free(flag);
		}
		else if (choice == 0) break; //退出
		else //输入操作有误
		{
			cout << "输入有误，请重试！" << endl;
			continue;
		}
	}
}