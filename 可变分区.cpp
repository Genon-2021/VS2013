#include<iostream>
#include<stdlib.h>
using namespace std;

#define Free 0 //����״̬
#define Busy 1 //����״̬
#define OK 1    //���
#define ERROR 0 //����
#define max_length 890 //�������������Ϣ640KB
typedef int Status;
int flag;//��־λ  0Ϊ������     1Ϊ�ѷ���Ĺ�����

typedef struct FreAarea//����һ��������˵����ṹ
{
	long size;   //������С
	long address; //������ַ
	int state;   //״̬
}ElemType;


typedef struct DuLNode// ���Ա��˫������洢�ṹ
{
	ElemType data;
	struct DuLNode *prior; //ǰ��ָ��
	struct DuLNode *next;  //���ָ��
}


DuLNode, *DuLinkList;
DuLinkList block_first; //ͷ���
DuLinkList block_last;  //β���
DuLinkList block_curr;//��ǰ�ڵ�

Status Alloc(int);//�ڴ����
Status free(int); //�ڴ����
Status First_fit(int);//�״���Ӧ�㷨
Status Best_fit(int); //�����Ӧ�㷨
Status Worst_fit(int); //�����Ӧ�㷨
Status Next_fit(int);//ѭ���״���Ӧ�㷨
Status Initblock();//�����ռ�� 
void show();//�鿴����


Status Initblock()//������ͷ�����ڴ�ռ�����
{
	block_first = (DuLinkList)malloc(sizeof(DuLNode));//����ͷ�ڵ�ռ�
	block_last = (DuLinkList)malloc(sizeof(DuLNode));//����β�ڵ�ռ�
	//ͷβ�ڵ��ʼ��
	block_first->prior = NULL;
	block_first->next = block_last;
	block_last->prior = block_first;
	block_last->next = NULL;
	block_last->data.address = 0;
	block_last->data.size = max_length;
	block_last->data.state = Free;
	//��ǰ�ڵ��ʼ��
	block_curr = block_first->next;
	return OK;
}


Status Alloc(int ch)//��������
{
	int request = 0;
	cout << "��������Ҫ����������С(��λ:KB)��" << endl;
	cin >> request;
	if (request<0 || request == 0)
	{
		cout << "�����С�����ʣ������ԣ�" << endl;
		return ERROR;
	}

	if (ch == 2) //ѡ�������Ӧ�㷨
	{
		if (Best_fit(request) == OK) cout << "����ɹ���" << endl;
		else cout << "�ڴ治�㣬����ʧ�ܣ�" << endl;
		return OK;
	}
	if (ch == 3) //ѡ�������Ӧ�㷨
	{
		if (Worst_fit(request) == OK) cout << "����ɹ���" << endl;
		else cout << "�ڴ治�㣬����ʧ�ܣ�" << endl;
		return OK;
	}
	if (ch == 4)//ѡ��ѭ���״���Ӧ�㷨
	{
		if (Next_fit(request) == OK) cout << "����ɹ���" << endl;
		else cout << "�ڴ治�㣬����ʧ�ܣ�" << endl;
		return OK;
	}
	else //Ĭ���״���Ӧ�㷨
	{
		if (First_fit(request) == OK) cout << "����ɹ���" << endl;
		else cout << "�ڴ治�㣬����ʧ�ܣ�" << endl;
		return OK;
	}
}

