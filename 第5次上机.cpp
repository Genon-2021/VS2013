/*1.��дһ�����򣬶���һ��Time�࣬����3�����ݳ�Ա��hours��ʱ����minutes���֣���seconds���룩��
���й��캯�����Դ�������ʱ������������+�����غ������������show()�������ʱ�䡣ע�⣺3ʱ50��15�룬����15��50�룬Ӧ��Ϊ4ʱ6��5�롣

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
		cout << h << "ʱ" << m << "��" <<s<< "��" << endl;
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
	cout << "t1Ϊ:";
	t1.show();
	cout << "t2Ϊ:";
	t2.show();
	cout << "t1,t2���Ϊ:";
	//a = operator+(t1, t2);
	a = t1 + t2;
	a.show();

	return 0;
}