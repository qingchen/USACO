/*
ID: caiweid3
PROG: hidden
LANG: C++              
*/

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <memory.h>
#include <algorithm>

using namespace std;

char s[200001];

int main() 
{
	freopen("hidden.in", "r", stdin);
	freopen("hidden.out", "w", stdout);
	int n, tmp;
	cin >> n;
	tmp = 0;
	while (tmp < n)
	{
		cin >> s + tmp;
		tmp += 72;
	}
	memcpy(s+n, s, n*sizeof(char));
	int i = 0, j = 1, k;
	while (j < n)
	{
		k = 0;
		while (s[i+k] == s[j+k] && k < n-1)
			k++;
		if (k >= n-1)
			break;
		if (s[i+k] > s[j+k])
		{
			i = j;
			j++;
		}
		else
			j = j+k+1;
	}

	cout << i << endl;
	//system("pause");
}