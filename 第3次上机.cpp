/*编写一个程序，要求：

(1)声明一个类complex，定义类complex的两个对象c1和c2，对象c1通过构造函数直接指定复数的实部和虚部
（类私有数据成员为double类型：real和imag）为3.3及5.5，对象c2通过构造函数直接指定复数的实部和虚部为6.6和8.8；

(2)定义友元运算符重载函数，它以c1、c2对象为参数，调用该函数时能返回两个复数对象相加、相减及相乘操作；

(3)定义成员函数print，调用该函数时，输出当前对象的实部和虚部。
例如：对象的实部和虚部为6.6和8.8，则调用print函数输出格式为：6.6+8.8 i ；对象的实部和虚部为6.6和-8.8，
则调用print函数输出格式为：6.6-8.8 i。

(4)编写主程序，计算出复数对象c1和c2相加、相减及相乘结果，并将其结果输出。

*/

#include<iostream>
using namespace std;
class  complex
{
	double real, imag;
public:
	friend complex operator+(complex c1, complex c2)
	{
		complex temp;
		temp.real = c1.real + c2.real;
		temp.imag = c1.imag + c2.imag;
		return temp;
	}
	friend complex operator-(complex c1, complex c2);
	friend complex operator*(complex c1, complex c2);
	complex(double r = 0, double i = 0){ real = r; imag = i; }
	void print()
	{ 
		if (imag > 0)
		{
			cout << real << " +" << imag << "i" << endl;
		}
		else if (imag != 0)
		{
			cout << real << imag << "i" << endl;
		}
	}
};
/*complex operator+(complex c1, complex c2)
{
	complex temp;
	temp.real = c1.real + c2.real;
	temp.imag = c1.imag + c2.imag;
	return temp;
}*/

complex operator-(complex c1, complex c2)
{
	complex temp;
	temp.real= c1.real-c2.real;
	temp.imag = c1.imag-c2.imag;
	return temp;
}

complex operator*(complex c1, complex c2)
{
	complex temp;
	temp.real = c1.real * c2.real-c1.imag*c2.imag;
	temp.imag = c1.imag * c2.real+c1.imag*c2.real;
	return temp;
}


int main()
{
	complex com1(3.3, 5.5), com2(6.6, 8.8), a,b,c;
	a = operator+(com1, com2);
	b = operator-(com1, com2);
	c = operator*(com1, com2);
	a.print();
	b.print();
	c.print();

	return 0;
}