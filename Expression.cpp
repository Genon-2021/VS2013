
#include <iostream>  
#include<stack>  
#include<string>  
using namespace std;
stack <char> p;
stack <int> q;
string s;
void add()
{
	int a = 0, b = 0;
	char c;
	c = p.top();
	p.pop();
	a = q.top();
	q.pop();
	b = q.top();
	q.pop();
	if (c == '+')
	{
		a = b + a;
		q.push(a);
	}
	else if (c == '-')
	{
		a = b - a;
		q.push(a);
	}
	else if (c == '*')
	{
		a = a*b;
		q.push(a);
	}
	else if (c == '/')
	{
		a = b / a;
		q.push(a);
	}
}
int main()
{
	int n, i, len, m;
	cin >> n;
	while (n--)
	{
		cin >> s;
		len = s.length();
		for (i = 0; i<len; i++)
		{
			if (s[i]<48 && s[i] != ')')
			{
				if (s[i] == '(' || p.empty())
				{
					p.push(s[i]);
				}
				else
				{
					if (s[i] == '*' || s[i] == '/')
					{
						if (p.top() == '+' || p.top() == '-' || p.top() == '(')
							p.push(s[i]);
						else
						{
							if (!p.empty())
							{
								while (p.top() != '+' || p.top() != '-' || p.top() != '(')
								{
									add();
									if (p.empty())
										break;
									else if (p.top() == '+' || p.top() == '-' || p.top() == '(')
										break;
								}
								p.push(s[i]);
							}
						}
					}
					else if (s[i] == '+' || s[i] == '-')
					{
						if (p.top() == '(')
						{
							p.push(s[i]);
						}
						else
						{
							if (!p.empty())
							{
								while (p.top() != '(' || !p.empty())
								{
									add();
									if (p.empty())
										break;
									else if (p.top() == '(')
										break;
								}
								p.push(s[i]);
							}
						}
					}
				}
			}
			else if (s[i] == ')')
			{
				while (p.top() != '(')
				{
					add();
					if (p.top() == '(')
						break;
				}
				p.pop();
			}
			else
			{
				m = 0;
				while ((s[i] >= 48 && s[i] <= 57))
				{
					m = m * 10 + s[i] - '0';
					i++;
				}
				q.push(m);
				i--;
			}
		}
		while (!p.empty())
		{
			add();
		}
		cout << q.top() << endl;
	}
	return 0;
}
