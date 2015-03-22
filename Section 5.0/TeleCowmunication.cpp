/*
ID: caiweid3
PROG: telecow
LANG: C++              
*/

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <memory.h>
#include <algorithm>
#include <queue>


using namespace std;

const int oo = 10000000;
int G[201][201], pG[201][201];
int source, sink, n;
int num[201], d[201], pre[201], search_record[201];
bool full[101];

void RevBFS()
{
	for (int i = 1; i <= n; i++)
	{
		d[i] = n;
		num[d[i]]++;
	}

	int now = sink;
	num[d[now]]--;
	d[now] = 0;
	num[d[now]]++;
	queue<int> s;
	s.push(now);

	while (!s.empty())
	{
		now = s.front();
		s.pop();
		for (int i = 1; i <= n; i++)
			if (G[i][now] && d[i]==n)
			{
				num[d[i]]--;
				d[i] = d[now]+1;
				num[d[i]]++;
				s.push(i);
			}
	}
}

int Augment()
{
	int minv = 0x7fffffff;
	for (int i = sink; i != source; i = pre[i])
		if (G[pre[i]][i] < minv)
			minv = G[pre[i]][i];
	for (int i = sink; i != source; i = pre[i])
	{
		G[pre[i]][i] -= minv;
		G[i][pre[i]] += minv;
	}

	return minv;
}

int Retreat(int &current)
{
	int minv = n-1;
	for (int i = 1; i <= n; i++)
		if (G[current][i] && d[i]<minv)
			minv = d[i];

	int res = d[current];
	num[d[current]]--;
	d[current] = minv + 1;
	num[d[current]]++;
	
	if (current != source)
		current = pre[current];
	return num[res];
}

int FindMaxFlow()
{
	RevBFS();
	int i, current = source, flow = 0;

	for (i = 1; i <= n; i++)
		search_record[i] = 1;

	while (d[source] < n)
	{
		for (i = search_record[current]; i <= n; i++)
			if (G[current][i]>0 && d[i] == d[current]-1)
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
	freopen("telecow.in", "r", stdin);
	freopen("telecow.out", "w", stdout);
	int m, c1, c2, a, b;
	cin >> n >> m >> c1 >> c2;
	if (c1 > c2)
		swap(c1, c2);
	n = n*2;
	source = c1*2;
	sink = c2*2-1;
	for (int i = 0; i < m; i++)
	{
		cin >> a >> b;
		if (b < a)
			swap(a, b);
		G[a*2-1][a*2] = 1;
		G[b*2-1][b*2] = 1;
		G[a*2][b*2-1] = oo;
		G[b*2][a*2-1] = oo;
	}

	memcpy(pG,G,201*201*sizeof(int));
	int ans = FindMaxFlow();
	int point[101], pos = 0, flow = ans;
	

	for (int i = 1; i <= n/2; i++)
	{
		if(G[i*2-1][i*2])
			continue;
		else
			full[i] = true;
	}
	for (int i = 1; i <= n/2; i++)
	{
		if (!full[i])
			continue;
		memcpy(G,pG,201*201*sizeof(int));
		int tmp;
		G[i*2-1][i*2] -= 1;
		tmp = FindMaxFlow();
		if (flow-tmp == 1)
		{
			point[pos++] = i;
			pG[i*2-1][i*2] -= 1;
			flow -= 1;
		}
	}

	cout << ans << endl;
	for (int i = 0; i < pos-1; i++)
		cout << point[i] << " ";
	cout << point[pos-1] << endl;
	//system("pause");
}