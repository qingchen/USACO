/*
ID: caiweid3
PROG: hamming
LANG: C++              
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>


using namespace std;

ofstream fout ("hamming.out");
ifstream fin ("hamming.in");

int Check(int n)
{
	int count=0;
	while(n)
	{
		if(n&1)
			count++;
		n=n>>1;
	}
	return count;
}

int main() 
{
	int n,b,d,count,ans[1024];
	fin>>n>>b>>d;
	int up_bound=2<<b;
	bool find=true;
	ans[0]=0;
	count=1;
	for(int i=0;i<up_bound;i++)
	{
		find=true;
		for(int j=0;j<count;j++)
		{
			if(Check(i^ans[j])<d)
			{
				find=false;
				break;
			}
		}
		if(find)
			ans[count++]=i;
		if(count>=n)
			break;
	}
	int index=0;
	while(index+10<count)
	{
		for(int i=index;i<index+9;i++)
			fout<<ans[i]<<" ";
		fout<<ans[index+9]<<endl;
		index+=10;
	}
	for(int i=index;i<count-1;i++)
		fout<<ans[i]<<" ";
	fout<<ans[count-1]<<endl;

	//system("pause");
    return 0;
	
}
