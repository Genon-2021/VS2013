/*1.编写一个程序，定义一个Time类，包含3个数据成员：hours（时）、minutes（分）、seconds（秒），
另有构造函数用以创建对象、时间相加运算符“+”重载函数、输出函数show()用以输出时间。注意：3时50分15秒，加上15分50秒，应该为4时6分5秒。

*/

#include<iostream>

using namespace std;

class Time
{
	int h, m, s;
public:
	Time(){};
	Time(int h, int m, int s)
	{
		this->h = h;
		this->m = m;
		this->s = s;
	}
	//friend Time operator+(Time t1, Time t2);
	Time operator+(Time t1)
	{
		Time t;
		t.s = s + t1.s;
		t.m = m +t1.m+ t.s / 60;
		t.h = h + t1.h+t.m / 60;
		Time a;
		a.s = t.s % 60;
		a.m = t.m % 60;
		a.h = t.h;
		return a ;
	};
	void show()
	{
		cout << h << "时" << m << "分" <<s<< "秒" << endl;
	}
	
};

/*Time operator+(Time t1)
{
	Time t;
	if ((t1.s + t2.s) < 60)
	{
		t.s = t1.s + t2.s;
	}
	else
	{
		t.s = (t1.s + t2.s) - 60;
		t.m = t1.m + t2.m + 1;
		
	}

	if (t.m < 60)
	{
		t.m =t.m;
	}
	else
	{
		t.m = t.m - 60;
		t.h = t1.h + t2.h + 1;
		
	}
	
	return t;
}*/

int main()
{
	Time t1(3, 50, 15), t2(0, 15, 50), a;
	cout << "t1为:";
	t1.show();
	cout << "t2为:";
	t2.show();
	cout << "t1,t2相加为:";
	//a = operator+(t1, t2);
	a = t1 + t2;
	a.show();

	return 0;
}