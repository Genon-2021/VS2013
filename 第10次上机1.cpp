/*1. ��д���򣺽�һ���ı��ļ����磺c:\a.txt�������ݣ�
׷�ӵ���һ���ı��ļ����磺c:\b.txt�����ݵ�β����Ҳ���ǣ�ʵ�������ļ����ݵĺϲ���

2. ͳ��һ���ı��ļ����磺c:\a1.txt���д�д��ĸ�ĸ�����*/

#include<iostream>
#include<fstream>

using namespace std;

int main()
{
	fstream a("F:\\a.txt", ios::in);
	if (!a)
	{
		cout << "���ܴ�!";
		return 1;
	}
	fstream b("F:\\b.txt", ios::app);
	if (!b)
	{
		cout << "���ܴ�!";
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

