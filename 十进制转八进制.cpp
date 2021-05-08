#include<iostream>
using namespace std;

template <class T>
class mystack
{
public:
	T array[100];
	int topindex = 0;

	//判断栈是否为空
	bool isEmpty()
	{
		return topindex == 0;
	}

	//入栈
	void push(T n)
	{
		array[topindex] = n;
		topindex++;
	}

	//出栈
	T pop()
	{
		if (isEmpty()) return NULL;
		topindex--;
		return array[topindex];
	}

	//查看栈顶元素
	T top()
	{
		if (isEmpty()) return NULL;
		return array[topindex - 1];
	}
};

//十进制转化为八进制 
void EtoT(int a)
{
	mystack<int> s;//定义一个存放余数的栈s 
	while (a)
	{
		s.push(a % 8);//余数入栈 
		a = a / 8;//求商 
	}
	while (!s.isEmpty())
	{
		cout << s.pop();//余数出栈 
	}
	cout << endl;
}

int main()
{
	int b = 1348;
	cout << b << "(十进制)转换为八进制为:";
	EtoT(b);

	system("pause");
	return 0;
}