/*
ID: caiweid3
PROG: milk6
LANG: C++              
*/

#include <iostream>
#include <string>
#include <fstream>
#include <memory.h>
#include <stdlib.h>
#include <queue>

using namespace std;

int source, sink, n, pos;
int d[35], num[35], pre[35], search_record[35], ans[1001];
int G[35][35], pG[35][35];
bool full[1001];

struct Edge
{
	int a, b, v;
}e[1001];

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
		{
			if (d[i]==n && G[i][tmp])
			{
				num[d[i]]--;
				d[i] = d[tmp]+1;
				num[d[i]]++;
				q.push(i);
			}
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

	int res = num[d[current]];
	num[d[current]]--;
	d[current] = minv + 1;
	num[d[current]]++;
	
	if (current != source)
		current = pre[current];
	return res;
}

int FindMaxFlow()
{
	int i, current, flow = 0;
	RevBFS();
	for (i = 1; i <= n; i++)
		search_record[i] = 1;
	current = source;

	while (d[source] < n)
	{
		for (i = search_record[current]; i <= n; i++)
			if (G[current][i] && d[current] == d[i]+1)
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
	freopen("milk6.in","r",stdin);
	freopen("milk6.out","w",stdout);
	int m, a, b, c;
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> a >> b >> c;
		G[a][b] += c+1;
		e[i].a = a;
		e[i].b = b;
		e[i].v = c+1;
	}
	source = 1;
	sink = n;
	memcpy(pG,G,35*35*sizeof(int));
	int flow = FindMaxFlow();
	int tflow = flow;
	for (int i = 0; i < m; i++)
	{
		if(G[e[i].a][e[i].b])
			continue;
		else
			full[i] = true;
	}
	for (int i = 0; i < m; i++)
	{
		if (!full[i])
			continue;
		memcpy(G,pG,35*35*sizeof(int));
		int tmp;
		G[e[i].a][e[i].b] -= e[i].v;
		tmp = FindMaxFlow();
		if (tflow-tmp == e[i].v)
		{
			ans[pos++] = i+1;
			pG[e[i].a][e[i].b] -= e[i].v;
			tflow -= e[i].v;
		}
	}

	cout << flow-pos << " " << pos << endl;
	for (int i = 0; i < pos; i++)
		cout << ans[i] << endl;

	//system("pause");
}