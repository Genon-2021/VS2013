/*1. ��д���򣺽�һ���ı��ļ����磺c:\a.txt���������������һ���ı��ļ����磺c:\b.txt����
Ҫ�������ʱ����Сд��ĸת���ɴ�д��ĸ��

2. ���������<<��>>��ʹ�û��ܹ�ֱ����������������*/

#include<iostream>
#include<fstream>

using namespace std;

int main()
{
	fstream in("F:\\a.txt", ios::in);
	if (!in)
	{
		cout << "���ܴ�!";
		return 1;
	}
	fstream out("F:\\b.txt", ios::out);
	if (!out)
	{
		cout << "���ܴ�!";
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
