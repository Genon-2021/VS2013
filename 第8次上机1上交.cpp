/*1. ����һ������ʵ����3��ͬ�������ݵĺ͵���ģ�壬��д�����ô���ģ�������������main( )�����У����������ݺ�˫�������ݽ��в��ԣ���




2. ��д�����Գ���ʵ�����¹��ܣ�

(1)�����ѧ����CStudent������˽�г�Ա3����ѧ�ţ�������������ɼ�����
�вι��캯�����ڸ�3����Ա��ֵ�����ҵ��ɼ�С��0���ߴ���100ʱ���׳��쳣������������Ϣ"ѧ���ɼ�����0-100֮��!"�����к�����Աshow()���������3����Ա��ֵ��

(2)���������У�����2��ѧ��������в��ԡ�*/

#include<iostream>

using namespace std;

template <typename T> 
class Sum
{
private:
	T x, y, z;
public:
	Sum(T a,T b,T c)
	{
		x = a;
		y = b;
		z = c;
	}
	T sum()
	{
		return (x + y + z);
	}
};


int main()
{
	Sum<int> sum1(1, 2, 3);
	Sum<double> sum2(1.1, 2.2, 3.3);
	cout << "the sum is: " << sum1.sum()<< endl;
	cout << "the sum is: " << sum2.sum()<< endl;

	return 0;
}