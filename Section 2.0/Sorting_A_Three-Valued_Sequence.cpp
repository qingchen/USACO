/*
ID: caiweid3
PROG: sort3
LANG: C++              
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>


using namespace std;

ofstream fout ("sort3.out");
ifstream fin ("sort3.in");


int main() 
{
	int n,count[3],place[3][3],a[1001];
	fin>>n;
	count[0]=count[1]=count[2]=0;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			place[i][j]=0;
	for(int i=0;i<n;i++)
	{
		fin>>a[i];
		count[a[i]-1]++;
	}
	int index=count[0];
	for(int i=0;i<index;i++)
		place[0][a[i]-1]++;
	for(int i=index;i<index+count[1];i++)
		place[1][a[i]-1]++;
	index+=count[1];
	for(int i=index;i<n;i++)
		place[2][a[i]-1]++;
	place[0][0]=place[1][1]=place[2][2]=0;
	int ans=0,tmp;
	for(int i=0;i<3;i++)
		for(int j=i+1;j<3;j++)
		{
			tmp=min(place[i][j],place[j][i]);
			place[i][j]-=tmp;
			place[j][i]-=tmp;
			ans+=tmp;
		}
	int buff=0;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			buff+=place[i][j];
	ans+=buff/3*2;
	fout<<ans<<endl;
	//system("pause");
    return 0;
	
}
