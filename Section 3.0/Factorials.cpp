/*
ID: caiweid3
PROG: fact4
LANG: C++              
*/
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

ofstream fout ("fact4.out");
ifstream fin ("fact4.in");



int main() 
{
	int n,tmp,count=0;
	int m[5000];
	fin>>n;
	for(int i=1;i<=n;i++)
		if(i%5==0)
		{
			tmp=i;
			while(tmp%5==0)
			{
				count++;
				tmp/=5;
			}
			m[i]=tmp;
		}
		else
			m[i]=i;
	int ans=1;
	for(int i=1;i<=n;i++)
	{
		if(count>0&&m[i]%2==0)
		{
			tmp=m[i];
			while(tmp%2==0&&count>0)
			{
				count--;
				tmp/=2;
			}
			ans=(ans*tmp)%10;
		}
		else
			ans=(ans*m[i])%10;
	}
	fout<<ans<<endl;
//	system("pause");
	return 0;

}