/*
ID: caiweid3
PROG: fence9
LANG: C++              
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <memory.h>


using namespace std;

ofstream fout ("fence9.out");
ifstream fin ("fence9.in");



int main() 
{
	int n, m, p;
	int sum = 0;

	fin >> n >> m >> p;
	
	int x1, x2;
	for (int i = 1; i < m; i++)
	{
		x1 = i * n / (double)m;
		x2 = i * (n - p) / (double)m + p;
		if ((i * (n - p)) % m == 0)
			x2--;
		sum += x2 - x1;
	}
	fout << sum <<endl;
	//system("pause");
	return 0;
	
}
