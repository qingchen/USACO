/*
ID: caiweid3
PROG: charrec
LANG: C++              
*/

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <memory.h>
#include <algorithm>


using namespace std;

char cha_table[30] = " abcdefghijklmnopqrstuvwxyz";
char font[27][20][20];
char input_c[1201][20];
int dis[1201][27][20];
int lines[1201];
int pattern[1201];
int f[1201];
int n;
const int oo = 20*20*1200;

int main() 
{
	freopen("charrec.in", "r", stdin);
	freopen("charrec.out", "w", stdout);
	ifstream fin("font.in");
	fin >> n;
	for (int i = 0; i < 27; i++)
		for (int j = 0; j < 20; j++)
			fin >> font[i][j];

	int *dp = &f[1];
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> input_c[i];
		for (int c = 0; c < 27; c++)
			for (int j = 0; j < 20; j++)
				for (int k = 0; k < 20; k++)
					if (font[c][j][k] != input_c[i][k])
						dis[i][c][j]++;
		dp[i] = oo;
	}

	int tmp;
	for (int i = 0; i < n; i++)
	{
		if (i + 18 < n)
		{
			for (int j = 0; j < 27; j++)
			{
				tmp = 0;
				for (int k = 1; k < 20; k++)
					tmp += dis[i+k-1][j][k];
				if (dp[i+18] == oo || dp[i+18] > dp[i-1] + tmp)
				{
					dp[i+18] = dp[i-1] + tmp;
					lines[i+18] = 19;
					pattern[i+18] = j;
				}
				for (int k = 1; k < 20; k++)
				{
					tmp -= dis[i+k-1][j][k];
					tmp += dis[i+k-1][j][k-1];
					if (dp[i+18] > dp[i-1] + tmp)
					{
						dp[i+18] = dp[i-1] + tmp;
						lines[i+18] = 19;
						pattern[i+18] = j;
					}
				}
			}
		}
		if (i + 19 < n)
		{
			for (int j = 0; j < 27; j++)
			{
				tmp = 0;
				for (int k = 0; k < 20; k++)
					tmp += dis[i+k][j][k];
				if (dp[i+19] == oo || dp[i+19] > dp[i-1] + tmp)
				{
					dp[i+19] = dp[i-1] + tmp;
					lines[i+19] = 20;
					pattern[i+19] = j;
				}
			}
		}
		if (i + 20 < n)
		{
			for (int j = 0; j < 27; j++)
			{
				tmp = 0;
				for (int k = 0; k < 20; k++)
					tmp += dis[i+k+1][j][k];
				if (dp[i+20] == oo || dp[i+20] > dp[i-1] + tmp)
				{
					dp[i+20] = dp[i-1] + tmp;
					lines[i+20] = 21;
					pattern[i+20] = j;
				}
				for (int k = 0; k < 20; k++)
				{
					tmp -= dis[i+k+1][j][k];
					tmp += dis[i+k][j][k];
					if (dp[i+20] > dp[i-1] + tmp)
					{
						dp[i+20] = dp[i-1] + tmp;
						lines[i+20] = 21;
						pattern[i+20] = j;
					}
				}
			}
		}
	}

	string ans = "";
	for (int i = n-1; i >= 0 && lines[i]; i -= lines[i])
		ans += cha_table[pattern[i]];

	for (int i = ans.size()-1; i >= 0; i--)
		cout << ans[i];
	cout << endl;
	//system("pause");
}