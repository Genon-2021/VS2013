#include<iostream>
#include<string>//用字符串类
#include<fstream>//文件
#include<sstream>//将字符的数字转换成整形
#include<cstring>//strcpy 函数
//#include "计算机工作的高级语言实现.h"
using namespace std;
#define max 8
char s[max][100];//全局变量 用来存汇编代码
typedef std::uint64_t hash_t;//为了使用switch
constexpr hash_t prime = 0x100000001B3ull;
constexpr hash_t basis = 0xCBF29CE484222325ull;
hash_t hash_(char const* str)//将字符串转换成一个整数类型
{
	hash_t ret{ basis };

	while (*str) {
		ret ^= *str;
		ret *= prime;
		str++;
	}

	return ret;
}
constexpr hash_t hash_compile_time(char const* str, hash_t last_value = basis)
{
	return *str ? hash_compile_time(str + 1, (*str ^ last_value) * prime) : last_value;
};
void Get_txt()//读入文件的汇编代码
{
	ifstream fin("data.txt");//放入自己的文件名字
	int i = 0;
	while (fin.getline(s[i], 100))
	{
		i++;
	}
};
int main()
{
	Get_txt();
	int TF;//状态寄存器
	cout << "单步执行请按0，直接显示结果请按1：";
	cin >> TF;
	string IR, DR;//指令寄存器和数据寄存器（暂存器）
	int AR;//地址寄存器
	int ABUS, DBUS;//指令总线和数据总线
	int q = 0;//中间变量
	int o_PC = 0;//程序计数器PC
	int n_PC = 1;//数据存储器的PC，起计数作用
	int RA = 1, AC = 0;//寄存器
	int num[102];//模拟数据存储器
	for (int i = 2; i <= 101; i++)//最后保存在101位置
		num[i] = i;
	int flag = 0;//标志位  用于判断循环
	while (flag != 1)
	{
		AR = o_PC;//PC传给地址寄存器
		o_PC++;//PC+1
		ABUS = AR;//地址寄存器给指令总线
		DR = s[AR];//将指令取出来送给数据寄存器
		IR = DR;//将指令送给指令寄存器
		char temp[4];
		strcpy(temp, IR.substr(0, 3).c_str());
		switch (hash_(temp))//判断是哪个指令
		{
		case hash_compile_time("MOV"):
		{
			char temp1[4];
			strcpy(temp1, IR.substr(4, 2).c_str());
			switch (hash_(temp1))
			{
			case hash_compile_time("RA"):
			{
				int d;
				stringstream ss;
				ss << IR.substr(7, 1);
				ss >> d;
				DBUS = d;//将数据送给数据总线
				RA = DBUS;//将数据送给RA寄存器

			}break;
			case hash_compile_time("AC"):
			{
				int d;
				stringstream ss;
				ss << IR.substr(7, 1);
				ss >> d;
				DBUS = d;//将数据送给数据总线
				AC = DBUS;//将数据送给AC寄存器

			}break;
			}

		}break;
		case hash_compile_time("ADD"):
		{
			//暂存结果
			q = AC + RA;
			DBUS = q;//将数据送给数据总线
			AC = DBUS;//将运算后的数据送给AC寄存器

		}break;
		case hash_compile_time("INC"):
		{
			n_PC++;//从数据寄存器取出数据
			AR = n_PC;
			DBUS = num[AR];
			RA = DBUS;

		}break;
		case hash_compile_time("CMP"):
		{
			int d;
			stringstream ss;
			ss << IR.substr(7, 3);
			ss >> d;
			if (RA > d)
				o_PC = 6;
			else
				o_PC = 5;

		}break;
		case hash_compile_time("JNE"):
		{
			int d;
			stringstream ss;
			ss << IR.substr(4, 1);
			ss >> d;
			o_PC = d;//将要跳转的地址给PC

		}break;
		case hash_compile_time("RET"):
		{
			flag = 1;
		}break;
	defalut:break;
		}
		if (TF == 1)//一起输出
		{
			cout << "寄存器RA：" << RA
				<< "  " << "寄存器AC：" << AC
				<< "  " << "程序计数器PC：" << o_PC
				<< endl;
		}
		if (TF == 0)//单步执行
		{
			cout << "寄存器RA：" << RA
				<< "  " << "寄存器AC：" << AC
				<< "  " << "程序计数器PC：" << o_PC
				<< endl;
			system("pause");
			int get;
			cout << "修改寄存器RA的值请按1,否则请按0:";
			cin >> get;
			if (get == 1)
			{
				cout << "请输入你想改变的寄存器RA的值：";
				cin >> RA;
				o_PC = 4;
				n_PC = RA;
			}
		}
	}
	cout << AC << endl;
	system("pause");
}