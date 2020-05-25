#include<iostream>
#include<stdexcept>
#include<string>
using namespace std;
class TestException :public runtime_error {
public:
	TestException(string s = "")
		:runtime_error(s){}
};
void f()
{
	throw TestException("TestException");
}
void g()
{
	f();
}
void h()
{
	g();
}
int main()
{
	try {
		h();
	}
	catch (TestException& te)
	{
		cout << "In main: Caught ";
		cout << te.what();
	}
	return 0;
}
