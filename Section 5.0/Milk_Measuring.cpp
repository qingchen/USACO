/*
ID: caiweid3
PROG: milk4
LANG: C++              
*/

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <algorithm>
#include <memory.h>

using namespace std;

bool dp[20001];
int a[101], b[101];
int p, q, k;

bool dfs(int depth, int pos)
{
	if (depth == k)
	{
		memset(dp, false, sizeof(dp));
		dp[0] = true;
		for (int i = 0; i < depth; i++)
			for (int j = b[i]; j <= q; j++)
				if (dp[j-b[i]])
					dp[j] = true;
		if (dp[q])
			return true;
		else
			return false;
	}
	if (pos >= p)
		return false;
	b[depth] = a[pos];
	if (dfs(depth+1, pos+1))
		return true;
	if (dfs(depth, pos+1))
		return true;
	return false;
}

int main() 
{
	freopen("milk4.in", "r", stdin);
	freopen("milk4.out", "w", stdout);
	cin >> q >> p;
	for (int i = 0; i < p; i++)
		cin >> a[i];

	sort(&a[0], &a[p]);

	for (k = 1; k <= p; k++)
		if (dfs(0, 0))
			break;

	cout << k;
	for (int i = 0; i < k; i++)
		cout << " " << b[i];
	cout << endl;
	//system("pause");
}