//初始化队列的大小
#define queue_capacity 100

template <class T>
class myqueue
{
public:
	T array[queue_capacity];
	int headindex;//头索引
	int tailindex;//尾索引
	int count;//记录队列大小
	myqueue()
	{
		headindex = 0;
		tailindex = 0;
		count = 0;
	}

	//判断队列是否为空
	bool isEmpty()
	{
		return count == 0;
	}

	//判断队列是否为满
	bool isFull()
	{
		return count == queue_capacity;
	}

	//插入数据
	void add(T n)
	{
		if (isFull()) return;//判满
		array[tailindex] = n;
		tailindex++;//尾索引加1
		tailindex = tailindex%queue_capacity;
		count++;//队列大小增加
	}

	//删除数据
	T serve()
	{
		if (isEmpty()) return NULL;
		T result = array[headindex];//获取头索引的数据
		headindex++;
		headindex = headindex%queue_capacity;
		count--;//队列大小减少
		return result;//返回头索引的数据
	}

	//查看队列头索引的数据
	T head()
	{
		if (isEmpty()) return NULL;
		return array[headindex];
	}
};