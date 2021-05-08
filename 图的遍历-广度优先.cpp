#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<map>
#include<Windows.h>

using namespace std;

//每一步的休息的毫秒数
#define SLEEP_MS 1000

string fromIntToString(int a)
{
	string res;
	stringstream ss;
	ss << a;
	ss >> res;
	return res;
}

//站在一个位置，可能搜索的四个位置的行列偏移量
//搜索次序顺时针入栈，从上面开始
//		0
//	  3 # 1
//		2
int sequence[4][2] =
{
	{ 0, -1 }, { 1, 0 }, { 0, 1 }, { -1, 0 }
};

#define MAP_SIZE 5
//地图数据 //0不可通过 1可通过 2要找的位置 3起始位置 4路径点
int mapStatue[MAP_SIZE][MAP_SIZE] =
{
	{ 3, 1, 1, 0, 0 },
	{ 0, 0, 1, 0, 0 },
	{ 0, 0, 1, 1, 1 },
	{ 1, 1, 1, 0, 0 },
	{ 0, 0, 1, 1, 2 }
};


#define queue_capacity 100
template <class T>
class myqueue
{
public:
	T array[queue_capacity];
	int headindex;
	int tailindex;
	int count;
	myqueue()
	{
		headindex = 0;
		tailindex = 0;
		count = 0;
	}

	bool isEmpty()
	{
		return count == 0;
	}

	bool isFull()
	{
		return count == queue_capacity;
	}

	void add(T n)
	{
		if (isFull()) return;
		array[tailindex] = n;
		tailindex++;
		tailindex = tailindex%queue_capacity;
		count++;
	}

	T serve()
	{
		if (isEmpty()) return NULL;
		T result = array[headindex];
		headindex++;
		headindex = headindex%queue_capacity;
		count--;
		return result;
	}

	T head()
	{
		if (isEmpty()) return NULL;
		return array[headindex];
	}
};

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

void drawMap(int mapData[MAP_SIZE][MAP_SIZE], int visited[MAP_SIZE][MAP_SIZE], bool isNotPath)
{
	//清屏
	if (isNotPath) system("cls");
	//绘制棋盘
	for (int i = -1; i < MAP_SIZE + 1; i++)
	{
		for (int j = -1; j < MAP_SIZE + 1; j++)
		{
			if (i == -1 || j == -1 || i == MAP_SIZE || j == MAP_SIZE)
			{
				printf("■ ");
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
				printf("■ ");
			}
			else if (mapData[i][j] == 2)
			{
				printf("★ ");
			}
			else if (mapData[i][j] == 4)
			{
				printf("[] ");
			}
		}
		printf("\n");
	}
}

int main(int argc, char *argv[])
{
	//结果路径记录
	std::map<string, int*> hm;

	myqueue<int*> queue;
	//记录访问状态的数组 0未去过 1去过
	int visited[MAP_SIZE][MAP_SIZE];
	memset(visited, 0, MAP_SIZE*MAP_SIZE*sizeof(int));
	//是否继续迭代的标志
	bool flag = true;
	//起始边 从0：0点到0：0点
	int start[4] = { 0, 0, 0, 0 };
	//将起始边放入队列
	queue.add(start);
	//结束点的行列
	int endCol = -1;
	int endRow = -1;

	while (flag)
	{
		if (queue.isEmpty()) break;

		//从队首取出一条边
		int* currenEdge = queue.serve();
		//取出此边的目的点
		int tempTarget[2] = { currenEdge[2], currenEdge[3] };
		//判断目的点是否去过，若去过则直接进入下次循环
		if (visited[tempTarget[1]][tempTarget[0]] == 1)
		{
			continue;
		}
		//标识目的点为访问过
		visited[tempTarget[1]][tempTarget[0]] = 1;

		//记录到达此点的上一个点
		hm[fromIntToString(tempTarget[1]) + ":" + fromIntToString(tempTarget[0])] =
			new int[2]{currenEdge[1], currenEdge[0]};

		//休眠SLEEP_MS毫秒以方便观察过程
		Sleep(SLEEP_MS);

		//判断有否找到目的点
		if (mapStatue[tempTarget[1]][tempTarget[0]] == 2)
		{
			endCol = tempTarget[0];
			endRow = tempTarget[1];
			break;
		}

		//将所有可能的边入队列
		int currCol = tempTarget[0];
		int currRow = tempTarget[1];
		//遍历当前位置走位可的四个位置
		for (int k = 0; k < 4; k++)
		{
			//获取当前偏移量
			int* rc = sequence[k];
			//取出行列偏移量
			int i = rc[1];
			int j = rc[0];
			//若当前偏移量对应地图位置可以通过
			if (currRow + i >= 0 && currRow + i < MAP_SIZE&&currCol + j >= 0 && currCol + j < MAP_SIZE&&mapStatue[currRow + i][currCol + j] != 0)
			{
				int* tempEdge = new int[4]
				{
					currCol, currRow, currCol + j, currRow + i
				};
				queue.add(tempEdge);
			}
		}
		drawMap(mapStatue, visited, true);
	}

	//若不存在终点，则程序直接返回
	if (endRow == -1) return 0;

	//用于存放找到的路径的栈
	mystack<string> pathStr;
	//当前位置（结束点）坐标字符串
	string currP = fromIntToString(endRow) + ":" + fromIntToString(endCol);
	//将其记录到栈中
	pathStr.push(currP);
	//不断迭代直至回到起点
	while (true)
	{
		//取出当前点的上一个点
		int* tempP = hm[currP];
		currP = fromIntToString(tempP[0]) + ":" + fromIntToString(tempP[1]);
		//将地图中的此位置修改为4，表示是路径点
		if (mapStatue[tempP[0]][tempP[1]] == 1)
		{
			mapStatue[tempP[0]][tempP[1]] = 4;
		}
		//将其记录到栈中
		pathStr.push(currP);
		//如果已经到达起点则终止迭代
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
	cout << "==========================================" << endl;
	//绘制找到的路线
	drawMap(mapStatue, visited, false);
	return 0;

}