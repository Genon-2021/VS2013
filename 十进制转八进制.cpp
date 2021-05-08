#include<iostream>
using namespace std;

template <class T>
class mystack
{
public:
	T array[100];
	int topindex = 0;

	//�ж�ջ�Ƿ�Ϊ��
	bool isEmpty()
	{
		return topindex == 0;
	}

	//��ջ
	void push(T n)
	{
		array[topindex] = n;
		topindex++;
	}

	//��ջ
	T pop()
	{
		if (isEmpty()) return NULL;
		topindex--;
		return array[topindex];
	}

	//�鿴ջ��Ԫ��
	T top()
	{
		if (isEmpty()) return NULL;
		return array[topindex - 1];
	}
};

//ʮ����ת��Ϊ�˽��� 
void EtoT(int a)
{
	mystack<int> s;//����һ�����������ջs 
	while (a)
	{
		s.push(a % 8);//������ջ 
		a = a / 8;//���� 
	}
	while (!s.isEmpty())
	{
		cout << s.pop();//������ջ 
	}
	cout << endl;
}

int main()
{
	int b = 1348;
	cout << b << "(ʮ����)ת��Ϊ�˽���Ϊ:";
	EtoT(b);

	system("pause");
	return 0;
}