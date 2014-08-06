/*
ID: caiweid3
PROG: game1
LANG: C++              
*/
#include <iostream>
#include <fstream>
#include <stdlib.h>


using namespace std;

ofstream fout ("game1.out");
ifstream fin ("game1.in");

int dp[101][101];

int main() 
{
	int n,num[101],sum[101][101];
    fin>>n;
    for (int i=1;i<=n;i++)
        fin>>num[i];
    for (int i=1;i<=n;i++)
    {
        sum[i][i]=num[i];
        for (int j=i+1;j<=n;j++)
            sum[i][j]=sum[i][j-1]+num[j];
    }
    for (int i=1;i<=n;i++)
        dp[i][i]=num[i];
    for (int l=1;l<n;l++)
        for (int i=1;i<=n-l;i++)
            dp[i][i+l]=sum[i][i+l]-min(dp[i][i+l-1],dp[i+1][i+l]);
    fout<<dp[1][n]<<" "<<sum[1][n]-dp[1][n]<<endl;
	//system("pause");
	return 0;
}