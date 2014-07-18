/*
ID: caiweid3
PROG: runround
LANG: C++              
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>

using namespace std;

ofstream fout ("runround.out");
ifstream fin ("runround.in");

int tmp[50],digits[50];

bool Check(unsigned int i)
{
	int p,j,index=0;
	bool used[50];
	bool dig_used[10];
	for(int i=0;i<10;i++)
		dig_used[i]=false;
	while(i)
	{
		tmp[index++]=i%10;
		i/=10;
		if(dig_used[tmp[index-1]])
			return false;
		dig_used[tmp[index-1]]=true;
	}
	for(int k=0;k<index;k++)
	{
		digits[k]=tmp[index-k-1];
		used[k]=false;
	}
	for(p=0,j=0;;j++)
	{
		if(used[p])
			break;
		else
			used[p]=true;
		p+=digits[p]%index;
		p%=index;
	}
	if(p==0&&j==index)
		return true;
	else
		return false;
}

int main() 
{
	unsigned int m;
	fin>>m;
	for(int i=m+1;;i++)
	{
		if(Check(i))
		{
			fout<<i<<endl;
			break;
		}
	}
	//system("pause");
    return 0;
	
}
