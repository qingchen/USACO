/*
ID: caiweid3
PROG: kimbits
LANG: C++              
*/
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

ofstream fout ("kimbits.out");
ifstream fin ("kimbits.in");

unsigned int dp[50][50];
int N,L;
unsigned int I;

int main() 
{	
	fin>>N>>L>>I;
	char ans[50];
	for(int i=1;i<=N;i++)
		dp[0][i]=dp[i][0]=1;
	dp[0][0]=1;
	for(int i=1;i<=N;i++)
		for(int j=1;j<=L;j++)
			dp[j][i]=dp[j-1][i-1]+dp[j][i-1];
	for(int i=0;i<N;i++)
		ans[i]='0';
	ans[N]='\0';
	for(int i=N-1;i>=0;i--)
	{
		if(I>dp[L][i])
		{
			ans[N-i-1]='1';
			I-=dp[L][i];
			L--;
		}
		if(L==0)
			break;
	}
	fout<<ans<<endl;
	//system("pause");
	return 0;
}