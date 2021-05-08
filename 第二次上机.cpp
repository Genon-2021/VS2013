/*编写一个程序，已有若干学生的数据，包括学号、姓名、成绩，
要求输出这些学生的数据并计算出学生人数和平均成绩
（要求学生人数和总成绩用静态数据成员表示）。*/

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
	cout << "学号" << "  " << "姓名" << "  " << "成绩" << endl;
	for (int i = 0; i < 3; i++)
	{
		stu[i].output();
	}
	cout << "总人数：" << stu->Count() << endl;
	cout << "平均分：" << stu->ave ()<< endl;

	return 0;
}

