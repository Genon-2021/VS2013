/*1.дһ�����򣬶���������Container���������������������ࣺ
Sphere�����壩��Cylinder��Բ���壩��Cube�������壩�����麯���ֱ���㼸��ͼ�ε������

�����ʽ�ֱ�Ϊ��PI*r*r*r*4/3��PI*r*r*h��r*r*r��rΪ�뾶��hΪԲ����ĸߣ�*/

#include<iostream>
#define PI 3.14
using namespace std;

class container
{
protected:
	double r;
public:
	container(double r)
	{
		this->r = r;
	};
	virtual double V()= 0;
};

class sphere:public container
{
public:
	sphere(double r) :container(r){};
	double V()
	{
		return  PI*r*r*r * 4 / 3;
	}
};

class cylinder :public container
{
protected:
	double h;
public:
	cylinder(double h, double r) :container(r)
	{
		this->h = h;
	};
	double V()
	{
		return  PI*r*r*h;
	}
};

class cube :public container
{
public:
	cube(double r) :container(r){};
	double V()
	{
		return  r*r*r;
	}
};

int main()
{
	container *p;
	sphere a(1);
	p = &a;
	cout << "������:" << p->V() << endl;
	
	cylinder b(1, 1);
	p = &b;
	cout << "Բ�������:" << p->V() << endl;

	cube c(1);
	p = &c;
	cout << "����������:" << p->V() << endl;
}