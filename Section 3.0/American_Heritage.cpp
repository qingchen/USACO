/*
ID: caiweid3
PROG: heritage
LANG: C++              
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>


using namespace std;

ofstream fout ("heritage.out");
ifstream fin ("heritage.in");


char First[50];
char Mid[50];
int mid_pos;

void Build(int start,int end)
{
	if(start>end)
		return;
	for(int i=start;i<=end;i++)
	{
		if(First[i]==Mid[mid_pos])
		{
			mid_pos++;
			Build(start,i-1);
			Build(i+1,end);
			fout<<First[i];
		}
	}
}

int main() 
{
	fin>>First;
	fin>>Mid;
	Build(0,strlen(First)-1);
	fout<<endl;
	//system("pause");
	return 0;
	
}
