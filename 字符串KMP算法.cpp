#include<iostream>
#include<string>
#include<Windows.h>

using namespace std;

// P为模式串，下标从0开始 
void GetNext(string P, int next[])
{
	int p_len = P.size();
	int i = 0;   //P的下标
	int j = -1;
	next[0] = -1;

	while (i < p_len)
	{
		if (j == -1 || P[i] == P[j])
		{
			i++;
			j++;
			next[i] = j;
		}
		else
			j = next[j];
	}
}

//KMP回溯算法 
//在S中找到P第一次出现的位置 
int KMP(string S, string P, int next[])
{
	GetNext(P, next);

	int i = 0;  //S的下标
	int j = 0;  //P的下标
	int s_len = S.size();
	int p_len = P.size();

	while (i < s_len && j < p_len)
	{
		if (j == -1 || S[i] == P[j])  //P的第一个字符不匹配或S[i] == P[j]
		{
			i++;
			j++;
		}
		else
			j = next[j];  //当前字符匹配失败，进行跳转
	}

	if (j == p_len)  //匹配成功
		return i - j;

	return -1;
}

//傻瓜回溯算法
int Foolish(string S, string P)
{
	int i = 0;    //S的下标
	int j = 0;    //P的下标
	int s_len = S.size();
	int p_len = P.size();

	while (i < s_len && j < p_len)
	{
		if (S[i] == P[j])  //若相等，都前进一步
		{
			i++;
			j++;
		}
		else  //不相等
		{
			i = i - j + 1;
			j = 0;
		}
	}

	if (j == p_len)  //匹配成功
		return i - j;

	return -1;
}

int main()
{
	string a = string{ "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" }+
			   string{ "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" }+
			   string{ "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" }+
			   string{ "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" }+
			   string{ "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" }+
			   string{ "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" }+
			   string{ "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" }+
			   string{ "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" }+
			   string{ "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" }+
			   string{ "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" }+
			   string{ "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" }+
		       string{ "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaas" };
	string b = "aaaaaas";
	int next[10000] = { 0 };

	cout << "====用KMP回溯算法计算10000次====" << endl;
	DWORD start, end;

	start = GetTickCount();
	for (int j = 0; j < 10000; j++){
		 KMP(a, b, next);
	}
	end = GetTickCount() - start;
	cout <<"耗时："<< end << endl;

	cout << "====用傻瓜回溯算法计算10000次====" << endl;
	start = GetTickCount();
	for (int j = 0; j < 10000; j++){
		Foolish(a, b);
	}
	end = GetTickCount() - start;
	cout << "耗时：" << end << endl;

	return 0;
}


