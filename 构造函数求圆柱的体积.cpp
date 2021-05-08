/*建立类cylinder，cylinder的构造函数被传递了两个double值，分别表示圆柱体的半径和高度。
用类cylinder计算圆柱体的体积，并存储在一个double变量中。
在类cylinder中包含一个成员函数vol，用来显示每个cylinder对象的体积。*/

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