Status First_fit(int request)//�״���Ӧ�㷨
{
	//Ϊ������ҵ�����¿ռ��ҳ�ʼ��
	DuLinkList temp = (DuLinkList)malloc(sizeof(DuLNode));
	temp->data.size = request;
	temp->data.state = Busy;

	DuLNode *p = block_first->next;
	while (p)
	{
		if (p->data.state == Free && p->data.size == request)
		{//�д�Сǡ�ú��ʵĿ��п�
			p->data.state = Busy;
			return OK;
			break;
		}
		if (p->data.state == Free && p->data.size>request)
		{//�п��п���������������ʣ��
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


Status Best_fit(int request)//�����Ӧ�㷨
{
	int ch; //��¼��Сʣ��ռ�
	DuLinkList temp = (DuLinkList)malloc(sizeof(DuLNode));
	temp->data.size = request;
	temp->data.state = Busy;
	DuLNode *p = block_first->next;
	DuLNode *q = NULL; //��¼��Ѳ���λ��

	while (p) //��ʼ����С�ռ�����λ��
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

	if (q == NULL) return ERROR;//û���ҵ����п�
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



Status Worst_fit(int request)//�����Ӧ�㷨
{
	int ch; //��¼���ʣ��ռ�
	DuLinkList temp = (DuLinkList)malloc(sizeof(DuLNode));
	temp->data.size = request;
	temp->data.state = Busy;
	DuLNode *p = block_first->next;
	DuLNode *q = NULL; //��¼��Ѳ���λ��

	while (p) //��ʼ�����ռ�����λ��
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

	if (q == NULL) return ERROR;//û���ҵ����п�
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

Status Next_fit(int request)//ѭ���״���Ӧ�㷨
{
	//Ϊ������ҵ�����¿ռ��ҳ�ʼ��
	DuLinkList temp = (DuLinkList)malloc(sizeof(DuLNode));
	temp->data.size = request;
	temp->data.state = Busy;

	DuLNode *p = block_curr;

	cout << "W�⵱ǰλ��:" << p->data.address << endl;
	while (p)
	{
		cout << "��ǰλ��:" << p->data.address << endl;
		if (p->data.state == Free && p->data.size == request)
		{//�д�Сǡ�ú��ʵĿ��п�
			p->data.state = Busy;
			block_curr = p;
			return OK;
			break;
		}
		if (p->data.state == Free && p->data.size>request)
		{//�п��п���������������ʣ��
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



Status free(int flag)//�������
{
	DuLNode *p = block_first;
	for (int i = 0; i <= flag; i++)
		if (p != NULL)
			p = p->next;
		else
			return ERROR;

	p->data.state = Free;
	if (p->prior != block_first && p->prior->data.state == Free)//��ǰ��Ŀ��п�����
	{
		p->prior->data.size += p->data.size;//�ռ�����,�ϲ�Ϊһ��
		p->prior->next = p->next;//ȥ��ԭ�����ϲ���p
		p->next->prior = p->prior;
		p = p->prior;
	}
	if (p->next != block_last && p->next->data.state == Free)//�����Ŀ��п�����
	{
		p->data.size += p->next->data.size;//�ռ�����,�ϲ�Ϊһ��
		p->next->next->prior = p;
		p->next = p->next->next;
	}
	if (p->next == block_last && p->next->data.state == Free)//�����Ŀ��п�����
	{
		p->data.size += p->next->data.size;
		p->next = NULL;
	}

	return OK;
}


void show()//��ʾ����������
{
	int flag = 0;
	cout << "\n����������:\n";
	cout << "==============================================\n\n";
	DuLNode *p = block_first->next;
	cout << "������\t��ʼ��ַ\t������С\t״̬\n\n";
	while (p)
	{
		cout << "  " << flag++ << "\t";
		cout << "  " << p->data.address << "\t\t";
		cout << " " << p->data.size << "KB\t\t";
		if (p->data.state == Free) cout << "����\n\n";
		else cout << "�ѷ���\n\n";
		p = p->next;
	}
	cout << "==============================================\n\n";
}


int main()//������
{
	int ch;//�㷨ѡ����
	cout << "��������ʹ�õ��ڴ�����㷨��\n";
	cout << "(1)�״���Ӧ�㷨\n(2)�����Ӧ�㷨\n(3)�����Ӧ�㷨\n(4)ѭ���״���Ӧ�㷨\n";

	cin >> ch;
	while (ch<1 || ch>4)
	{
		cout << "�������������������ʹ�õ��ڴ�����㷨��\n";
		cin >> ch;
	}

	Initblock(); //�����ռ��
	int choice;  //����ѡ����

	while (1)
	{
		show();
		cout << "���������Ĳ�����";
		cout << "\n1: �����ڴ�\n2: �����ڴ�\n0: �˳�\n";

		cin >> choice;
		if (choice == 1) Alloc(ch); // �����ڴ�
		else if (choice == 2)  // �ڴ����
		{
			int flag;
			cout << "��������Ҫ�ͷŵķ����ţ�" << endl;
			cin >> flag;
			free(flag);
		}
		else if (choice == 0) break; //�˳�
		else //�����������
		{
			cout << "�������������ԣ�" << endl;
			continue;
		}
	}
}