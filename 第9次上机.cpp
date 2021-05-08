#include <fstream>
#include <iostream>
using namespace std;
void main()
{
	char ch;
	ifstream file("F:\a.txt");//读取c盘的文本文件
	ofstream file1("F:\b.txt", ios::app);//创建文本文件
	while (file.get(ch))//读取文本中的内容
	{
		cout << ch;
		file1 << ch;//写入内容到文件
	}
	file.close(); //关闭文件流
	file1.close();
	cout << endl;
}