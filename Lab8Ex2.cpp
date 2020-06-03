//Lab8Ex2.cpp
#include<iostream>
using namespace std;
template<typename T>
bool isEqualTo(T a,T b)
{
	if (a == b) return true;
	else return false;
}
class Complex {
public:
	Complex(double r = 0.0, double i = 0.0)
		:real(r), imaginary(i){}
	double getR()const { return real; }
	double getI()const { return imaginary; }
	void setR(const double r) { real = r; }
	void setI(const double i) { imaginary = i; }
	bool operator ==(Complex b)
	{
		return real == b.real && imaginary == b.imaginary;
	}
private:
	double real, imaginary;
};
int main()
{
	//Part 1
	int a = 1, b = 2;
	cout << "a is " << (isEqualTo(a, b) ? "" : "not") << " equal to b" << endl;
	double x = 3.14, y = 6.28;
	cout << "x is " << (isEqualTo(x, y) ? "" : "not") << " equal to y" << endl;
	char c = 'A', d = 65;
	cout << "c is " << (isEqualTo(c, d) ? "" : "not") << " equal to d" << endl;
	/*Part 2: This will lead to a compile error, because there is no operator == for class Complex
	Complex e(2, 3), f(2, 3);
	if (isEqualTo(e, f)) cout << "Complex a is equal to complex b" << endl;*/
	//Part 3
	Complex e(2, 3), f(2, 3);
	if (isEqualTo(e, f)) cout << "Complex a is equal to complex b" << endl;
	return 0;
}
