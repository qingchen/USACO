/*
ID: caiweid3
PROG: range
LANG: C++              
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <memory.h>


using namespace std;

ofstream fout ("range.out");
ifstream fin ("range.in");

int dp[251][251];
int map[251][251];
int ans[251];

int main() 
{
	int n;
	char c;
	fin>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			fin>>c;
			if(c=='0')
				map[i][j]=0;
			else
				map[i][j]=1;
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(map[i][j])
				dp[i][j]=min(min(dp[i-1][j-1],dp[i][j-1]),dp[i-1][j])+1;
	
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				for(int k=2;k<=dp[i][j];k++)
					ans[k]++;
	for(int i=2;i<=n;i++)
		if(ans[i])
			fout<<i<<" "<<ans[i]<<endl;
	//system("pause");
	return 0;
	
}
