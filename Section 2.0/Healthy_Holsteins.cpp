/*
ID: caiweid3
PROG: holstein
LANG: C++              
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>


using namespace std;

ofstream fout ("holstein.out");
ifstream fin ("holstein.in");

int t,n,V[30],G[20][30],ans=100,path[20];
bool used[20];

void Search(int d,int res)
{
	if(d>t+1)
		return;
	bool done=true;
	for(int i=0;i<n;i++)
		if(V[i]>0)
		{
			done=false;
			break;
		}
	if(done)
	{
		if(ans<res)
			return;
		ans=res;
		int count=0;
		for(int i=0;i<t;i++)
			if(used[i])
				path[count++]=i+1;
		return;
	}
	Search(d+1,res);
	for(int i=0;i<n;i++)
		V[i]-=G[d-1][i];
	used[d-1]=true;
	Search(d+1,res+1);
	for(int i=0;i<n;i++)
		V[i]+=G[d-1][i];
	used[d-1]=false;
}
int main() 
{
	fin>>n;
	for(int i=0;i<n;i++)
		fin>>V[i];
	fin>>t;
	for(int i=0;i<t;i++)
		for(int j=0;j<n;j++)
			fin>>G[i][j];
	Search(1,0);
	fout<<ans;
	for(int i=0;i<ans;i++)
		fout<<" "<<path[i];
	fout<<endl;
	//system("pause");
    return 0;
	
}
