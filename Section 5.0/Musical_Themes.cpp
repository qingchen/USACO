/*
ID: caiweid3
PROG: theme
LANG: C++              
*/

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <algorithm>

using namespace std;

int dp[5001];
int a[5001];
int n;

int main()
{
	freopen("theme.in","r",stdin);
	freopen("theme.out","w",stdout);
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	int ans = 0;
	dp[n-1] = 1;

	for (int i = n-7; i >= 0; i--)
		for (int j = i+5; j < n-1; j++)
		{
			if (a[i+1]-a[i] == a[j+1]-a[j])
			{
				//dp[j] = max(dp[j], dp[j+1]+1);
				dp[j] = dp[j+1]+1;
				if (dp[j] > j-i)
					dp[j] = j-i;
				if (dp[j] > 4)
					ans = max(ans, dp[j]);
			}
			else
				dp[j] = 1;
		}
	cout << ans << endl;
	//system("pause");
}