/*
ID: caiweid3
PROG: butter
LANG: C++              
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <queue>
#include <memory.h>


using namespace std;

ofstream fout ("butter.out");
ifstream fin ("butter.in");

bool visited[801];
int cow[801];
int n,p,c;

struct NODE
{
	int x,w;
};

vector<NODE> map[801];

bool operator<(const NODE &a,const NODE &b)
{
	return a.w>b.w;
}

int Dijkstra(int i)
{
	int ans=0;
	for(int j=1;j<=p;j++)
		visited[j]=false;
	priority_queue<NODE> heap;
	NODE now,tmp;
	now.x=i;
	now.w=0;
	heap.push(now);
	while(!heap.empty())
	{
		now=heap.top();
		heap.pop();
		if(!visited[now.x])
		{
			visited[now.x]=true;
			ans+=cow[now.x]*now.w;
			for(int j=0;j<map[now.x].size();j++)
			{
				tmp.w=now.w+map[now.x][j].w;
				tmp.x=map[now.x][j].x;
				heap.push(tmp);
			}
		}
	}
	return ans;
}

int main() 
{	
	int tmp;
	fin>>n>>p>>c;
	for(int i=0;i<n;i++)
	{
		fin>>tmp;
		cow[tmp]++;
	}
	int a,b,w;
	NODE t;
	for(int i=0;i<c;i++)
	{
		fin>>a>>b>>w;
		t.w=w;
		t.x=b;
		map[a].push_back(t);
		t.x=a;
		map[b].push_back(t);
	}
	
	int ans=0x7fffffff;
	for(int i=1;i<=p;i++)
	{
		tmp=Dijkstra(i);
		if(tmp<ans)
			ans=tmp;
	}
	fout<<ans<<endl;
	//system("pause");
	return 0;
}