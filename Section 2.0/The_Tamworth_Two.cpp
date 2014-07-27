/*
ID: caiweid3
PROG: ttwo
LANG: C++              
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <memory.h>

using namespace std;

ofstream fout ("ttwo.out");
ifstream fin ("ttwo.in");

struct Obj
{
	int i,j,d;
};

int Move[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
Obj far,cow;
int map[10][10];
bool flag[400][400];

bool Check()
{
	if(far.i==cow.i&&far.j==cow.j)
		return true;
	else
		return false;
}

void MakeMove()
{
	int nexti=far.i+Move[far.d][0],nextj=far.j+Move[far.d][1];
	if(nexti>=0&&nexti<=9&&nextj>=0&&nextj<=9&&map[nexti][nextj]==0)
	{
		far.i=nexti;
		far.j=nextj;
	}
	else
		far.d=(far.d+1)%4;
	nexti=cow.i+Move[cow.d][0];
	nextj=cow.j+Move[cow.d][1];
	if(nexti>=0&&nexti<=9&&nextj>=0&&nextj<=9&&map[nexti][nextj]==0)
	{
		cow.i=nexti;
		cow.j=nextj;
	}
	else
		cow.d=(cow.d+1)%4;
}

bool Hash()
{
	if(flag[cow.d*100+cow.i*10+cow.j][far.d*100+far.i*10+far.j])
		return false;
	else
	{
		flag[cow.d*100+cow.i*10+cow.j][far.d*100+far.i*10+far.j]=true;
		return true;
	}
}

int main() 
{
	char tmp;
	for(int i=0;i<10;i++)
		for(int j=0;j<10;j++)
		{
			fin>>tmp;
			if(tmp=='*')
				map[i][j]=1;
			else if(tmp=='.')
				map[i][j]=0;
			else if(tmp=='C')
			{
				map[i][j]=0;
				cow.i=i;
				cow.j=j;
				cow.d=0;
			}
			else
			{
				map[i][j]=0;
				far.i=i;
				far.j=j;
				far.d=0;
			}
		}
	Hash();
	if(Check())
		fout<<0<<endl;
	else
		for(int i=1;;i++)
		{
			MakeMove();
			if(Check())
			{
				fout<<i<<endl;
				break;
			}
			if(!Hash())
			{
				fout<<0<<endl;
				break;
			}
		}
	//system("pause");
    return 0;
	
}