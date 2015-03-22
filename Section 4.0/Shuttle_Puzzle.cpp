/*
ID: caiweid3
PROG: shuttle
LANG: C++              
*/

#include <iostream>
#include <string>
#include <fstream>
#include <memory.h>
#include <stdlib.h>
#include <queue>

using namespace std;

string s;
int ans[2000];
int pos, n;

bool dfs(const int &p)
{
	if (p == n)
	{
		bool flag = true;
		for (int i = 0; i < n; i++)
			if (s[i] != 'b')
			{
				flag = false;
				break;
			}
		if (flag)
			return true;
	}
	if (p>1 && s[p-2]=='w' && s[p-1]=='b')
	{
		ans[pos] = p-2+1;
		pos++;
		s[p] = 'w';
		s[p-2] = ' ';
		if (dfs(p-2))
			return true;
		pos--;
		s[p] = ' ';
		s[p-2] = 'w';
	}
	if (p>0 && s[p-1]=='w')
	{
		ans[pos] = p-1+1;
		pos++;
		s[p] = 'w';
		s[p-1] = ' ';
		if (dfs(p-1))
			return true;
		pos--;
		s[p] = ' ';
		s[p-1] = 'w';
	}
	if (p<2*n && s[p+1]=='b')
	{
		ans[pos] = p+1+1;
		pos++;
		s[p] = 'b';
		s[p+1] = ' ';
		if (dfs(p+1))
			return true;
		pos--;
		s[p] = ' ';
		s[p+1] = 'b';
	}
	if (p<2*n-1 && s[p+1]=='w' && s[p+2]=='b')
	{
		ans[pos] = p+2+1;
		pos++;
		s[p] = 'b';
		s[p+2] = ' ';
		if (dfs(p+2))
			return true;
		pos--;
		s[p] = ' ';
		s[p+2] = 'b';
	}
	return false;
}

int main()
{
	freopen("shuttle.in","r",stdin);
	freopen("shuttle.out","w",stdout);
	cin >> n;
	for (int i = 0; i < n; i++)
		s += 'w';
	s += ' ';
	for (int i = 0; i < n; i++)
		s += 'b';
	dfs(n);
	for (int i = 0, j = 1; i < pos; i++, j++)
	{
		if (j!=20 && i!=pos-1)
			cout << ans[i] << " ";
		else
		{
			cout << ans[i] << endl;
			j = 0;
		}
	}
	//system("pause");
}