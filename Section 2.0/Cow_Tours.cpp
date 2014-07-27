/*
ID: caiweid3
PROG: cowtour
LANG: C++              
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <iomanip>

using namespace std;

ofstream fout ("cowtour.out");
ifstream fin ("cowtour.in");


struct LOCATED
{
	int x,y;
};

double Calculate(LOCATED a,LOCATED b)
{
	return sqrt(pow((double)a.x-b.x,2)+pow((double)a.y-b.y,2));
}


double map[151][151];
double dis[151];
LOCATED p[151];
int n;

void Floyd()
{
	for(int k=0;k<n;k++)
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
			{
				if(map[i][k]&&map[k][j]&&i!=j)
				{
					if(map[i][j]==0||map[i][j]>map[i][k]+map[k][j])
						map[i][j]=map[i][k]+map[k][j];
				}
			}
}

int main() 
{
	int tmp;
	char ctmp;
	fin>>n;
	for(int i=0;i<n;i++)
		fin>>p[i].x>>p[i].y;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			fin>>ctmp;
			if(ctmp=='1')
				map[i][j]=Calculate(p[i],p[j]);
		}
	}
	Floyd();
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			dis[i]=max(dis[i],map[i][j]);
	double ans=1000000;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if(map[i][j]==0&&i!=j)
			{
				ans=min(ans,dis[i]+dis[j]+Calculate(p[i],p[j]));
			}
	for(int i=0;i<n;i++)
		ans=max(ans,dis[i]);
	fout<<fixed<<setprecision(6)<<ans<<endl;
	//system("pause");
	return 0;

}