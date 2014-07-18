/*
ID: caiweid3
PROG: lamps
LANG: C++              
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>

using namespace std;

ofstream fout ("lamps.out");
ifstream fin ("lamps.in");

int lamps[101];
int c,n,on_count,off_count,ans_count,on[101],off[101];
int ans[30][101];
bool possi=false;

void Check()
{
	bool find=true;
	for(int i=0;i<on_count;i++)
	{
		if(!lamps[on[i]])
		{
			find=false;
			break;
		}
	}
	if(find)
	{
		for(int i=0;i<off_count;i++)
			if(lamps[off[i]])
			{
				find=false;
				break;
			}
	}
	if(find)
	{
		possi=true;
		bool equal,exist=true;
		for(int i=0;i<ans_count;i++)
		{
			equal=true;
			for(int j=0;j<n;j++)
				if(ans[i][j]!=lamps[j])
				{
					equal=false;
					break;
				}
			if(equal)
				break;
		}
		if(!equal)
		{
			for(int i=0;i<n;i++)
				ans[ans_count][i]=lamps[i];
			ans_count++;
		}
	}
}

void dfs(int depth)
{
	if(depth==c)
	{
		Check();
		return;
	}
	for(int i=0;i<n;i++)
		lamps[i]=!lamps[i];
	dfs(depth+1);
	for(int i=0;i<n;i++)
		lamps[i]=!lamps[i];
	for(int i=0;i<n;i+=2)
		lamps[i]=!lamps[i];
	dfs(depth+1);
	for(int i=0;i<n;i+=2)
		lamps[i]=!lamps[i];
	for(int i=1;i<n;i+=2)
		lamps[i]=!lamps[i];
	dfs(depth+1);
	for(int i=1;i<n;i+=2)
		lamps[i]=!lamps[i];
	for(int i=0;i<n;i+=3)
		lamps[i]=!lamps[i];
	dfs(depth+1);
	for(int i=0;i<n;i+=2)
		lamps[i]=!lamps[i];
}

int main() 
{
	fin>>n>>c;
	while(c>4)c-=2;
	int tmp;
	while(fin>>tmp)
	{
		if(tmp==-1)
			break;
		on[on_count++]=tmp-1;
	}
	while(fin>>tmp)
	{
		if(tmp==-1)
			break;
		off[off_count++]=tmp-1;
	}
	for(int i=0;i<n;i++)
		lamps[i]=1;
	dfs(0);
	if(!possi)
	{
		fout<<"IMPOSSIBLE"<<endl;
		return 0;
	}
	int change_buff,min;
	bool flag;
	for(int i=0;i<ans_count;i++)
	{
		min=i;
		for(int j=i+1;j<ans_count;j++)
		{
			flag=true;
			for(int k=0;k<n;k++)
			{
				if(ans[j][k]<ans[min][k])
					break;
				if(ans[j][k]>ans[min][k])
				{
					flag=false;
					break;
				}
			}
			if(flag)
				min=j;
		}
		for(int j=0;j<n;j++)
		{
			change_buff=ans[i][j];
			ans[i][j]=ans[min][j];
			ans[min][j]=change_buff;
		}
	}
	for(int i=0;i<ans_count;i++)
	{
		for(int j=0;j<n;j++)
			fout<<ans[i][j];
		fout<<endl;
	}
	//system("pause");
    return 0;
	
}
