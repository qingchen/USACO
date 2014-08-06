/*
ID: caiweid3
PROG: inflate
LANG: C++              
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>


using namespace std;

ofstream fout ("inflate.out");
ifstream fin ("inflate.in");

struct NODE
{
	int cost,worth;
}p[10001];

int dp[10001];

int main() 
{
	int m,n;
	fin>>m>>n;
	for(int i=0;i<n;i++)
		fin>>p[i].worth>>p[i].cost;
	for(int i=0;i<n;i++)
		for(int j=1;j<=m;j++)
			if(j>=p[i].cost)
				dp[j]=max(dp[j],dp[j-p[i].cost]+p[i].worth);
	fout<<dp[m]<<endl;
	//system("pause");
	return 0;

}