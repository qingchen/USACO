/*
ID: caiweid3
PROG: job
LANG: C++              
*/

#include <iostream>
#include <fstream>
#include <memory.h>
#include <stdlib.h>

using namespace std;


int main()
{
	freopen("job.in","r",stdin);
	freopen("job.out","w",stdout);
	int n;
	int e[2][31], delay[31], cost[2][1001];
	cin >> n >> e[0][0] >> e[1][0];
	for (int i = 1; i <= e[0][0]; i++)
		cin >> e[0][i];
	for (int i = 1; i <= e[1][0]; i++)
		cin >> e[1][i];

	int pos, min;
	for (int i = 0; i < 2; i++)
	{
		memset(delay, 0, sizeof(delay));
		for (int k = 1; k <= n; k++)
		{
			min = 100000;
			for (int j = 1; j <= e[i][0]; j++)
			{
				if (min > e[i][j] + delay[j])
				{
					pos = j;
					min = e[i][j] + delay[j];
				}
			}
			delay[pos] += e[i][pos];
			cost[i][k] = delay[pos];
		}
	}

	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		if (cost[0][i] + cost[1][n-i+1] > ans)
			ans = cost[0][i] + cost[1][n-i+1];
	}
	cout << cost[0][n] << " " << ans << endl;
	//system("pause");
}