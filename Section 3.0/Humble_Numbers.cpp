/*
ID: caiweid3
PROG: humble
LANG: C++              
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>


using namespace std;

ofstream fout ("humble.out");
ifstream fin ("humble.in");

int prim[101],a[101];
int ans[100001];

int main() 
{
	int k,n,min;
	fin>>k>>n;
	for(int i=0;i<k;i++)
		fin>>prim[i];
	ans[0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<k;j++)
		{
			while(ans[a[j]]*prim[j]<=ans[i-1])
				a[j]++;
		}
		min=0x7fffffff;
		for(int j=0;j<k;j++)
			if(min>ans[a[j]]*prim[j])
				min=ans[a[j]]*prim[j];
		ans[i]=min;
	}
	fout<<ans[n]<<endl;
	//system("pause");
	return 0;

}