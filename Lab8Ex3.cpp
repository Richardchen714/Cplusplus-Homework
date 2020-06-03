#include<iostream>
using namespace std;
template<typename T>
class Vector {
	template<typename S>
	friend ostream& operator<<(ostream&, Vector<S>&);
	template<typename R>
	friend istream& operator>>(istream&, Vector<R>&);
public:
	Vector(int s = 1) :size(s)
	{
		ptr = new T[size];
		for (int i = 0; i < s; i++)
			ptr[i] = 0;
	}
private:
	int size;
	T* ptr;
};
template<typename S>
ostream& operator<<(ostream& out, Vector<S> &v)
{
	if (v.size)
		for (int i = 0; i < v.size; i++)
			out << v.ptr[i] << " ";
	else out << "This is an empty vector" << endl;
	return out;
}
template<typename R>
istream& operator>>(istream& in, Vector<R>& v)
{
	for (int i = 0; i < v.size; i++)
		in >> v.ptr[i];
	return in;
}
int main()
{
	Vector<int>a(5);
	cout << "Enter 5 integers\n";
	cin >> a;
	cout << a;
	return 0;
}
