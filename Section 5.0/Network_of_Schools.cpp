/*
ID: caiweid3
PROG: schlnet
LANG: C++              
*/

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <memory.h>


using namespace std;

bool in_stack[101];
bool m[101][101], con[101][101];
int n, ind, count, top;
int low[101], num[101], belong[101], in_degree[101], out_degree[101];
int stack[101];

void Tarjan(const int &i)
{
	low[i] = num[i] = ++ind;
	in_stack[i] = true;
	stack[++top] = i;

	bool flag = false;
	int j;
	for (j = 1; j <= n; j++)
	{
		if (m[i][j])
		{
			flag = true;
			if (!num[j])
			{
				Tarjan(j);
				if (low[i] > low[j])
					low[i] = low[j];
			}
			else if (in_stack[j] && low[i] > num[j])
				low[i] = num[j];
		}
	}

	if (low[i] == num[i])
	{
		count++;
		do
		{
			j = stack[top--];
			in_stack[j] = false;
			belong[j] = count;
		} while (i!=j); 
	}

}

int main() 
{
	freopen("schlnet.in", "r", stdin);
	freopen("schlnet.out", "w", stdout);
	int tmp;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		while (cin >> tmp)
		{
			if (!tmp)
				break;
			if (tmp == i)
				continue;
			m[i][tmp] = true;
		}
	}
	for (int i = 1; i <= n; i++)
		if (!num[i])
			Tarjan(i);
	
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		{
			if (m[i][j])
			{
				if (belong[i] == belong[j])
					continue;
				else
				{
					con[belong[i]][belong[j]] = true;
					in_degree[belong[j]]++;
					out_degree[belong[i]]++;
				}
			}
		}
	int zero_in = 0, zero_out = 0;

	for (int i = 1; i <= count; i++)
	{
		if (!in_degree[i])
			zero_in++;
		if (!out_degree[i])
			zero_out++;
	}

	cout << zero_in << endl;
	if (count == 1)
		cout << 0 << endl;
	else
		cout << max(zero_in, zero_out) << endl;
	//system("pause");
}