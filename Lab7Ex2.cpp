#include<iostream>
#include<stdexcept>
using namespace std;
class Item {
public:
	Item(int x=0)
		:value(x)
	{
		cout << "Item " << value << " constructor called.\n";
		if (value == 3) throw runtime_error("An exception was thrown");
	}
	~Item()
	{
		cout << "Item " << value << " destructor called.\n";
	}
private:
	int value;
};
void create()
{
	Item item1(1);
	Item item2(2);
	Item item3(3);
}
int main()
{
	try {
		create();
	}
	catch (runtime_error& exception)
	{
		cout << exception.what() << endl;
	}
}