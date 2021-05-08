/*1.��дһ������Ҫ�����������ʱ����������Ԫ��������غ�������

(1)����һ��������complex������˽�����ݳ�Աreal��imag��double���ͣ��������ڶ����Ĭ��ֵ�Ĺ��캯�������Դ������󡣶����Ա����print�����øú���ʱ�������ǰ�����ʵ�����鲿�����磺�����ʵ�����鲿Ϊ6.6��8.8�������print���������ʽΪ��6.6+8.8 i �������ʵ�����鲿Ϊ6.6��-8.8�������print���������ʽΪ��6.6-8.8 i��

(2)������������غ��������������+��-�������øú���ʱ�ܷ�����������������ӡ����������

(3) ������������غ��������������~�������øú���ʱ�ܷ��ظ��������������ԭ��ĶԳƵ����

(4) ������������غ��������������++������ǰ׺++��ʽ�������øú���ʱʵ�ָ�������������ʵ�����鲿�ֱ���������

(5) ������������غ��������������--�����ú�׺--��ʽ�������øú���ʱʵ�ָ����Լ�������ʵ�����鲿�ֱ��Լ�����

(6) ������������غ��������������==�����б����������Ƿ���ȣ��Ƚϸ�����ʵ�����鲿�Ƿ����ȣ���������������غ��������������>�������ڱȽ����������Ĵ�С���Ƚϸ���ģ�Ĵ�С�����ۺ�����==��>��������б����������Ĵ�С��

(7)��Main()�����ж�����complex����������c1��c2��������������غ����ĵ��ò����������������������ֱ�����������ף���

ע�⣺���˳�����뼰���н������Ϊ��Ԫ��ҵ�ϴ���

 

2.��д����ĳ���Ҫ�����������ʱ�������ó�Ա��������غ�����*/

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
		cout << "c1����c2" << endl;
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
	cout << "c1�ĳ�ʼֵ��";
	c1.print();
	cout << "c2�ĳ�ʼֵ��";
	c2.print();
	cout << "c1,c2�ĺ�Ϊ��";
	a = operator+(c1, c2);
	a.print();
	cout << "c1,c2�Ĳ�Ϊ��";
	a = operator-(c1, c2);
	a.print();
	cout << "c1�ĶԳƵ�Ϊ��";
	a = operator~(c1);
	a.print();
	cout << "c1ǰ׺����Ϊ��";
	a = operator++(c1);
	a.print();
	cout << "c1��׺�Լ�Ϊ��";
	a = operator--(c1,0);
	a.print();
	cout << "�����Ĵ�С��";
	a = operator>=(c1, c2);

	return 0;
}