/*������cylinder��cylinder�Ĺ��캯��������������doubleֵ���ֱ��ʾԲ����İ뾶�͸߶ȡ�
����cylinder����Բ�������������洢��һ��double�����С�
����cylinder�а���һ����Ա����vol��������ʾÿ��cylinder����������*/

#include<iostream>
using namespace std;

class cylinder{
private:
	double r, h, v;
public:
	cylinder(double a, double b);
	void vol();
};

cylinder::cylinder(double a,double b){
	r = a;
	h = b;
	v = 3.14*r*r*h;
}

void cylinder::vol(){
	cout << "volume is:" << v << endl;
}

int main(){
	cylinder x(1, 2);
	x.vol();
	cylinder *p = new cylinder(1, 3);
	p->vol();
	return 0;
}