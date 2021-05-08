/*1.派生类的定义及构造函数问题

编写一个学生和教师数据输入（函数名input）和显示（函数名disp）程序，学生数据有编号、姓名、班号和成绩，
教师数据有编号、姓名、职称和部门。要求将编号、姓名输入（函数名input）和显示（函数名disp）设计成一个类person，
并作为学生数据操作类student和教师数据操作类teacher的基类。在main()函数中，分别定义一个学生对象和一个教师对象，实现数据的输入和显示。

2.多继承问题

       定义时间类Time（含有保护数据成员：小时(hours)、分钟(minutes)、秒(seconds)；含有构造函数；
	   含有输出时间信息的成员函数）。定义日期类Date（含有保护数据成员：年(year)、月(month)、日(day)；
	   含有构造函数；含有输出日期信息的成员函数）。设计一个派生类Birthtime，它继承类Time和Date，
	   并且增加一个数据成员Childname用于表示小孩的名字，同时设计主程序显示一个小孩的名字和出生时间（年月日时分秒）。*/

#include<iostream>
#include<string>

using namespace std;

class person
{
protected:
	string num;
	string name;
public:
	void input()
	{
		cout << "编号:", cin >> num;
		cout << "姓名:", cin >> name;
	}

	void disp()
	{
		cout << "编号:" << num << endl;
		cout << "姓名:" << name << endl;
	}
};

class student :public person
{
protected:
	string Cnum;
	int score;
public:
	void input()
	{
		person::input();
		cout << "班级:", cin >> Cnum;
		cout << "成绩:", cin >> score;

	}
	void disp()
	{
		person::disp();
		cout << "班级:" << Cnum << endl;
		cout << "成绩:" << score << endl;
	}
};

class teacher :public person
{
protected:
	string position;
	string department;
public:
	void input()
	{
		person::input();
		cout << "职位:", cin >> position;
		cout << "部门:", cin >> department;
	}
	void disp()
	{
		person::disp();
		cout << "职位:" << position << endl;
		cout << "部门:" << department << endl;
	}
};

int main()
{
	student a;
	teacher b;
	cout << "----录入信息----" << endl;
	cout << "==学生==" << endl;
	a.input();
	cout << "==老师==" << endl;
	b.input();
	cout << "----输出信息----" << endl;
	cout << "==学生==" << endl;
	a.disp();
	cout << "==老师==" << endl;
	b.disp();

	return 0;
}