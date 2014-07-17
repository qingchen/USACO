/*
ID: caiweid3
PROG: preface
LANG: C++              
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>

using namespace std;

enum Roman{I,V,X,L,C,D,M};
int Num[7]={1,5,10,50,100,500,1000};
int PowTen[5]={0,1,10,100,1000};
char Ch[7]={'I','V','X','L','C','D','M'};
int count[7];

ofstream fout ("preface.out");
ifstream fin ("preface.in");

void Count(int n)
{
	if(n<4)
	{
		count[0]+=n;
		return;
	}
	int tmp;
	for(int i=6;i>=0;i--)
	{
		tmp=n/Num[i];
		count[i]+=tmp;
		n%=Num[i];
		if(i%2==0)
		{
			if(n+PowTen[i/2]>=PowTen[i/2+1])
			{
				n-=9*PowTen[i/2];
				count[i-2]++;
				count[i]++;
				//cout<<Ch[i-2]<<Ch[i];
			}
		}
		else
		{
			if(n+PowTen[i/2+1]>=Num[i])
			{
				n-=4*PowTen[i/2+1];
				count[i-1]++;
				count[i]++;
				//cout<<Ch[i-1]<<Ch[i];
			}
		}
	}
}
int main() 
{
	int n;
	fin>>n;
	for(int i=1;i<=n;i++)
	{
		//cout<<i<<" ";
		Count(i);
		//cout<<endl;
	}
	for(int i=0;i<7;i++)
		if(count[i])
			fout<<Ch[i]<<" "<<count[i]<<endl;

	//system("pause");
    return 0;
	
}
