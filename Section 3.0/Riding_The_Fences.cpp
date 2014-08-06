/*
ID: caiweid3
PROG: fence
LANG: C++              
*/
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

ofstream fout ("fence.out");
ifstream fin ("fence.in");

vector<int> e[501];
int ans[1100];
int pos;

void dfs(int i)
{
	if(e[i].size()==0)
		ans[pos++]=i;
	else
	{
		int tmp;
		vector<int>::iterator it=e[i].begin();
		for(unsigned int j=0;j<e[i].size();j++)
		{
			for(vector<int>::iterator jt=e[*it].begin();jt!=e[*it].end();jt++)
			{
				if(*jt==i)
				{
					e[*it].erase(jt);
					break;
				}
			}
			tmp=*it;
			it=e[i].erase(it);
			dfs(tmp);
		}
		ans[pos++]=i;
	}
}

int main() 
{
	int f,a,b;
	fin>>f;
	for(int i=0;i<f;i++)
	{
		fin>>a>>b;
		e[a].push_back(b);
		e[b].push_back(a);
	}
	int start1=-1,start2;
	for(int i=500;i>=1;i--)
		if(e[i].size()!=0)
		{
			start2=i;
			if(e[i].size()&1)
				start1=i;
			sort(e[i].begin(),e[i].end());
		}
	if(start1!=-1)
		dfs(start1);
	else
		dfs(start2);
	for(int i=pos-1;i>=0;i--)
		fout<<ans[i]<<endl;
	//system("pause");
	return 0;

}