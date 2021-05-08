#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sstream>
#include<vector>
#include<map>
#include<windows.h>

using namespace std;

template <class T>
class mystack
{
public:
	T array[100];
	int topindex = 0;

	bool isEmpty()
	{
		return topindex == 0;
	}

	void push(T n)
	{
		array[topindex] = n;
		topindex++;
	}

	T pop()
	{
		if (isEmpty()) return NULL;
		topindex--;
		return array[topindex];
	}

	T top()
	{
		if (isEmpty()) return NULL;
		return array[topindex - 1];
	}
};

#define MAP_SIZE 5
//��ͼ���� //0����ͨ�� 1��ͨ�� 2Ҫ�ҵ�λ�� 3��ʼλ�� 4·����
int mapStatue[MAP_SIZE][MAP_SIZE] =
{
	{ 3, 1, 1, 0, 0 },
	{ 0, 0, 1, 0, 0 },
	{ 0, 0, 1, 1, 2 },
	{ 1, 1, 1, 0, 0 },
	{ 0, 0, 1, 1, 1 }
};

//���Ƶ�ͼ
void drawMap(int mapData[MAP_SIZE][MAP_SIZE], int visited[MAP_SIZE][MAP_SIZE], bool isNotPath)
{
	//����
	if (isNotPath) system("cls");
	//��������
	for (int i = -1; i < MAP_SIZE + 1; i++)
	{
		for (int j = -1; j < MAP_SIZE + 1; j++)
		{
			if (i== -1 || j== -1 || i == MAP_SIZE || j == MAP_SIZE)
			{
				printf("�� ");
			}
			else if (mapData[i][j] == 3)
			{
				printf(":: ");
			}
			else if (visited[i][j] == 1 && isNotPath)
			{
				printf("<> ");
			}
			else if (mapData[i][j] == 1)
			{
				printf("   ");
			}
			else if (mapData[i][j] == 0)
			{
				printf("�� ");
			}
			else if (mapData[i][j] == 2)
			{
				printf("�� ");
			}
			else if (mapData[i][j] == 4)
			{
				printf("[] ");
			}
		}
		printf("\n");
	}
}

//ÿһ������Ϣ�ĺ�����
#define SLEEP_MS 1000

string fromIntToString(int a)
{
	string res;
	stringstream ss;
	ss << a;
	ss >> res;
	return res;
}

//վ��һ��λ�ã������������ĸ�λ�õ�����ƫ����
//��������˳ʱ����ջ�������濪ʼ
//		0
//	  3 # 1
//		2
int sequence[4][2]=
{
	{ 0, -1 }, { 1, 0 }, { 0,1 }, {-1,0}
};

int main(int argc, char *argv[])
{
	//���·����¼
	std::map<string, int*> hm;
	//�����������ջ
	mystack<int*> stack;
	//��¼����״̬������ 0δȥ�� 1ȥ��
	int visited[MAP_SIZE][MAP_SIZE];
	memset(visited, 0, MAP_SIZE*MAP_SIZE*sizeof(int));
	//�Ƿ���������ı�־λ
	bool flag = true;
	//��ʼ�� ��0:0�㵽0:0��
	int start[4] = { 0, 0, 0, 0 };
	//����ʼ�߷���ջ
	stack.push(start);

	//�����������
	int endCol;
	int endRow;

	while (flag)
	{
		//��ջ��ȡ��һ����
		int* currentEdge = stack.pop();
		//ȡ���˱ߵ�Ŀ�ĵ�
		int tempTarget[2] = { currentEdge[2], currentEdge[3] };
		//�ж�Ŀ�ĵ��Ƿ�ȥ������ȥ����ֱ�ӽ����´�ѭ��
		if (visited[tempTarget[1]][tempTarget[0]]== 1)
		{
			continue;
		}

		//��ʶĿ�ĵ�Ϊ���ʹ�
		visited[tempTarget[1]][tempTarget[0]] = 1;

		//��¼����˵����һ����
		hm[fromIntToString(tempTarget[1]) + ":"+fromIntToString(tempTarget[0])]=
		new int[2]{currentEdge[1], currentEdge[0]};

		//����SLEEP_MS�����Ա�۲����
		Sleep(SLEEP_MS);
		//�ж��з��ҵ�Ŀ�ĵ�
		if (mapStatue[tempTarget[1]][tempTarget[0]] == 2)
		{
			endCol = tempTarget[0];
			endRow = tempTarget[1];
			break;
		}

		//�����п��ܵı���ջ
		int currCol = tempTarget[0];
		int currRow = tempTarget[1];
		//������ǰλ����Χ���ܵ��ĸ�λ��
		for (int k = 0; k < 4; k++)
		{
			//��ȡ��ǰƫ����
			int* rc = sequence[k];
			//ȡ������ƫ����
			int i = rc[1];
			int j = rc[0];
			//����ǰƫ������Ӧ��ͼλ�ÿ���ͨ��
			if (currRow + i >= 0 && currRow + i < MAP_SIZE&&currCol + j >= 0 && currCol + j < MAP_SIZE&&mapStatue[currRow + i][currCol + j] != 0)
			{
				int* tempEdge = new int[4]
				{
					currCol, currRow, currCol + j, currRow + i
				};
				stack.push(tempEdge);
			}
		}
		drawMap(mapStatue, visited, true);
	}

	//���ڴ���ҵ���·����ջ
	mystack<string> pathStr;
	//��ǰλ�ã������㣩�����ַ���
	string currP = fromIntToString(endRow) + ":" + fromIntToString(endCol);
	//�����¼��ջ��
	pathStr.push(currP);
	//���ϵ���ֱ���ص����
	while (true)
	{
		//ȡ����ǰ�����һ����
		int* tempP = hm[currP];
		currP = fromIntToString(tempP[0]) + ":" + fromIntToString(tempP[1]);
		//����ͼ�еĴ�λ���޸�Ϊ4����ʾ��·����
		if (mapStatue[tempP[0]][tempP[1]] == 1)
		{
			mapStatue[tempP[0]][tempP[1]] = 4;
		}
		//�����¼��ջ��
		pathStr.push(currP);
		//����Ѿ������������ֹ����
		if (tempP[0] == 0 && tempP[1] == 0)
		{
			break;
		}
	}

	cout << "==========================================" << endl;
	int count = 0;
	while (!pathStr.isEmpty())
	{
		count++;
		cout << pathStr.pop() << "->";
		if (count == 10)
		{
			count = 0;
			cout << endl;
		}
	}
	cout << "Finish" << endl;
	cout << "=========================================="<<endl;
	//�����ҵ���·��
	drawMap(mapStatue, visited, false);
	return 0;

}