#include<iostream>
using namespace std;

class complex
{
private:
	double real, imag;
public:
	complex(){};
	complex(double real, double imag)
	{
		this->imag = imag;
		this->real = real;
	}
	friend ostream &operator <<(ostream& out,complex& a)
	{
		out << a.real;
		if (a.imag > 0) out << "+";
		if(a.imag!=0) out<< a.imag << "i";
		return out;
	}
	friend istream &operator >>(istream& in, complex& a)
	{
		cout << "输入复数实部和虚部的值：" << endl;
		in >> a.real >> a.imag;
		return in;
	}
	friend complex operator+(complex c1, complex c2)
	{
		complex temp;
		temp.real = c1.real + c2.real;
		temp.imag = c1.imag + c2.imag;
		return temp;
	}
};

int main(int argc,char* argv[])
{
	complex s, d, f;
	cin >> s;
	cin >> d;
	f = s + d;
	cout << "s=" << s << endl << "d=" << d << endl << "s+d=" << f << endl;
	return 0;
	
}