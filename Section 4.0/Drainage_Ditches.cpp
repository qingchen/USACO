/*
ID: caiweid3
PROG: ditch
LANG: C++              
*/

#include <iostream>
#include <fstream>
#include <queue>
#include <stdlib.h>

using namespace std;

const int maxn = 201;
int current, n, sink, source;
int d[maxn], num[maxn], search_record[maxn], pre[maxn];
int G[maxn][maxn];

void RevBFS()
{
	for (int i = 1; i <= n; i++)
	{
		d[i] = n;
		num[d[i]]++;
	}

	num[d[sink]]--;
	d[sink] = 0;
	num[d[sink]]++;

	queue<int> q;
	q.push(sink);
	int tmp;
	while (!q.empty())
	{
		tmp = q.front();
		q.pop();
		for (int i = 1; i <= n; i++)
			if (d[i]==n && G[i][tmp])
			{
				num[d[i]]--;
				d[i] = d[tmp] + 1;
				num[d[i]]++;
				q.push(i);
			}
	}
}

int Augment()
{
	int min_capacity = 0x7fffffff;

	for (int i = sink; i != source; i = pre[i])
		if (G[pre[i]][i] < min_capacity)
			min_capacity = G[pre[i]][i];

	for (int i = sink; i != source; i = pre[i])
	{
		G[pre[i]][i] -= min_capacity;
		G[i][pre[i]] += min_capacity;
	}

	return min_capacity;
}

int Retreat(int &current)
{
	int min_d = n - 1;

	for (int j = 1; j <= n; j++)
		if (G[current][j]>0 && d[j] < min_d)
			min_d = d[j];

	int res = d[current];
	num[d[current]]--;
	d[current] = min_d + 1;
	num[d[current]]++;

	if (current != source)
		current = pre[current];
	
	return num[res];
}

int FindMaxFlow()
{
	int flow = 0;
	RevBFS();

	for (int i = 1; i <= n; i++)
		search_record[i] = 1;
	current = source;

	int i;
	while (d[source] < n)
	{
		for (i = search_record[current]; i <= n; i++)
			if (G[current][i] > 0 && d[current] == d[i] + 1)
				break;

		if (i <= n)
		{
			search_record[current] = i;
			pre[i] = current;
			current = i;

			if (current == sink)
			{
				flow += Augment();
				current = source;
			}
		}
		else
		{
			search_record[current] = 1;

			if (Retreat(current) == 0)
				break;
		}
	}
	return flow;
}

int main()
{
	freopen("ditch.in","r",stdin);
	freopen("ditch.out","w",stdout);
	int m, a, b, v;
	cin >> m >> n;
	for (int i = 0; i < m; i++)
	{
		cin >> a >> b >> v;
		G[a][b] += v;
	}
	source = 1;
	sink = n;
	cout << FindMaxFlow() << endl;
	//system("pause");
}