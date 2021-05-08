#include<iostream>
#include<string>
using namespace std;

class CStudent{
	int sno;
	string name;
	float escore;
	float cscore;
public:
	CStudent();
	CStudent(int sno, string name);
	void SetScore(float escore1,float cscore1);
	void SetSnoSname(int sno1, string name1);
	void all(int sno,string name,float escore,float cscoe)
	{
		this->sno = sno;
		this->name = name;
		this->escore = escore;
		this->cscore = cscoe;
	}
	void output(); 
};

CStudent::CStudent(){
	name = "";
}

CStudent::CStudent(int sno, string name){
	this->sno=sno;
	this->name = name;
}

void CStudent:: SetScore(float escore1, float cscore1){
	escore = escore1;
	cscore = cscore1;
}
void CStudent::SetSnoSname(int sno,string name){
	this->sno = sno;
	this->name = name;
}

void CStudent::output(){
	cout << "sno: " << sno
		<< "; name: " << name
        << "; escore=" << escore
		<< "; cscore=" << cscore << endl;
}

int main(){
	CStudent stu0;
	CStudent stu1(1, "student1");
	stu1.SetScore(96, 95);
	stu1.output();

	stu0.all(2, "students", 12, 56);
	stu0.output();

}