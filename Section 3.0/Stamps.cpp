/*
ID: caiweid3
PROG: stamps
LANG: C++              
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <memory>

using namespace std;

ofstream fout ("stamps.out");
ifstream fin ("stamps.in");

int dp[2000001];
int value[51];
const int max_int=0x7fffff00;
int main() 
{
	int k,n;
	fin>>k>>n;
	for(int i=0;i<n;i++)
		fin>>value[i];
	for(int i=1;i<=2000000;i++)
		dp[i]=0x7ffffff0;
	for(int j=1;;j++)
	{
		dp[j]=max_int;
		for(int i=0;i<n;i++)
			if(j>=value[i]&&dp[j]>dp[j-value[i]]+1)
				dp[j]=dp[j-value[i]]+1;
		if(dp[j]>k)
			break;
	}
	for(int j=1;;j++)
		if(dp[j]>k)
		{
			fout<<j-1<<endl;
			break;
		}
	//system("pause");
	return 0;

}