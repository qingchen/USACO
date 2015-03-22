/*
ID: caiweid3
PROG: fence6
LANG: C++              
*/


#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;



struct SEGMENT
{
	int lenth, next[2][9];
};


SEGMENT s[101];
int n, start, ans;
bool appear[101];

void Search(int id, int direct, int lenth)
{
	if (lenth > ans)
		return;

	if (id == start && direct)
	{
		ans = lenth;
		return;
	}

	bool find;

	appear[id] = true;

	for (int i = 1; i <= s[id].next[1-direct][0]; i++)
	{
		if (appear[s[id].next[1-direct][1]])
			continue;

		find = false;
		for (int k = 1; k <= s[s[id].next[1-direct][i]].next[0][0]; k++)
		{
			if (s[s[id].next[1-direct][i]].next[0][k] == id)
			{
				find = true;
				break;
			}
		}

		if (find)
			Search(s[id].next[1-direct][i], 0, lenth+s[id].lenth);
		else
			Search(s[id].next[1-direct][i], 1, lenth+s[id].lenth);
	}

	appear[id] = false;
}

int main() 
{
	freopen("fence6.in","r",stdin);
    freopen("fence6.out","w",stdout);
	ans = 0x7fffffff;
	cin >> n;
	int tmp;

	for (int i = 0; i < n; i++)
	{
		cin >> tmp;
		cin >> s[tmp].lenth >> s[tmp].next[0][0] >> s[tmp].next[1][0];
		for (int j = 1; j <= s[tmp].next[0][0]; j++)
			cin >> s[tmp].next[0][j];
		for (int j = 1; j <= s[tmp].next[1][0]; j++)
			cin >> s[tmp].next[1][j];
	}

	bool find;
	for (int i = 1; i <= n; i++)
	{
		start = i;
		for (int j = 1; j <= s[i].next[0][0]; j++)
		{
			find = false;
			for (int k = 1; k <= s[s[i].next[0][j]].next[0][0]; k++)
			{
				if (s[s[i].next[0][j]].next[0][k] == i)
				{
					find = true;
					break;
				}
			}
			if (find)
				Search(s[i].next[0][j], 0, s[i].lenth);
			else
				Search(s[i].next[0][j], 1, s[i].lenth);
		}
	}

	cout << ans << endl;
	//system("pause");
	return 0;
	
}
