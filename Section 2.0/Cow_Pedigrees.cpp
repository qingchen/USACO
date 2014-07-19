/*
ID: caiweid3
PROG: nocows
LANG: C++              
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>


using namespace std;

ofstream fout ("nocows.out");
ifstream fin ("nocows.in");

const int mod=9901;
int dp[201][101];

int main() 
{		
	int n,k;
	fin>>n>>k;
	for(int i=1;i<=k;i++)
		dp[1][i]=1;
	for(int i=1;i<=n;i+=2)
	{
		for(int j=1;j<=k;j++)
		{
			for(int m=1;m<=i-2;m+=2)
			{
				dp[i][j]+=(dp[i-m-1][j-1]*dp[m][j-1])%mod;
				dp[i][j]%=mod;
			}
		}
	}
	fout<<(dp[n][k]+mod-dp[n][k-1])%mod<<endl;
	//system("pause");
    return 0;
	
}
