#include <fstream>
#include <iostream>
using namespace std;
void main()
{
	char ch;
	ifstream file("F:\a.txt");//��ȡc�̵��ı��ļ�
	ofstream file1("F:\b.txt", ios::app);//�����ı��ļ�
	while (file.get(ch))//��ȡ�ı��е�����
	{
		cout << ch;
		file1 << ch;//д�����ݵ��ļ�
	}
	file.close(); //�ر��ļ���
	file1.close();
	cout << endl;
}