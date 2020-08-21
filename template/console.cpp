// console.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "include.h"
#include "compiler.h"
#include "template.h"
using namespace std;

class Complex {
public:
	Complex() :x(0), y(0) {  }
	Complex(int v1, int v2) {
		x = v1;
		y = v2;
	}
	void Set(int v1, int v2) {
		x = v1;
		y = v2;
	}
	bool operator>(Complex& dest) {
		return x > dest.x && y > dest.y;
	}
	bool operator==(Complex& dest) {
		return x == dest.x && y == dest.y;
	}
private:
	int x, y;
};

int ints[] = { 1,2,3,6,7,8,10 };

CPCHAR str1 = "include.h", str2 = "compiler.h";
int i1 = 124, i2 = 124;
float f1 = 53.57, f2 = 62.67;
Complex c1(4, 5), c2(3, 6);

MyList<Complex> list1;
MyList<int> list2;
MyList<MyList<int>> list3;

int main()
{
	/*cout << Compare(str1, str2) << endl;
	cout << Compare(i1, i2) << endl;
	cout << Compare(f1, f2) << endl;
	cout << Compare(c1, c2) << endl;
	cout << Compare(&c1, &c2) << endl;
	cout << Compare(&f1, &f2) << endl;*/

	/*i1 = Find(keywords, 63, "case");
	i1 = Find((char*)symbols, (int)strlen(symbols), '#');
	i1 = Find(ints, 7, 5);*/

	/*list1.Push(c1);
	list1.Push(c2);

	i1 = 1;
	list2.Push(i1);
	list3.Push(list2);

	list3[0].Push(i1);
	list3[1].Push(i1);
	list3[2].Push(i1);
	list3[3].Push(i1);
	list3[4].Push(i1);*/

	ww.Open("..\\console\\template.h");
	ww.GetToken();

	system("pause");
}
