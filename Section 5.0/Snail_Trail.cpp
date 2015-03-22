/*
ID: caiweid3
PROG: snail
LANG: C++              
*/

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <algorithm>
#include <memory.h>

using namespace std;
bool map[130][130], visited[130][130];
int n;
int lenth, ans;
int mov[4][2] = {{1,0}, {0,1}, {0,-1}, {-1,0}};


int Travel(int &x, int &y, int dir)
{
	int l = 0;
	while (1)
	{
		x = x+mov[dir][0];
		y = y+mov[dir][1];
		if (x>=0 && x<n && y>=0 && y<n && !map[x][y] && !visited[x][y])
		{
			visited[x][y] = true;;
			l++;
		}
		else
			return l;
	}
}

void dfs(int x, int y)
{
	int tmp, tmpx, tmpy;
	bool flag = true;
	for (int i = 0; i < 4; i++)
	{
		tmpx = x;
		tmpy = y;
		tmp = Travel(tmpx, tmpy, i);
		if (tmp!=0)
		{
			flag = false;
			lenth += tmp;
			if (tmpx>=0 && tmpx<n && tmpy>=0 && tmpy<n && visited[tmpx][tmpy])
			{
				if (lenth > ans)
					ans = lenth;
				lenth -= tmp;
				tmpx -= mov[i][0];
				tmpy -= mov[i][1];
				while (tmpx!=x || tmpy!=y)
				{
					visited[tmpx][tmpy] = false;
					tmpx = tmpx-mov[i][0];
					tmpy = tmpy-mov[i][1];
				}
				continue;
			}
			tmpx -= mov[i][0];
			tmpy -= mov[i][1];
			dfs(tmpx, tmpy);
			lenth -= tmp;
			while (tmpx!=x || tmpy!=y)
			{
				visited[tmpx][tmpy] = false;
				tmpx = tmpx-mov[i][0];
				tmpy = tmpy-mov[i][1];
			}
		}
	}
	if (flag)
	{
		if (lenth > ans)
			ans = lenth;
	}
}

int main()
{
	freopen("snail.in","r",stdin);
	freopen("snail.out","w",stdout);
	int b, r;
	char c;
	cin >> n >> b;
	for (int i = 0; i < b; i++)
	{
		cin >> c >> r;
		map[r-1][c-'A'] = true;
	}
	visited[0][0] = true;
	dfs(0, 0);
	cout << ans+1 << endl;
	//system("pause");
}