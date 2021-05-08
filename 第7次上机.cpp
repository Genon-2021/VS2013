/*1.写一个程序，定义抽象基类Container，由它派生出三个派生类：
Sphere（球体）、Cylinder（圆柱体）、Cube（正方体）。用虚函数分别计算几种图形的体积。

体积公式分别为：PI*r*r*r*4/3；PI*r*r*h；r*r*r（r为半径、h为圆柱体的高）*/

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
	cout << "球的体积:" << p->V() << endl;
	
	cylinder b(1, 1);
	p = &b;
	cout << "圆柱的体积:" << p->V() << endl;

	cube c(1);
	p = &c;
	cout << "正方体的体积:" << p->V() << endl;
}