#include<iostream>
using namespace std;
template <typename T>
T max(T *array, int n)
{
	int i;
	T maxvalue = array[0];
	for (i = 1; i < n; i++)
		if (array[i]> maxvalue)maxvalue = array[i];
	return maxvalue;
}

int main()
{
	int a[] = { 1, 5, 66, 7, 22, 5, 30 };
	double b[] = { 2.33, 2.3, 6.5, 7.21, 7.36, 1.21 };
	char s[] = "Hello my friend!";
	cout << max(a, sizeof(a)/sizeof(int)) << endl;
	cout << max(b, sizeof(b)/sizeof(double)) << endl;
	cout << max(s, strlen(s)) << endl;
}