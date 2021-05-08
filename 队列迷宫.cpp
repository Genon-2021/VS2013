#include<iostream>
#include<stdio.h>
#include "myqueue.h"
#include "mazemap.h"

using namespace std;

//�Ƿ��Ѿ����ʹ��ı�־����
bool flag[size][size];

//��¼·���Ķ�������
myqueue<int*>* path[size][size];

//��ʼ����־���鼰·����������
void init()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			flag[i][j] = false;
			path[i][j] = NULL;
		}
	}
}

//����Թ�
void outputmaze(myqueue<int*>* path)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (map[i][j] == 0)
			{
				printf("��");
			}
			else if (map[i][j] == 2)
			{
				printf(" E");
			}
			else if (i==start[0]&&j==start[1])
			{
				printf("S ");
			}
			else if (path != NULL)
			{
				bool isin = false;
				for (int k = 0; k < path->count; k++)
				{
					int* cp = path->array[k];
					if (cp[0] == i&&cp[1] == j)
					{
						isin = true;
						break;
					}
				}
				if (isin)
				{
					printf("��");
				}
				else
				{
					printf("  ");
				}
			}
			else
			{
				printf("  ");
			}
			
		}
		printf("\n");
	}
}

//�����ֵ�ķ���
bool myabs(int a)
{
	return a > 0 ? a : -a;
}

int main(int argc, char *argv[])
{
	printf("��ʼ���Թ�\n");
	outputmaze(NULL);
	printf("====================================\n");
	init();
	myqueue<int*> test;
	test.add(start);
	path[start[0]][start[1]] = new myqueue<int*>();
	path[start[0]][start[1]]->add(start);
	flag[start[0]][start[1]] = true;
	while (true)
	{
		int* point = test.serve();
		int currRow = point[0];
		int currCol = point[1];

		//������Χ4�����ܵ�λ��
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				if (myabs(i) == myabs(j))continue;
				//�õ�Ҫ����λ�õ����к�
				int testRow = currRow + i;
				int testCol = currCol + j;
				if (testRow < 0 || testRow >= size || testCol<0 || testCol>size)
				{
					continue;
				}
				if (map[testRow][testCol] == 0) continue;
				if (flag[testRow][testCol] == true) continue;
				if (map[testRow][testCol] == 2)
				{
					//ȡ����ǰ��·��
					myqueue<int*>* resultPath = path[currRow][currCol];
					//���յ����·��
					resultPath->add(new int[2]{testRow, testCol});
					printf("�ҵ���·��\n");
					//��ӡ·��
					for (int k = 0; k < resultPath->count; k++)
					{
						//ȡ��һ��·����
						int* tp = resultPath->array[k];
						//��ӡ��Ϣ
						if (k != resultPath->count - 1)
						{
							printf("%d:%d->", tp[0], tp[1]);
						}
						else
						{
							printf("%d:%d\n", tp[0], tp[1]);
						}
					}
					printf("====================================\n");
					printf("��·�����Թ�\n");
					outputmaze(resultPath);
					printf("====================================\n");
					return 0;
				}
				int* cp = new int[2]{testRow, testCol};
				test.add(cp);
				flag[testRow][testCol] = true;
				myqueue<int*>* currPath = path[currRow][currCol];
				myqueue<int*>* testPath = new myqueue<int*>();
				path[testRow][testCol] = testPath;
				for (int k = 0; k <currPath->count; k++)
				{
					testPath->add(currPath->array[k]);
				}
				testPath->add(cp);
			}
		}
	}
	return 0;
}