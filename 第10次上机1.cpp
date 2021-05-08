/*1. 编写程序：将一个文本文件（如：c:\a.txt）的内容，
追加到另一个文本文件（如：c:\b.txt）内容的尾部。也就是，实现两个文件内容的合并。

2. 统计一个文本文件（如：c:\a1.txt）中大写字母的个数。*/

#include<iostream>
#include<fstream>

using namespace std;

int main()
{
	fstream a("F:\\a.txt", ios::in);
	if (!a)
	{
		cout << "不能打开!";
		return 1;
	}
	fstream b("F:\\b.txt", ios::app);
	if (!b)
	{
		cout << "不能打开!";
		return 1;
	}
	char ch;
	while (a.get(ch))
	{
		b << ch;
	}
	a.close();
	b.close();

	return 0;
}

