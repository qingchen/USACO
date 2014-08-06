/*
ID: caiweid3
PROG: msquare
LANG: C++              
*/
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <queue>
#include <memory.h>

using namespace std;

ofstream fout ("msquare.out");
ifstream fin ("msquare.in");

const int factorial[9]= {1,1,2,6,24,120,720,5040};
 
int sta[8],res[8];
bool c[8],hash_table[50000];

struct NODE
{
	int num[8];
	int depth;
	string ans;
};

bool Check(int (&a)[8])
{
	for(int i=0;i<8;i++)
		if(a[i]!=res[i])
			return false;
	return true;
}

int cantor(int *a)
{
    int sum=0,temp;
    for(int i=0; i<8; i++)
    {
        temp=0;
        for(int j=i+1; j<8; j++)
        {
            if(a[i]>a[j])temp++;
        }
        sum=sum*(8-i)+temp;
    }
    return sum;
}
 
void re_cantor(int x)
{
    memset(c, false, sizeof(c));
    memset(sta, 0, sizeof(sta));
    for (int i=0; i<8; i++)
    {
        while (c[sta[i]]) sta[i]++;
        while (x >= factorial[7-i])
        {
            x -= factorial[7-i];
            sta[i]++;
            while (c[sta[i]]) sta[i]++;
        }
        c[sta[i]] = true;
    }
}

int main() 
{	
	for(int i=0;i<8;i++)
		fin>>res[i];
	NODE ini;
	for(int i=0;i<8;i++)
		ini.num[i]=i+1;
	ini.depth=0;
	hash_table[cantor(ini.num)]=true;
	queue<NODE> q;
	NODE now,tmp;
	int hash_num;
	q.push(ini);
	while(!q.empty())
	{
		tmp=q.front();
		if(Check(tmp.num))
		{
			fout<<tmp.depth<<endl;
			fout<<tmp.ans<<endl;
			return 0;
		}
		q.pop();
		for(int i=0;i<8;i++)
			now.num[i]=tmp.num[7-i];
		hash_num=cantor(now.num);
		if(!hash_table[hash_num])
		{
			hash_table[hash_num]=true;
			now.depth=tmp.depth+1;
			now.ans=tmp.ans+'A';
			q.push(now);
		}
		for(int i=1;i<4;i++)
		{
			now.num[i]=tmp.num[i-1];
			now.num[3+i]=tmp.num[4+i];
		}
		now.num[0]=tmp.num[3];
		now.num[7]=tmp.num[4];
		hash_num=cantor(now.num);
		if(!hash_table[hash_num])
		{
			hash_table[hash_num]=true;
			now.depth=tmp.depth+1;
			now.ans=tmp.ans+'B';
			q.push(now);
		}
		for(int i=0;i<8;i++)
			now.num[i]=tmp.num[i];
		now.num[1]=tmp.num[6];
		now.num[2]=tmp.num[1];
		now.num[5]=tmp.num[2];
		now.num[6]=tmp.num[5];
		hash_num=cantor(now.num);
		if(!hash_table[hash_num])
		{
			hash_table[hash_num]=true;
			now.depth=tmp.depth+1;
			now.ans=tmp.ans+'C';
			q.push(now);
		}
	}
	//system("pause");
	return 0;
}