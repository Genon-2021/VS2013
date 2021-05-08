/*1.编写一个程序，要求（重载运算符时，均采用友元运算符重载函数）：

(1)声明一个复数类complex，含有私有数据成员real和imag（double类型）。在类内定义带默认值的构造函数，用以创建对象。定义成员函数print，调用该函数时，输出当前对象的实部和虚部。例如：对象的实部和虚部为6.6和8.8，则调用print函数输出格式为：6.6+8.8 i ；对象的实部和虚部为6.6和-8.8，则调用print函数输出格式为：6.6-8.8 i。

(2)定义运算符重载函数（重载运算符+和-），调用该函数时能返回两个复数对象相加、相减操作。

(3) 定义运算符重载函数（重载运算符~），调用该函数时能返回复数对象关于坐标原点的对称点对象。

(4) 定义运算符重载函数（重载运算符++，采用前缀++形式），调用该函数时实现复数自增操作（实部和虚部分别自增）。

(5) 定义运算符重载函数（重载运算符--，采用后缀--形式），调用该函数时实现复数自减操作（实部和虚部分别自减）。

(6) 定义运算符重载函数（重载运算符==），判别两个复数是否相等（比较复数的实部和虚部是否均相等）；定义运算符重载函数（重载运算符>），用于比较两个复数的大小（比较复数模的大小）。综合运用==和>运算符，判别两个复数的大小。

(7)在Main()函数中定义类complex的两个对象c1和c2，进行运算符重载函数的调用并输出运算结果（输出结果尽量直观且容易明白）。

注意：将此程序代码及运行结果，作为单元作业上传。

 

2.改写上面的程序，要求重载运算符时，均采用成员运算符重载函数。*/

#include<iostream>
#include<math.h>
using namespace std;

class  complex
{
	double real, imag;
public:
	friend complex operator+(complex c1, complex c2);
	friend complex operator-(complex c1, complex c2);
	friend complex operator~(complex c1);
	friend complex operator++(complex c1);
	friend complex operator--(complex c1,int );
	friend complex operator>=(complex c1, complex c2);
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
complex operator+(complex c1, complex c2)
{
	complex temp;
	temp.real = c1.real + c2.real;
	temp.imag = c1.imag + c2.imag;
	return temp;
}

complex operator-(complex c1, complex c2)
{
	complex temp;
	temp.real = c1.real - c2.real;
	temp.imag = c1.imag - c2.imag;
	return temp;
}

complex operator~(complex c1)
{
	complex temp;
	temp.real = -c1.real;
	temp.imag = -c1.imag;
	return temp;
}

complex operator++(complex c1)
{
	++c1.real, ++c1.imag;
	return c1;
}

complex operator--(complex c1,int )
{
	c1.real--, c1.imag--;
	return c1;
}

complex operator>=(complex c1, complex c2)
{
	if ((c1.real == c2.real) && (c1.imag == c2.imag))
	{
		cout << "c1等于c2" << endl;
	}
	else
	{
		if ((c1.real*c1.real + c1.imag*c1.imag) > (c2.real*c2.real + c2.imag*c2.imag))
		{
			cout << "c1>c2" << endl;
		}
		else
		{
			cout << "c1<c2" << endl;
		}
	}
	return 0;
}
	
int main()
{
	complex c1(3.3, 5.5), c2(6.6, 8.8), a, b,c,d,e,f;
	cout << "c1的初始值：";
	c1.print();
	cout << "c2的初始值：";
	c2.print();
	cout << "c1,c2的和为：";
	a = operator+(c1, c2);
	a.print();
	cout << "c1,c2的差为：";
	a = operator-(c1, c2);
	a.print();
	cout << "c1的对称点为：";
	a = operator~(c1);
	a.print();
	cout << "c1前缀自增为：";
	a = operator++(c1);
	a.print();
	cout << "c1后缀自减为：";
	a = operator--(c1,0);
	a.print();
	cout << "两数的大小：";
	a = operator>=(c1, c2);

	return 0;
}