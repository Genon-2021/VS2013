/*1.������Ķ��弰���캯������

��дһ��ѧ���ͽ�ʦ�������루������input������ʾ��������disp������ѧ�������б�š���������źͳɼ���
��ʦ�����б�š�������ְ�ƺͲ��š�Ҫ�󽫱�š��������루������input������ʾ��������disp����Ƴ�һ����person��
����Ϊѧ�����ݲ�����student�ͽ�ʦ���ݲ�����teacher�Ļ��ࡣ��main()�����У��ֱ���һ��ѧ�������һ����ʦ����ʵ�����ݵ��������ʾ��

2.��̳�����

       ����ʱ����Time�����б������ݳ�Ա��Сʱ(hours)������(minutes)����(seconds)�����й��캯����
	   �������ʱ����Ϣ�ĳ�Ա������������������Date�����б������ݳ�Ա����(year)����(month)����(day)��
	   ���й��캯�����������������Ϣ�ĳ�Ա�����������һ��������Birthtime�����̳���Time��Date��
	   ��������һ�����ݳ�ԱChildname���ڱ�ʾС�������֣�ͬʱ�����������ʾһ��С�������ֺͳ���ʱ�䣨������ʱ���룩��*/

#include<iostream>
#include<string>

using namespace std;

class person
{
protected:
	string num;
	string name;
public:
	void input()
	{
		cout << "���:", cin >> num;
		cout << "����:", cin >> name;
	}

	void disp()
	{
		cout << "���:" << num << endl;
		cout << "����:" << name << endl;
	}
};

class student :public person
{
protected:
	string Cnum;
	int score;
public:
	void input()
	{
		person::input();
		cout << "�༶:", cin >> Cnum;
		cout << "�ɼ�:", cin >> score;

	}
	void disp()
	{
		person::disp();
		cout << "�༶:" << Cnum << endl;
		cout << "�ɼ�:" << score << endl;
	}
};

class teacher :public person
{
protected:
	string position;
	string department;
public:
	void input()
	{
		person::input();
		cout << "ְλ:", cin >> position;
		cout << "����:", cin >> department;
	}
	void disp()
	{
		person::disp();
		cout << "ְλ:" << position << endl;
		cout << "����:" << department << endl;
	}
};

int main()
{
	student a;
	teacher b;
	cout << "----¼����Ϣ----" << endl;
	cout << "==ѧ��==" << endl;
	a.input();
	cout << "==��ʦ==" << endl;
	b.input();
	cout << "----�����Ϣ----" << endl;
	cout << "==ѧ��==" << endl;
	a.disp();
	cout << "==��ʦ==" << endl;
	b.disp();

	return 0;
}