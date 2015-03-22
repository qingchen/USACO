/*
ID: caiweid3
PROG: camelot
LANG: C++              
*/
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <memory.h>
#include <queue>

using namespace std;

ofstream fout ("camelot.out");
ifstream fin ("camelot.in");

struct NODE
{
	int x,y;
	NODE(int xx=0,int yy=0):x(xx),y(yy){};
};

int knight_move[8][2]={{1,-2},{2,-1},{2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2}};
int dist[26][30];
int king_dist[26][30];
int king_cost[26][30];
int cost[26][30];
int min_king_cost[26][30];
bool visit[26][30];

int r,c;

void Calculate(NODE start)
{
	memset(visit,false,sizeof(visit));
	NODE tmp;
	int next_x,next_y;
	dist[start.x][start.y]=0;
	queue<NODE> q;
	q.push(start);
	visit[start.x][start.y]=true;
	while(!q.empty())
	{
		tmp=q.front();
		q.pop();
		for(int i=0;i<8;i++)
		{
			next_x=tmp.x+knight_move[i][0];
			next_y=tmp.y+knight_move[i][1];
			if(next_x>=0&&next_x<c&&next_y>=0&&next_y<r&&!visit[next_x][next_y])
			{
				visit[next_x][next_y]=true;
				dist[next_x][next_y]=dist[tmp.x][tmp.y]+1;
				q.push(NODE(next_x,next_y));
				cost[next_x][next_y]+=dist[next_x][next_y];
			}
		}
	}
	for(int i=0;i<c;i++)
		for(int j=0;j<r;j++)
			king_cost[i][j]=king_dist[i][j];
	for(int i=0;i<c;i++)
		for(int j=0;j<r;j++)
		{
			q.push(NODE(i,j));
			while(!q.empty())
			{
				tmp=q.front();
				q.pop();
				for(int k=0;k<8;k++)
				{
					next_x=tmp.x+knight_move[k][0];
					next_y=tmp.y+knight_move[k][1];
					if(next_x>=0&&next_x<c&&next_y>=0&&next_y<r)
						if(king_cost[next_x][next_y]+dist[next_x][next_y]>king_cost[tmp.x][tmp.y]+dist[tmp.x][tmp.y]+1)
						{
							king_cost[next_x][next_y]=king_cost[tmp.x][tmp.y]+dist[tmp.x][tmp.y]+1-dist[next_x][next_y];
							q.push(NODE(next_x,next_y));
						}
				}
			}
		}
	for(int i=0;i<c;i++)
		for(int j=0;j<r;j++)
			if(min_king_cost[i][j]>king_cost[i][j])
				min_king_cost[i][j]=king_cost[i][j];
}

bool knight[26][30];
int main() 
{
	fin>>r>>c;
	char a;
	int b;
	fin>>a>>b;
	int x,y;
	x=a-'A';
	y=b-1;
	for(int i=0;i<c;i++)
		for(int j=0;j<r;j++)
		{
			king_dist[i][j]=max(abs(i-x),abs(j-y));
			min_king_cost[i][j]=0x7fffffff;
		}
	bool knight_exist=false;
	int ans=0x7fffffff;
	while(fin>>a>>b)
	{
		x=a-'A';
		y=b-1;
		Calculate(NODE(x,y));
		knight_exist=true;
		knight[x][y]=true;
	}
	if(!knight_exist)
		fout<<0<<endl;
	else
	{
		for(int i=0;i<c;i++)
			for(int j=0;j<r;j++)
				if((cost[i][j]>0||knight[i][j])&&ans>cost[i][j]+min_king_cost[i][j])
					ans=cost[i][j]+min_king_cost[i][j];
		fout<<ans<<endl;
	}
	//system("pause");
	return 0;
	
}