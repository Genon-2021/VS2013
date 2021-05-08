//��ʼ�����еĴ�С
#define queue_capacity 100

template <class T>
class myqueue
{
public:
	T array[queue_capacity];
	int headindex;//ͷ����
	int tailindex;//β����
	int count;//��¼���д�С
	myqueue()
	{
		headindex = 0;
		tailindex = 0;
		count = 0;
	}

	//�ж϶����Ƿ�Ϊ��
	bool isEmpty()
	{
		return count == 0;
	}

	//�ж϶����Ƿ�Ϊ��
	bool isFull()
	{
		return count == queue_capacity;
	}

	//��������
	void add(T n)
	{
		if (isFull()) return;//����
		array[tailindex] = n;
		tailindex++;//β������1
		tailindex = tailindex%queue_capacity;
		count++;//���д�С����
	}

	//ɾ������
	T serve()
	{
		if (isEmpty()) return NULL;
		T result = array[headindex];//��ȡͷ����������
		headindex++;
		headindex = headindex%queue_capacity;
		count--;//���д�С����
		return result;//����ͷ����������
	}

	//�鿴����ͷ����������
	T head()
	{
		if (isEmpty()) return NULL;
		return array[headindex];
	}
};