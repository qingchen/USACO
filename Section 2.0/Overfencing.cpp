/*
ID: caiweid3
PROG: maze1
LANG: C++              
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <memory.h>
#include <queue>


using namespace std;

ofstream fout ("maze1.out");
ifstream fin ("maze1.in");

struct state
{
	int i,j,septh;
};

int mov[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
bool road[101][40][4];
bool visit[101][40];
int  dist[101][40];
int w,h;

void bfs(int i,int j)
{
	state s,tmp;
	s.i=i;
	s.j=j;
	s.septh=1;
	queue<state> v;
	v.push(s);
	while(!v.empty())
	{
		s=v.front();
		v.pop();
		if(visit[s.i][s.j])
			continue;
		visit[s.i][s.j]=true;
		if(dist[s.i][s.j]==0||dist[s.i][s.j]>s.septh)
			dist[s.i][s.j]=s.septh;
		for(int k=0;k<4;k++)
			if(road[s.i][s.j][k])
			{
				tmp.i=s.i+mov[k][0];
				tmp.j=s.j+mov[k][1];
				tmp.septh=s.septh+1;
				v.push(tmp);
			}
	}
}

int main() 
{
	fin>>w>>h;
	fin.get();
	int x,y,exit1_x,exit1_y,exit2_x,exit2_y;
	bool use_exit1=true;
	char tmp;
	for(int i=0;i<2*h+1;i++)
	{
		for(int j=0;j<2*w+1;j++)
		{
			fin.get(tmp);
			//cin>>tmp;
			if(i%2==0)
			{
				if(tmp==' ')
				{
					if(i/2<h)
						road[i/2][(j-1)/2][0]=true;
					if((i/2)-1>=0)
						road[i/2-1][(j-1)/2][2]=true;
					if(i==0)
					{
						if(use_exit1)
						{
							exit1_x=0;
							exit1_y=(j-1)/2;
							road[exit1_x][exit1_y][0]=false;
							use_exit1=false;
						}
						else
						{
							exit2_x=0;
							exit2_y=(j-1)/2;
							road[exit2_x][exit2_y][0]=false;
						}
					}
					if(i==2*h)
					{
						if(use_exit1)
						{
							exit1_x=h-1;
							exit1_y=(j-1)/2;
							road[exit1_x][exit1_y][2]=false;
							use_exit1=false;
						}
						else
						{
							exit2_x=h-1;
							exit2_y=(j-1)/2;
							road[exit2_x][exit2_y][2]=false;
						}
					}
				}
			}
			else
			{
				if(j%2!=0)
					continue;
				if(tmp==' ')
				{
					if(j/2<w)
						road[(i-1)/2][j/2][3]=true;
					if(j/2-1>=0)
						road[(i-1)/2][j/2-1][1]=true;
					if(j==0)
					{
						if(use_exit1)
						{
							exit1_x=(i-1)/2;
							exit1_y=0;
							road[exit1_x][exit1_y][3]=false;
							use_exit1=false;
						}
						else
						{
							exit2_x=(i-1)/2;
							exit2_y=0;
							road[exit2_x][exit2_y][3]=false;
						}
					}
					if(j==2*w)
					{
						if(use_exit1)
						{
							exit1_x=(i-1)/2;
							exit1_y=w-1;
							road[exit1_x][exit1_y][1]=false;
							use_exit1=false;
						}
						else
						{
							exit2_x=(i-1)/2;
							exit2_y=w-1;
							road[exit2_x][exit2_y][1]=false;
						}
					}
				}
			}
		}
		fin.get();//cin>>tmp;
	}
	bfs(exit1_x,exit1_y);
	for(int i=0;i<h;i++)
		for(int j=0;j<w;j++)
			visit[i][j]=false;
	bfs(exit2_x,exit2_y);
	int ans=0;
	for(int i=0;i<h;i++)
		for(int j=0;j<w;j++)
			if(dist[i][j]>ans)
				ans=dist[i][j];
	fout<<ans<<endl;
	//system("pause");
	return 0;

}