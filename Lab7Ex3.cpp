#include<iostream>
#include<stdexcept>
#include<string>
using namespace std;
class TestException:public runtime_error{
public:
	TestException(string s = "")
		:runtime_error(s){}
};
void g()
{
	try {
		throw TestException();
	}
	catch (TestException&)
	{
		cout << "Exception caught in function g(). Rethrowing...\n";
		throw;
	}
}
int main()
{
	try {
		g();
	}
	catch (TestException&)
	{
		cout << "Exception caught in function main().";
	}
	return 0;
}
