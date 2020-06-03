//Lab8Ex1
#include <iostream>
#include<string>
using namespace std;
template<typename elementType, int numberOfElement>
class Array
{
public:
	Array(elementType a[numberOfElement])
	{
		for (int i = 0; i < numberOfElement; i++)
			Elements[i] = a[i];
	};
	void print()
	{
		for (int i = 0; i < numberOfElement; i++)
			cout << Elements[i] << " ";
		cout << endl;
	}
private:
	elementType Elements[numberOfElement];
};
int main()
{
	const int size1 = 5;
	int A[size1];
	cout << "Enter 5 integer values:" << endl;
	for (int i = 0; i < size1; i++)
		cin >> A[i];
	cout << "The values in the intArray are:" << endl;
	Array<int, size1> a(A);
	a.print();

	const int size2 = 7;
	string B[size2];
	cout << "Enter 7 one word string " << endl;
	for (int i = 0; i < size2; i++)
		cin >> B[i];
	cout << "The values in the stringArray are:" << endl;
	Array<string, size2>b(B);
	b.print();
	return 0;
}
