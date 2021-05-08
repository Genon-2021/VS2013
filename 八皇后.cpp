#include<iostream>
//#include<stdio.h>
//#include<stdlib.h>
#include<windows.h>

using namespace std;

#define NEED_DRAW//�Ƿ�������� 
#define STEP_SLEEP 20//ÿһ��������ʱ�� 
#define ANSWER_SLEEP 5000//ÿ�ҵ�һ���������ʱ�� 

//���̳ߴ�
#define N 8 
//��ŵ�ÿһ�лʺ������
int location[N + 1];

//���Ƶ�ǰ���̵ķ���
void drawBoard(int currRow)
{
#ifdef NEED_DRAW
	//����
	system("cls");
	//��������
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			if (location[i] == j&&i <= currRow)
			{
				printf("��");
			}
			else
			{
				printf("��");
			}
		}
		printf("\n");
	}
#endif
}

//��鵱ǰ�еĻʺ��Ƿ���ǰ��ںõĻʺ��ͻ�ķ���
//����ͻ����false,��ͻ����true
bool isConflict(int currRow)
{
	//��鵱ǰ�еĻʺ��Ƿ���ǰ��ںõĻʺ��ͻ
	bool flag = false;
	//Ŀǰ��currRow�У�����ǰ��ںõĸ��еĳ�ͻ���
	for (int i = currRow - 1; i >= 1; i--)
	{
		if (location[currRow] == location[i] ||
			currRow - i == abs(location[currRow] - location[i]))
		{
			flag = true;
			break;
		}
	}
	return flag;
}

//���л��ݷ��ʺ�ڷ�
void putQueenRetro()
{
	int currRow = 1;//��ʾ��ǰ�� 
	//�ڵ�һ�е�һ�з�һ���ʺ�
	location[currRow] = 1;
	int count = 0;

	//������ѭ��
	while (true)
	{
		//�ӵ�һ�����N�г��ԷŻʺ�
		//��������
		drawBoard(currRow);
		//����ANSWER_SLEEOP����
		Sleep(STEP_SLEEP);

		//��û�г�ͻ
		if (!isConflict(currRow))
		{
			//���н���
			if (currRow == N)
			{
				count++;
				drawBoard(currRow);
				//��ӡ���=====================begin
				printf("Answer %d [", count);
				for (int i = 1; i <= N; i++)
				{
					printf("%d", location[i]);
				}
				printf("]\n");
				//��ӡ����====================end
				//����STEP_SLEEP�����Ա�۲���
				Sleep(ANSWER_SLEEP);
				//����Ѱ��������
				if (location[currRow]<N)
				{
					//����ǰû�е���N�������ƶ�һ�У������ڱ������
					location[currRow] = location[currRow] + 1;
				}
				else
				{
					//�������һ��
					//�ص���һ��
					currRow--;
					//��һ�е���������һ��
					location[currRow] = location[currRow] + 1;
				}
			}
			else
			{
				//����һ�е�һ�аڷ�һ���ʺ�
				currRow++;
				location[currRow] = 1;
			}
		}
		else
		{
			//��ͻ�������������
			//����ǰ�аڷŵ��л�û�е����һ��
			if (location[currRow]<N)
			{
				//�ڷ�λ�������ƶ�һ��
				location[currRow] = location[currRow] + 1;
			}
			else
			{
				//����ǰ�аڷŵ����Ѿ��������һ��
				//�ص���һ��
				currRow--;
				//����ǰ�аڷ�λ���Ѿ��������һ��
				while (location[currRow] == N)
				{
					//�����ص���һ��
					currRow--;
					//��û�п��õ���һ�У����򷵻�
					if (currRow<1)return;
				}
				//��ǰ�аڷŵ�λ�������ƶ�һ��
				location[currRow] = location[currRow] + 1;
			}
		}
	}
}

int main()
{
	putQueenRetro();
	return 0;
}