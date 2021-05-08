/*��дһ������Ҫ��

(1)����һ����complex��������complex����������c1��c2������c1ͨ�����캯��ֱ��ָ��������ʵ�����鲿
����˽�����ݳ�ԱΪdouble���ͣ�real��imag��Ϊ3.3��5.5������c2ͨ�����캯��ֱ��ָ��������ʵ�����鲿Ϊ6.6��8.8��

(2)������Ԫ��������غ���������c1��c2����Ϊ���������øú���ʱ�ܷ�����������������ӡ��������˲�����

(3)�����Ա����print�����øú���ʱ�������ǰ�����ʵ�����鲿��
���磺�����ʵ�����鲿Ϊ6.6��8.8�������print���������ʽΪ��6.6+8.8 i �������ʵ�����鲿Ϊ6.6��-8.8��
�����print���������ʽΪ��6.6-8.8 i��

(4)��д�����򣬼������������c1��c2��ӡ��������˽�����������������

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