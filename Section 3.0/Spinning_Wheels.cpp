/*
ID: caiweid3
PROG: spin
LANG: C++              
*/
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

ofstream fout ("spin.out");
ifstream fin ("spin.in");

int speed[5],wedges_start[5][5],wedges_end[5][5];
int light[360];

bool Judge(int t)
{
	for(int i=0;i<360;i++)
		light[i]=0;
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			if(wedges_start[i][j]==-1)
				break;
			if(wedges_end[i][j]>wedges_start[i][j])
				for(int k=wedges_start[i][j];k<=wedges_end[i][j];k++)
				{
					light[k]++;
					if(light[k]==5)
						return true;
				}
			else
			{
				for(int k=wedges_start[i][j];k<360;k++)
				{
					light[k]++;
					if(light[k]==5)
						return true;
				}
				for(int k=0;k<=wedges_end[i][j];k++)
				{
					light[k]++;
					if(light[k]==5)
						return true;
				}
			}
		}
	}
	return false;
}

void Move()
{
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			if(wedges_start[i][j]==-1)
				break;
			wedges_start[i][j]=(wedges_start[i][j]+speed[i])%360;
			wedges_end[i][j]=(wedges_end[i][j]+speed[i])%360;
		}
	}
}

int main() 
{	
	int tmp;
	for(int i=0;i<5;i++)
	{
		fin>>speed[i]>>tmp;
		for(int j=0;j<tmp;j++)
		{
			fin>>wedges_start[i][j]>>wedges_end[i][j];
			wedges_end[i][j]=(wedges_end[i][j]+wedges_start[i][j])%360;
		}
		if(tmp<5)
			wedges_start[i][tmp]=wedges_end[i][tmp]=-1;
	}
	tmp=0;
	bool find=false;
	while(tmp<360)
	{
		if(Judge(tmp))
		{
			fout<<tmp<<endl;
			return 0;
		}
		tmp++;
		Move();
	}
	fout<<"none"<<endl;
	//system("pause");
	return 0;
}