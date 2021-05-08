#include<iostream>
//#include<stdio.h>
//#include<stdlib.h>
#include<windows.h>

using namespace std;

#define NEED_DRAW//是否绘制棋盘 
#define STEP_SLEEP 20//每一步的休眠时间 
#define ANSWER_SLEEP 5000//每找到一个解的休眠时间 

//棋盘尺寸
#define N 8 
//存放的每一行皇后的列数
int location[N + 1];

//绘制当前棋盘的方法
void drawBoard(int currRow)
{
#ifdef NEED_DRAW
	//清屏
	system("cls");
	//绘制棋盘
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			if (location[i] == j&&i <= currRow)
			{
				printf("★");
			}
			else
			{
				printf("□");
			}
		}
		printf("\n");
	}
#endif
}

//检查当前行的皇后是否与前面摆好的皇后冲突的方法
//不冲突返回false,冲突返回true
bool isConflict(int currRow)
{
	//检查当前行的皇后是否与前面摆好的皇后冲突
	bool flag = false;
	//目前在currRow行，检查和前面摆好的各行的冲突情况
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

//进行回溯法皇后摆放
void putQueenRetro()
{
	int currRow = 1;//表示当前行 
	//在第一行第一列放一个皇后
	location[currRow] = 1;
	int count = 0;

	//回溯主循环
	while (true)
	{
		//从第一行向第N行尝试放皇后
		//绘制棋盘
		drawBoard(currRow);
		//休眠ANSWER_SLEEOP毫秒
		Sleep(STEP_SLEEP);

		//若没有冲突
		if (!isConflict(currRow))
		{
			//若有解了
			if (currRow == N)
			{
				count++;
				drawBoard(currRow);
				//打印结果=====================begin
				printf("Answer %d [", count);
				for (int i = 1; i <= N; i++)
				{
					printf("%d", location[i]);
				}
				printf("]\n");
				//打印结束====================end
				//休眠STEP_SLEEP毫秒以便观察结果
				Sleep(ANSWER_SLEEP);
				//继续寻找其他解
				if (location[currRow]<N)
				{
					//若当前没有到第N列往右移动一列，继续在本行求解
					location[currRow] = location[currRow] + 1;
				}
				else
				{
					//否则回溯一行
					//回到上一行
					currRow--;
					//上一行的列数向右一格
					location[currRow] = location[currRow] + 1;
				}
			}
			else
			{
				//到下一行第一列摆放一个皇后
				currRow++;
				location[currRow] = 1;
			}
		}
		else
		{
			//冲突分两种情况处理
			//若当前行摆放的列还没有到最后一列
			if (location[currRow]<N)
			{
				//摆放位置向右移动一列
				location[currRow] = location[currRow] + 1;
			}
			else
			{
				//若当前行摆放的列已经到了最后一列
				//回到上一行
				currRow--;
				//若当前行摆放位置已经到了最后一列
				while (location[currRow] == N)
				{
					//继续回到上一行
					currRow--;
					//若没有可用的上一行，程序返回
					if (currRow<1)return;
				}
				//当前行摆放的位置向右移动一列
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