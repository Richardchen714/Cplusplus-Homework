#include<iostream>
#include<vector>
using namespace std;
template<typename T>
bool palindrome(vector<T>v)
{
	int i = 0;
	int j = v.size()-1;
	for (i, j; i<=j; i++, j--)
	{
		if (v[i] != v[j]) return false;
	}
	return true;
}
template<typename T1>
void outputVector(vector<T1>V)
{
	for (int i = 0; i <V.size(); i++)
		cout << V[i] << " ";
	if (palindrome(V)) cout << "is a palindrome\n";
	else cout << "is not a palindrome\n";
}
int main()
{
	vector<int>a = { 75,74,73,72,71,70,69,68,67,66,65 };
	vector<char>b = { 'K','J','I','H','G','F','G','H','I','J','K' };
	outputVector(a);
	outputVector(b);
	return 0;
}