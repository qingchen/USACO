/*
ID: caiweid3
PROG: concom
LANG: C++              
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <memory.h>

using namespace std;

ofstream fout ("concom.out");
ifstream fin ("concom.in");


bool control_flag[101];
int share[101][101];


void Control(int i,int j)
{
	if(control_flag[j])
		return;
	control_flag[j]=true;
	for(int k=1;k<=100;k++)
		if(k!=i&&!control_flag[k])
		{
			share[i][k]+=share[j][k];
			if(share[i][k]>50)
				Control(i,k);
		}
}
int main() 
{
	int n;
	fin>>n;
	int i,j,p;
	for(int k=0;k<n;k++)
	{
		fin>>i>>j>>p;
		share[i][j]+=p;
	}
#if 1
	for(int m=1;m<=100;m++)
	{
		memset(control_flag,0,sizeof(control_flag));
		for(int n=1;n<=100;n++)
		{
			if(m==n)
				continue;
			if(share[m][n]>50)
				Control(m,n);
		}
		for(int n=1;n<=100;n++)
		{
			if(control_flag[n])
				fout<<m<<" "<<n<<endl;
		}
	}
#endif
	//system("pause");
    return 0;
	
}