/*
ID: caiweid3
PROG: agrinet
LANG: C++              
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>


using namespace std;

ofstream fout ("agrinet.out");
ifstream fin ("agrinet.in");
int set_rank[101],father[101];

struct EDGE
{
	int u,v,w;
}e[101*101];

int cmp(const void *a,const void *b)
{
	return (*(EDGE*)a).w-(*(EDGE*)b).w;
}

int FindFather(int x)
{
	if(x!=father[x])
		father[x]=FindFather(father[x]);
	return father[x];
}

void Union(int x,int y)
{
	if(set_rank[x]>set_rank[y])
		father[y]=x;
	else
	{
		father[x]=y;
		if(set_rank[x]==set_rank[y])
			set_rank[y]++;
	}
}

int main() 
{
	int n,tmp,pos=0;
	fin>>n;
	for(int i=0;i<n;i++)
	{
		father[i]=i;
		set_rank[i]=0;
		for(int j=0;j<=i;j++)
			fin>>tmp;
		for(int j=i+1;j<n;j++)
		{
			fin>>tmp;
			e[pos].u=i;
			e[pos].v=j;
			e[pos].w=tmp;
			pos++;
		}
	}
	qsort(e,pos,sizeof(EDGE),cmp);
	int sum=0;
	for(int i=0;i<pos;i++)
	{
		if(FindFather(e[i].u)!=FindFather(e[i].v))
		{
			sum+=e[i].w;
			Union(FindFather(e[i].u),FindFather(e[i].v));
		}
	}
	fout<<sum<<endl;
	//system("pause");
	return 0;

}