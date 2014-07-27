/*
ID: caiweid3
PROG: fracdec
LANG: C++              
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>

using namespace std;

ofstream fout ("fracdec.out");
ifstream fin ("fracdec.in");
int flag[100001],pos,cir;
string ans;

void Slove(int a,int b)
{
	int tmp=a/b;
	string inverse;
	if(tmp>0)
	{
		while(tmp)
		{
			inverse+=tmp%10+'0';
			tmp/=10;
		}
		for(int i=inverse.size()-1;i>=0;i--)
			ans+=inverse[i];
	}
	else
		ans+='0';
	ans+='.';
	tmp=a%b;
	if(tmp==0)
	{
		ans+='0';
		pos=ans.size();
		return;
	}
	pos=ans.size();
	while(tmp)
	{
		if(!flag[tmp])
			flag[tmp]=pos;
		else
		{
			cir=flag[tmp];
			break;
		}
		tmp*=10;
		ans+=tmp/b+'0';
		pos++;
		tmp%=b;
	}
}
	
int main() 
{
	int a,b;
	fin>>a>>b;
	Slove(a,b);
	int index=0;
	for(int i=0;i<pos;i++)
	{
		if(cir>0&&i==cir)
		{
			fout<<'(';
			index++;
			if(index==76)
			{
				fout<<endl;
				index=0;
			}
			fout<<ans[i];
			index++;
			if(index==76)
			{
				fout<<endl;
				index=0;
			}
		}
		else
		{
			fout<<ans[i];
			index++;
			if(index==76)
			{
				fout<<endl;
				index=0;
			}
		}
	}
	if(cir>0)
		fout<<')'<<endl;
	else if(index!=0)
		fout<<endl;
	//system("pause");
	return 0;

}