/*
ID: caiweid3
PROG: castle
LANG: C++              
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>


using namespace std;

ofstream fout ("castle.out");
ifstream fin ("castle.in");

bool wall[51][51][4];
int room_flag[51][51];
int size[2501],room_count,n,m,tmp;

void dfs(int i,int j)
{
	if(room_flag[i][j]!=-1)
		return;
	size[room_count]++;
	room_flag[i][j]=room_count;
	if(!wall[i][j][0])
		dfs(i,j-1);
	if(!wall[i][j][1])
		dfs(i-1,j);
	if(!wall[i][j][2])
		dfs(i,j+1);
	if(!wall[i][j][3])
		dfs(i+1,j);
	return;
}

int main() 
{
	int s_max=0,c_max=0,ans_x,ans_y;
	char ans_w;
	fin>>m>>n;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
		{
			fin>>tmp;
			for(int k=0;k<4;k++)
				wall[i][j][k]=1&(tmp>>k);
			room_flag[i][j]=-1;
		}
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
		{
			if(room_flag[i][j]==-1)
			{
				room_count++;
				dfs(i,j);
				s_max=s_max>size[room_count]?s_max:size[room_count];
			}
		}
	 
		for(int i=0; i<m; i++)
			for (int j=n-1; j>=0; j--)
			{
				int a=room_flag[j][i],b=room_flag[j][i<m-1?i+1:0],c=room_flag[j>0?j-1:0][i];
				if (j>0 && wall[j][i][1] && a!=c && size[a]+size[c]>c_max)
				{
					c_max=size[a]+size[c];
					ans_x=j;
					ans_y=i;
					ans_w='N';
				}
				if (i<m-1 && wall[j][i][2] && a!=b && size[a]+size[b]>c_max)
				{
					c_max=size[a]+size[b];
					ans_x=j;
					ans_y=i;
					ans_w='E';
				}
			}
	fout<<room_count<<endl<<s_max<<endl<<c_max<<endl<<ans_x+1<<" "<<ans_y+1<<" "<<ans_w<<endl;
	//system("pause");
    return 0;
	
}
