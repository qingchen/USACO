/*
ID: caiweid3
PROG: rockers
LANG: C++              
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <memory.h>


using namespace std;

ofstream fout ("rockers.out");
ifstream fin ("rockers.in");

int dp[21][21][21];
int ca[21];

int main() 
{
	int n, t, m;
	fin >> n >> t >> m;
	for (int i = 1; i <= n; i++)
		fin >> ca[i];

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m ; j++)
		{
			for (int k = 0; k <= t; k++)
				dp[i][j][k] = dp[i][j-1][t];

			for (int k = 1; k <= t; k++)
			{
				dp[i][j][k] = max(dp[i-1][j][k], dp[i][j][k]);
				if (ca[i] <= k)
					dp[i][j][k] = max(dp[i][j][k], dp[i-1][j][k-ca[i]]+1);	
			}
		}
	}

	fout << dp[n][m][t] << endl;
	//system("pause");
	return 0;
	
}
