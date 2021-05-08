/*1. 建立一个用来实现求3个同类型数据的和的类模板，并写出调用此类模板的完整程序（在main( )函数中，用整型数据和双精度数据进行测试）。




2. 编写并调试程序，实现以下功能：

(1)定义大学生类CStudent，含有私有成员3个（学号，姓名，计算机成绩）；
有参构造函数用于给3个成员赋值，并且当成绩小于0或者大于100时，抛出异常，给出出错信息"学生成绩不在0-100之间!"；含有函数成员show()，用于输出3个成员的值。

(2)在主函数中，创建2个学生对象进行测试。*/

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