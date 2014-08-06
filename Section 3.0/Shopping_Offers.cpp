/*
ID: caiweid3
PROG: shopping
LANG: C++              
*/
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <memory.h>

using namespace std;

ofstream fout ("shopping.out");
ifstream fin ("shopping.in");

struct NODE
{
	int num[5],price;
};
NODE buy[110];

int hash_num,hash_table[1000];
int order[5];
int dp[6][6][6][6][6];

int main() 
{
	int s,n,c,k,b,p;
	memset(hash_table,0xff,sizeof(hash_table));
	memset(dp,0x7f,sizeof(dp));
	fin>>s;
	for(int i=0;i<s;i++)
	{
		fin>>n;
		for(int j=0;j<n;j++)
		{
			fin>>c>>k;
			if(hash_table[c]<0)
			{
				hash_table[c]=hash_num;
				buy[i].num[hash_num]=k;
				hash_num++;
				
			}
			else
				buy[i].num[hash_table[c]]=k;
		}
		fin>>buy[i].price;
	}
	fin>>b;
	if(!b)
	{
		fout<<0<<endl;
		return 0;
	}
	for(int i=0;i<b;i++)
	{
		fin>>c>>k>>p;
		if(!s)
		{
			hash_table[c]=hash_num;
			hash_num++;
		}
		buy[s+i].num[hash_table[c]]=1;
		buy[s+i].price=p;
		order[hash_table[c]]=k;
	}
	dp[0][0][0][0][0]=0;
	for(int i=0;i<s+b;i++)
		for(int a1=0;a1<=order[0];a1++)
			for(int a2=0;a2<=order[1];a2++)
				for(int a3=0;a3<=order[2];a3++)
					for(int a4=0;a4<=order[3];a4++)
						for(int a5=0;a5<=order[4];a5++)
							if(a1>=buy[i].num[0]&&a2>=buy[i].num[1]&&a3>=buy[i].num[2]&&a4>=buy[i].num[3]&&a5>=buy[i].num[4])
								dp[a1][a2][a3][a4][a5]=min(dp[a1][a2][a3][a4][a5],dp[a1-buy[i].num[0]][a2-buy[i].num[1]][a3-buy[i].num[2]][a4-buy[i].num[3]][a5-buy[i].num[4]]+buy[i].price);							
	fout<<dp[order[0]][order[1]][order[2]][order[3]][order[4]]<<endl;
	//system("pause");
	return 0;
	
}