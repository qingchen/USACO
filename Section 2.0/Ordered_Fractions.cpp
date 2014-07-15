/*
ID: caiweid3
PROG: frac1
LANG: C++              
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>


using namespace std;

ofstream fout ("frac1.out");
ifstream fin ("frac1.in");

struct frac
{
	int a,b;
	double c;
}ans[10000];

int cmp(const void* a,const void* b)
{
	return (*(frac*)a).c>(*(frac*)b).c?1:-1;
}

int gcd(int a,int b)
{
	return b?gcd(b,a%b):a;
}

int main() 
{
	int n,count=0;
	fin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i;j++)
			if(gcd(i,j)==1)
			{
				ans[count].a=j;
				ans[count].b=i;
				ans[count].c=(double)j/(double)i;
				count++;
			}
	qsort(ans,count,sizeof(ans[0]),cmp);
	fout<<"0/1"<<endl;
	for(int i=0;i<count;i++)
		fout<<ans[i].a<<'/'<<ans[i].b<<endl;
	//system("pause");
    return 0;
	
}
