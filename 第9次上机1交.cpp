/*1. 编写程序：将一个文本文件（如：c:\a.txt）内容输出到另外一个文本文件（如：c:\b.txt）。
要求：在输出时，将小写字母转换成大写字母。

2. 重载运算符<<和>>，使用户能够直接输入和输出复数。*/

#include<iostream>
#include<fstream>

using namespace std;

int main()
{
	fstream in("F:\\a.txt", ios::in);
	if (!in)
	{
		cout << "不能打开!";
		return 1;
	}
	fstream out("F:\\b.txt", ios::out);
	if (!out)
	{
		cout << "不能打开!";
		return 1;
	}
	char ch;
	while (in.get(ch))
	{
		if (ch >= 'a'&&ch <= 'z')
			ch = toupper(ch);
		out << ch;
	}
	in.close();
	out.close();
	return 0;
}
