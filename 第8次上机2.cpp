#include<iostream>
#include<string>

using namespace std;

class CStudent
{
private:
	int num;
	float score;
	string name;
public:
	CStudent(int num, float score, string name)
	{
		try
		{
			this->num = num;
			this->name = name;
			this->score = score;
			if (score < 0 || score>100) throw score;
		}
		catch (float)
		{
			cout << "ѧ����������0����100֮��" << endl;
		}
	}

	void show()
	{
		cout << "ѧ��: " << num << " ����: " << name << " ����: " << score << endl;
	}

};

int main()
{
	CStudent a(01, 99,"aa");
	a.show();
	CStudent b(02, 150, "bb");
	b.show();

	return 0;
}