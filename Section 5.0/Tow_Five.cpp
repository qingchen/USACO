/*
ID: caiweid3
PROG: twofive
LANG: C++              
*/

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <memory.h>
#include <algorithm>

using namespace std;

int maxr[6], maxc[6], shape[6];
int record[6][6][6][6][6];
bool used[26];

int Search(int a, int b, int c, int d, int e, int depth)
{
	if (a > 5 || b > 5 || c > 5 || d > 5 || e > 5)
		return 0;
	if (record[a][b][c][d][e])
		return record[a][b][c][d][e];
	if (used[depth])
		return record[a][b][c][d][e] = Search(a, b, c, d, e, depth+1);
	int res = 0;
	if (a < 5 && depth > maxr[0] && depth > maxc[a])
		res += Search(a+1, b, c, d, e, depth+1);
	if (a > b && depth > maxr[1] && depth > maxc[b])
		res += Search(a, b+1, c, d, e, depth+1);
	if (b > c && depth > maxr[2] && depth > maxc[c])
		res += Search(a, b, c+1, d, e, depth+1);
	if (c > d && depth > maxr[3] && depth > maxc[d])
		res += Search(a, b, c, d+1, e, depth+1);
	if (d > e && depth > maxr[4] && depth > maxc[e])
		res += Search(a, b, c, d, e+1, depth+1);
	return record[a][b][c][d][e] = res;
}

int Calculate(const int ans[], int num, int n)
{
	int r, c;
	int tmp[26];
	memcpy(tmp, ans, sizeof(tmp));
	tmp[n] = num;
	memset(maxr, 0, sizeof(maxr));
	memset(maxc, 0, sizeof(maxc));
	memset(shape, 0, sizeof(shape));
	for (int i = 0; i <= n; i++)
	{
		r = i / 5;
		c = i % 5;
		if (tmp[i] < maxr[r] || tmp[i] < maxc[c])
			return 0;
		if (tmp[i] > maxr[r])
			maxr[r] = tmp[i];
		if (tmp[i] > maxc[c])
			maxc[c] = tmp[i];
		shape[r]++;
	}

	memset(record, 0, sizeof(record));
	record[5][5][5][5][5] = 1;
	return Search(shape[0], shape[1], shape[2], shape[3], shape[4], 0);
}

void OrderToWords(const int &n, char *ans)
{
	int tmp = n, result, i, j;
	int num[26];
	memset(used, false, sizeof(used));
	num[0] = 0;
	used[0] = true;
	for (i = 1; i < 25; i++)
	{
		for (j = 1; j < 25; j++)
			if (!used[j])
			{
				used[j] = true;
				result = Calculate(num, j, i);
				used[j] = false;
				tmp -= result;
				if (tmp <= 0)
					break;
			}
		tmp += result;
		used[j] = true;
		num[i] = j;
	}
	for (int i = 0; i < 25; i++)
		ans[i] = num[i] + 'A';
	ans[25] = 0;
}

void WordsToOrder(const char *str, int &ans)
{
	ans = 0;
	memset(used, false, sizeof(used));
	int tmp[26];
	for (int i = 0; i < 25; i++)
		tmp[i] = str[i] - 'A';

	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < tmp[i]; j++)
		{
			if (!used[j])
			{
				used[j] = true;
				ans += Calculate(tmp, j, i);
				used[j] = false;
			}
		}
		used[tmp[i]] = true;
	}

	ans++;
}

int main() 
{
	freopen("twofive.in", "r", stdin);
	freopen("twofive.out", "w", stdout);
	char cmd;
	int n;
	char res[26];
	cin >> cmd;
	if (cmd == 'N')
	{
		cin >> n;
		OrderToWords(n, res);
		cout << res << endl;
	}
	else
	{
		cin >> res;
		WordsToOrder(res, n);
		cout << n << endl;
	}
	//system("pause");
}
