/*
ID: caiweid3
PROG: picture
LANG: C++              
*/

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <memory.h>
#include <algorithm>

using namespace std;

struct LINE
{
	LINE(){}
	LINE(bool _start, int _s, int _e, int _h):start(_start), s(_s), e(_e), h(_h){}
	bool start;
	int s, e, h;
};

bool cmp(const LINE &a, const LINE &b)
{
	if (a.h != b.h)
		return a.h < b.h;
	else if (a.start != b.start)
		return a.start;
	else
		return false;
}

LINE h[10000], v[10000];
int tmpl[21000];
int n;

int main() 
{
	freopen("picture.in", "r", stdin);
	freopen("picture.out", "w", stdout);
	cin >> n;
	int x1, y1, x2, y2;
	for (int i = 0; i < n; i++)
	{
		cin >> x1 >> y1 >> x2 >> y2;
		h[i*2] = LINE(true, x1, x2, y1);
		h[i*2+1] = LINE(false, x1, x2, y2);
		v[i*2] = LINE(true, y1, y2, x1);
		v[i*2+1] = LINE(false, y1, y2, x2);
	}

	int ans = 0;

	int *level = &tmpl[10500];
	sort(&h[0], &h[n*2], cmp);
	for (int i = 0; i < n*2; i++)
	{
		if (h[i].start)
		{
			for (int k = h[i].s; k < h[i].e; k++)
			{
				level[k]++;
				if (level[k] == 1)
					ans++;
			}
		}
		else
		{
			for (int k = h[i].s; k < h[i].e; k++)
			{
				level[k]--;
				if (level[k] == 0)
					ans++;
			}
		}
	}

	sort(&v[0], &v[n*2], cmp);
	memset(tmpl, 0, sizeof(tmpl));
	
	for (int i = 0; i < n*2; i++)
	{
		if (v[i].start)
		{
			for (int k = v[i].s; k < v[i].e; k++)
			{
				level[k]++;
				if (level[k] == 1)
					ans++;
			}
		}
		else
		{
			for (int k = v[i].s; k < v[i].e; k++)
			{
				level[k]--;
				if (level[k] == 0)
					ans++;
			}
		}
	}
	cout << ans << endl;
	//system("pause");
}