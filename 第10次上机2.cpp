#include<iostream>
#include<fstream>

using namespace std;

int main()
{
	fstream a("F:\\a.txt", ios::in);
	if (!a)
	{
		cout << "不能打开!" << endl;
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
	cout << "F;\\a.txt中大写字母的个数为:" << count << endl;
	a.close();
	
	return 0;
}