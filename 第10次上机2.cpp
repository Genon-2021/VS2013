#include<iostream>
#include<fstream>

using namespace std;

int main()
{
	fstream a("F:\\a.txt", ios::in);
	if (!a)
	{
		cout << "���ܴ�!" << endl;
		return 1;
	}
	int count = 0;
	char ch;
	while (a.get(ch))
	{
		if (ch >= 'A' && ch <= 'Z')
		{
			count++;
		}
	}
	cout << "F;\\a.txt�д�д��ĸ�ĸ���Ϊ:" << count << endl;
	a.close();
	
	return 0;
}