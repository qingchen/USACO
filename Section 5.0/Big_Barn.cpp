/*
ID: caiweid3
PROG: bigbrn
LANG: C++              
*/

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <algorithm>
#include <memory.h>

using namespace std;

int dp[1001][1001];
bool map[1001][1001];

int n;
int main() 
{
	freopen("bigbrn.in", "r", stdin);
	freopen("bigbrn.out", "w", stdout);
	int t, a, b;
	cin >> n >> t;
	for (int i = 0; i < t; i++)
	{
		cin >> a >> b;
		map[a][b] = true;
	}

	int ans = 0;
	for (int i = 1; i <=n ; i++)
		for (int j = 1; j<=n ;j++)
		{
			if (map[i][j])
				dp[i][j] = 0;
			else
				dp[i][j] = min(dp[i-1][j-1], min(dp[i][j-1], dp[i-1][j]))+1;
			if (dp[i][j] > ans)
				ans = dp[i][j];
		}
	cout << ans << endl;
	//system("pause");
}