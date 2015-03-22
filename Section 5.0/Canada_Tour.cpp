/*
ID: caiweid3
PROG: tour
LANG: C++              
*/

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <memory.h>
#include <algorithm>
#include <map>


using namespace std;

map<string, int> h;
int dp[101][101];
bool g[101][101];
int n;


int main() 
{
	freopen("tour.in", "r", stdin);
	freopen("tour.out", "w", stdout);
	int m, a, b;
	string s;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		cin >> s;
		h.insert(pair<string, int> (s, i));
	}
	for (int i = 1; i <= m; i++)
	{
		cin >> s;
		a = h[s];
		cin >> s;
		b = h[s];
		g[a][b] = g[b][a] = true;
	}

	memset(dp, 0x80, sizeof(dp));
	dp[1][1] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = i+1; j <= n; j++)
			for (int k = 1; k < j; k++)
			{
				if (g[k][j] && dp[i][k]>0)
				{
					dp[i][j] = max(dp[i][j], dp[i][k]+1);
					dp[j][i] = dp[i][j];
				}
			}

	int ans = 1;
	for (int i = 1; i <= n; i++)
			if (g[i][n])
				ans = max(ans, dp[i][n]);

	cout << ans << endl;
	//system("pause");
}