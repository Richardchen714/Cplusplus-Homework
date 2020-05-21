#include<iostream>
#include<cmath>
#include<bitset>
#include<stack>
using namespace std;
int main()
{
	bitset<1024>b;
	b.set();
	b[2] = 1;//is prime
	for (int i = 2; i < 1024; i++)
	{
		for (int j = 2; j * i < 1024; j++)
			if(b[i*j]) b.flip(i * j);//set b[i*j]=0
		
	}
	cout << "The prime numbers in the range from 2 to 1023 are:" << endl;
	for (int i = 2; i < 1024; i++)
		if (b[i]) cout << i<<" ";
	cout << endl;
	int number, temp;
	stack<int>s;
	while (true)
	{
		cout << "\nEnter a value from 2 to 1023 (-1 to end):";
		cin >> number;
		if (number == -1) break;
		if (number > 1023 || number < 0)
		{
			cout << "Invalid number" << endl;
			continue;
		}
		if (b[number]) cout << number << " is a prime number" << endl;
		else
		{
			temp = number;
			while (temp != 1)
			{
				for (int i = temp; i > 1; i--)
				{
					if ((b[i]) && (temp % i == 0))
					{
						s.push(i);
						temp = temp / i;
					}
				}
			}
			cout << number << " is not a prime number" << endl;
			cout << "The unique prime factorization of " << number << " is: ";
			while (!s.empty())
			{
				cout << s.top();
				if (s.size() != 1) cout << " * ";
				s.pop();
			}
			cout << endl;
		}
	}
	return 0;
}

