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