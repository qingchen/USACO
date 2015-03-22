/*
ID: caiweid3
PROG: fc
LANG: C++              
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <stdlib.h>
#include <vector>
#include <algorithm>

using namespace std;

struct POINT
{
	double x, y;
};

POINT p[10001];
POINT stack[10001];
int n, top;
const double eps = 1e-10;
double midx, midy;

bool cmp(const POINT &a, const POINT &b)
{
	return atan2(a.y-midy, a.x-midx) < atan2(b.y-midy, b.x-midx);
}

double CrossProduct(const POINT &as, const POINT &ae, const POINT &bs, const POINT &be)
{
	POINT a, b;
	a.x = as.x - ae.x;
	a.y = as.y - ae.y;
	b.x = bs.x - be.x;
	b.y = bs.y - be.y;
	return a.x*b.y - a.y*b.x;
}

inline double Dis(const POINT &a, const POINT &b)
{
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

int main()
{
	freopen("fc.in","r",stdin);
	freopen("fc.out","w",stdout);
	midx = midy = 0;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> p[i].x >> p[i].y;
		midx += p[i].x / n;
		midy += p[i].y / n;
	}
	sort(&p[0], &p[n], cmp);
	stack[top++] = p[0];
	stack[top++] = p[1];
	for (int i = 2; i < n-1; i++)
	{
		while (top>1 && CrossProduct(stack[top-2], stack[top-1], stack[top-1], p[i])<0)
			top--;
		stack[top++] = p[i];
	}

	while (top>1 && CrossProduct(stack[top-2], stack[top-1], stack[top-1], p[n-1])<0)
		top--;
	bool flag = true;
	int start = 0;
	POINT t = p[n-1];
	while (flag)
	{
		flag = false;
		if (top-start>=2 && CrossProduct(t, stack[top-1], stack[start], t)<0)
		{	
			t = stack[top-1];
			top--;
			flag = true;
		}
		if (top-start>=2 && CrossProduct(stack[start], t, stack[start+1], stack[start])<0)
		{
			start = start+1;
			flag = true;
		}
	}
	stack[top++] = t;
	stack[top] = stack[start];
	double ans = 0;
	for (int i = start; i <top; i++)
		ans += Dis(stack[i], stack[i+1]);
	printf("%.2lf\n", ans);
	//system("pause");
}