/*
ID: caiweid3
PROG: window
LANG: C++              
*/

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <memory.h>
#include <algorithm>


using namespace std;

struct WINDOW
{
	WINDOW(){}
	WINDOW(char label, int x1, int y1, int x2, int y2, int h):
label(label), x1(min(x1,x2)), y1(min(y1,y2)), x2(max(x1,x2)), y2(max(y1,y2)), h(h){}
	char label;
	int x1, y1, x2, y2, h;
};

WINDOW win[100];
int total, maxh, minh;

bool cmp(const WINDOW &a, const WINDOW &b)
{
	return a.h < b.h;
}

int cut(int x1, int y1, int x2, int y2, int depth)
{
	if (depth == total)
		return (x2-x1) * (y2-y1);
	if (x2 <= win[depth].x1 || x1 >= win[depth].x2 || y2 <= win[depth].y1 || y1 >= win[depth].y2)
		return cut(x1, y1, x2, y2, depth+1);
	int ans = 0;
	int k1 = max(x1, win[depth].x1), k2 = min(x2, win[depth].x2);
	if (x1 < k1)
		ans += cut(x1, y1, k1, y2, depth+1);
	if (k2 < x2)
		ans += cut(k2, y1, x2, y2, depth+1);
	int l1 = max(y1, win[depth].y1);
	int l2 = min(y2, win[depth].y2);
	if (y1 < l1)
		ans += cut(k1, y1, k2, l1, depth+1);
	if (l2 < y2)
		ans += cut(k1, l2, k2, y2, depth+1);
	return ans;
}

int main() 
{
	freopen("window.in", "r", stdin);
	freopen("window.out", "w", stdout);
	char label, cmd[50];
	int x1, y1, x2, y2;

	while (cin >> cmd)
	{
		if (cmd[0] == 'w')
		{
			sscanf(cmd, "w(%c,%d,%d,%d,%d)", &label, &x1, &y1, &x2, &y2);
			win[total] = WINDOW(label, x1, y1, x2, y2, maxh);
			total++;
			maxh++;
		}
		if (cmd[0] == 't')
		{
			for (int i = 0; i < total; i++)
				if (win[i].label == cmd[2])
				{
					win[i].h = maxh++;
					break;
				}
		}
		if (cmd[0] == 'b')
		{
			for (int i = 0; i < total; i++)
				if (win[i].label == cmd[2])
				{
					if (win[i].h == maxh-1)
						maxh--;
					win[i].h = --minh;
					break;
				}
		}
		if (cmd[0] == 'd')
		{
			for (int i = 0; i < total; i++)
				if (win[i].label == cmd[2])
				{
					if (win[i].h == maxh-1)
						maxh--;
					if (win[i].h == minh)
						minh++;
					win[i] = win[total-1];
					total--;
				}
		}
		if (cmd[0] == 's')
		{
			sort(&win[0], &win[total], cmp);
			for (int i = 0; i < total; i++)
				if (win[i].label == cmd[2])
				{
					double ans = (double)cut(win[i].x1, win[i].y1, win[i].x2, win[i].y2, i+1) * 100 /(double)((win[i].y2-win[i].y1)*(win[i].x2-win[i].x1));
					printf("%.3lf\n", ans);
				}
		}
	}
	//system("pause");
}