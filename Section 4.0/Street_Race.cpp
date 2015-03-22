/*
ID: caiweid3
PROG: race3
LANG: C++              
*/

#include <iostream>
#include <fstream>
#include <memory.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;
bool G[50][50];
bool visited[50], visited2[50];
int unavoidable[50], cut[50];
int num_unavoid, n, end_point, num_cut;

bool DFS(const int &a)
{
	if (a == n-1)
		return true;
	for (int i = 1; i < n; i++)
	{
		if (G[a][i] && !visited[i])
		{
			visited[i] = true;
			if (DFS(i))
				return true;
			visited[i] = false;
		}
	}
	return false;
}

void DFS2(const int &a)
{
	if (a == end_point)
		return;
	for (int i = 1; i < n; i++)
	{
		if (G[a][i] && !visited[i])
		{
			visited[i] = true;
			DFS2(i);
		}
	}
	return;
}

void DFS3(const int &a)
{
	if (a == n-1)
		return;
	for (int i = 0; i < n; i++)
	{
		if (G[a][i] && !visited2[i])
		{
			visited2[i] = true;
			DFS3(i);
		}
	}
	return;
}

int main()
{
	freopen("race3.in","r",stdin);
	freopen("race3.out","w",stdout);
	int tmp;
	for (n = 0; ; n++)
	{
		cin >> tmp;
		if (tmp == -1)
			break;
		if (tmp == -2)
			continue;
		while (tmp != -2)
		{
			G[n][tmp] = true;
			cin >> tmp;
		}
	}
	for (int i = 1; i < n-1; i++)
	{
		memset(visited, false, sizeof(visited));
		visited[i] = visited[0] = true;
		if (!DFS(0))
			unavoidable[num_unavoid++] = i;
	}
	bool flag;
	for (int i = 0; i < num_unavoid; i++)
	{
		flag = true;
		memset(visited, false, sizeof(visited));
		memset(visited2, false, sizeof(visited2));
		end_point = unavoidable[i];
		DFS2(0);
		DFS3(end_point);
		visited[0] = true;

		for (int i = 0; i < n-1; i++)
			if (i!=end_point && visited[i] && visited2[i])
			{
				flag = false;
				break;
			}
		if (flag)
			cut[num_cut++] = end_point;
	}
	cout << num_unavoid;
	sort(unavoidable, unavoidable+num_unavoid);
	for (int i = 0; i < num_unavoid; i++)
		cout << " " << unavoidable[i];
	cout << endl;
	cout << num_cut;
	sort(cut, cut+num_cut);
	for (int i = 0; i < num_cut; i++)
		cout <<" " << cut[i];
	cout << endl;
	//system("pause");
}