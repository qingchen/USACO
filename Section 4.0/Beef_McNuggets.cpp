/*
ID: caiweid3
PROG: nuggets
LANG: C++              
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <memory.h>


using namespace std;

ofstream fout ("nuggets.out");
ifstream fin ("nuggets.in");

bool cando[70000];

inline int gcd(int a, int b)
{
	return b == 0 ? a : gcd(b, a%b);
}

int main() 
{
	int n;
	int num[10];

	fin >> n;
	for (int i = 0; i < n; i++)
		fin >> num[i];

	int tmp = num[0];
	for (int i = 1; i < n; i++)
		tmp = gcd(tmp, num[i]);

	if (tmp != 1)
	{
		fout << 0 <<endl;
		return 0;
	}

	cando[0] = true;
	for (int i = 1; i <= 65536 ; i++)
	{
		for (int j = 0; j < n; j++)
			if (i >= num[j] && cando[i-num[j]])
				cando[i] = true;
	}

	if (cando[1])
	{
		fout << 0 << endl;
		return 0;
	}

	for (int i = 65536; i >= 1; i--)
		if (!cando[i])
		{
			fout << i << endl;
			break;
		}
	//system("pause");
	return 0;
	
}
