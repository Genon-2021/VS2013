#include<iostream>
#include<string>
#include<Windows.h>

using namespace std;

// PΪģʽ�����±��0��ʼ 
void GetNext(string P, int next[])
{
	int p_len = P.size();
	int i = 0;   //P���±�
	int j = -1;
	next[0] = -1;

	while (i < p_len)
	{
		if (j == -1 || P[i] == P[j])
		{
			i++;
			j++;
			next[i] = j;
		}
		else
			j = next[j];
	}
}

//KMP�����㷨 
//��S���ҵ�P��һ�γ��ֵ�λ�� 
int KMP(string S, string P, int next[])
{
	GetNext(P, next);

	int i = 0;  //S���±�
	int j = 0;  //P���±�
	int s_len = S.size();
	int p_len = P.size();

	while (i < s_len && j < p_len)
	{
		if (j == -1 || S[i] == P[j])  //P�ĵ�һ���ַ���ƥ���S[i] == P[j]
		{
			i++;
			j++;
		}
		else
			j = next[j];  //��ǰ�ַ�ƥ��ʧ�ܣ�������ת
	}

	if (j == p_len)  //ƥ��ɹ�
		return i - j;

	return -1;
}

//ɵ�ϻ����㷨
int Foolish(string S, string P)
{
	int i = 0;    //S���±�
	int j = 0;    //P���±�
	int s_len = S.size();
	int p_len = P.size();

	while (i < s_len && j < p_len)
	{
		if (S[i] == P[j])  //����ȣ���ǰ��һ��
		{
			i++;
			j++;
		}
		else  //�����
		{
			i = i - j + 1;
			j = 0;
		}
	}

	if (j == p_len)  //ƥ��ɹ�
		return i - j;

	return -1;
}

int main()
{
	string a = string{ "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" }+
			   string{ "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" }+
			   string{ "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" }+
			   string{ "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" }+
			   string{ "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" }+
			   string{ "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" }+
			   string{ "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" }+
			   string{ "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" }+
			   string{ "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" }+
			   string{ "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" }+
			   string{ "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" }+
		       string{ "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaas" };
	string b = "aaaaaas";
	int next[10000] = { 0 };

	cout << "====��KMP�����㷨����10000��====" << endl;
	DWORD start, end;

	start = GetTickCount();
	for (int j = 0; j < 10000; j++){
		 KMP(a, b, next);
	}
	end = GetTickCount() - start;
	cout <<"��ʱ��"<< end << endl;

	cout << "====��ɵ�ϻ����㷨����10000��====" << endl;
	start = GetTickCount();
	for (int j = 0; j < 10000; j++){
		Foolish(a, b);
	}
	end = GetTickCount() - start;
	cout << "��ʱ��" << end << endl;

	return 0;
}


