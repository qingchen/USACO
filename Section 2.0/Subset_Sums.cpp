/*
ID: caiweid3
PROG: subset
LANG: C++              
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>

using namespace std;

ofstream fout ("subset.out");
ifstream fin ("subset.in");

unsigned int dp[1000];

int main() 
{
	int n,sum;
	fin>>n;
	sum=(1+n)*n/2;
	if(sum%2==1)
	{
		fout<<0<<endl;
		return 0;
	}
	sum/=2;
	dp[0]=1;
	for(int i=1;i<=n;i++)
		for(int j=sum;j>=i;j--)
			dp[j]=dp[j]+dp[j-i];
	fout<<dp[sum]/2<<endl;
	//system("pause");
    return 0;
	
}
