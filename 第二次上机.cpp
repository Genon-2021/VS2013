/*��дһ��������������ѧ�������ݣ�����ѧ�š��������ɼ���
Ҫ�������Щѧ�������ݲ������ѧ��������ƽ���ɼ�
��Ҫ��ѧ���������ܳɼ��þ�̬���ݳ�Ա��ʾ����*/

#include<iostream>
#include<string>
#include<cmath>
using namespace std;

class student
{
	static int count;
	static	double sum;
public:
	int sno;
	double score;
	string name;

	student(int sno, string name, double score)
	{
		this->sno = sno;
		this->name = name;
		this->score = score;
		sum = sum+score;
	}

	student()
	{
		count++;
	}

	static int Count()
	{
		return count;
	}

	static double ave()
	{
		return sum / count;
	}

	void output()
	{
		cout << sno << "     " << name << "      " << score << endl;

	}
};

int student::count = 0;
double  student:: sum = 0;

int main()
{
	student* stu = new student[3];
	stu[0] = { 0, "A", 78 };
	stu[1] = { 1, "B", 55 };
	stu[2] = { 2, "C", 88 };
	cout << "ѧ��" << "  " << "����" << "  " << "�ɼ�" << endl;
	for (int i = 0; i < 3; i++)
	{
		stu[i].output();
	}
	cout << "��������" << stu->Count() << endl;
	cout << "ƽ���֣�" << stu->ave ()<< endl;

	return 0;
}

