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