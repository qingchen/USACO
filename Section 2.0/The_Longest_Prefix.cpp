/*
ID: caiweid3
PROG: prefix
LANG: C++              
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

ofstream fout ("prefix.out");
ifstream fin ("prefix.in");

bool dp[200000];

int main() 
{	
	vector<string> p;
	string tmp,s="";
	while(fin>>tmp)
	{
		if(tmp==".")
			break;
		p.push_back(tmp);
	}
	while(fin>>tmp)
	{
		s+=tmp;
	}
	bool equal;
	int j,ans=0;
	dp[0]=true;
	for(int i=0;i<s.size();i++)
	{
		if(!dp[i])
			continue;
		for(vector<string>::iterator it=p.begin();it!=p.end();it++)
		{
			equal=true;
			if((*it).size()+i>s.size())
				continue;
			for(j=0;j<(*it).size();j++)
			{
				if(s[i+j]!=(*it)[j])
				{
					equal=false;
					break;
				}
			}
			if(equal)
			{
				dp[i+j]=true;
				if(i+j>ans)
					ans=i+j;
			}
		}
	}
	fout<<ans<<endl;
	//system("pause");
    return 0;
	
}
