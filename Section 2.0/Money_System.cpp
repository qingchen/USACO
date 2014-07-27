/*
ID: caiweid3
PROG: money
LANG: C++              
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>


using namespace std;

ofstream fout ("money.out");
ifstream fin ("money.in");

long long dp[10001];
int main() 
{		
	
	int V[26],v,n;
	fin>>v>>n;
	for(int i=0;i<v;i++)
		fin>>V[i];
	dp[0]=1;
	for(int j=0;j<v;j++)
		for(int i=1;i<=n;i++)
			if(i-V[j]>=0)
				dp[i]+=dp[i-V[j]];
	fout<<dp[n]<<endl;
	//system("pause");
    return 0;
	
}
