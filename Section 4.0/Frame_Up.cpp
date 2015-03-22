/*
ID: caiweid3
PROG: frameup
LANG: C++              
*/

#include <iostream>
#include <string>
#include <fstream>
#include <memory.h>
#include <stdlib.h>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

char map[40][40];
bool appear[40];
int h, w;
int lui[30], luj[30], rli[30], rlj[30], r[30], l[30];
string ans(30,0);
int pos;
vector <string> v;


inline bool In(const int &x, const int &y, const char &c)
{
	if (x>=0 && x<=h && y>=0 &&y <=w && (map[x][y]==c || (map[x][y]!='.' && !appear[map[x][y]-'A'])))
		return true;
	else
		return false;
}

bool Judge(const char &c)
{
	int p = c-'A';
	int tmpi, tmpj;
	tmpj = luj[p]+1, tmpi = lui[p]+1;
	while (In(lui[p], tmpj, c))
		tmpj++;
	tmpj--;
	if (tmpj < r[p])
		return false;
	while (In(tmpi, r[p], c))
		tmpi++;
	tmpi--;
	if (tmpi < rli[p])
		return false;
	tmpj = r[p], tmpi = rli[p];
	while (In(rli[p], tmpj, c))
		tmpj--;
	tmpj++;
	if (tmpj > l[p])
		return false;
	while (In(tmpi, l[p], c))
		tmpi--;
	tmpi++;
	if (tmpi > lui[p])
		return false;
	return true;
}

bool dfs()
{
	bool flag = true;
	for (int i = 0; i < 26; i++)
		if (appear[i])
		{
			flag = false;
			break;
		}
	if (flag)
	{
		string tmp;
		for (int i = pos-1; i >=0; i--)
			tmp += ans[i];
		v.push_back(tmp);
		return true;
	}
	for (int i = 0; i < 26; i++)
	{
		if (appear[i])
		{
			if (Judge('A'+i))
			{
				appear[i] = false;
				ans[pos] = 'A'+i;
				pos++;
				dfs();
				appear[i] = true;
				pos--;
			}
		}
	}
}
int main()
{
	freopen("frameup.in","r",stdin);
	freopen("frameup.out","w",stdout);
	cin >> h >> w;
	for (int i = 0; i < 26; i++)
		l[i] = lui[i] = luj[i] = 1000;
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
		{
			cin >> map[i][j];
			if (!appear[map[i][j]-'A'])
				appear[map[i][j]-'A'] = true;
			if (map[i][j] == '.')
				continue;
			if (j > r[map[i][j]-'A'])
				r[map[i][j]-'A'] = j;
			if (j < l[map[i][j]-'A'])
				l[map[i][j]-'A'] = j;
			if (i<=lui[map[i][j]-'A'] && j<=luj[map[i][j]-'A'])
			{
				lui[map[i][j]-'A'] = i;
				luj[map[i][j]-'A'] = j;
			}
			if (i>=rli[map[i][j]-'A'])
			{
				rli[map[i][j]-'A'] = i;
				rlj[map[i][j]-'A'] = j;
			}
		}
	dfs();
	sort(v.begin(), v.end());
	for (vector<string>::iterator it=v.begin(); it!=v.end(); it++)
		cout << *it << endl;
	//system("pause");
}