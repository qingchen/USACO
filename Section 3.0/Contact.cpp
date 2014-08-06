/*
ID: caiweid3
PROG: contact
LANG: C++              
*/
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

ofstream fout ("contact.out");
ifstream fin ("contact.in");

char str[200001];
char ans[20];
int trie[10000];
int a,b,n;
int table[14]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192};

void PosToStr(int pos)
{
	char tmp[20];
	int count=0;
	while(pos)
	{
		if(pos&1)
			tmp[count++]='0';
		else
			tmp[count++]='1';
		pos=(pos-1)/2;
	}
	for(int i=0;i<count;i++)
		ans[i]=tmp[count-i-1];
	ans[count]='\0';
}

int main() 
{
	fin>>a>>b>>n;
	while(!fin.eof())
		fin>>str+strlen(str);
	int lenth=strlen(str);
	int index;
	for(int i=0;i<lenth;i++)
	{
		index=0;
		for(int j=0;j<b;j++)
		{
			if(i+j<lenth)
			{
				if(str[i+j]=='0')
					index=index*2+1;
				else
					index=index*2+2;
				trie[index]++;
			}
		}
	}
	int start=table[a]-1,end=table[b+1]-2;
	int fre,pos,out_flag;
	bool end_flag;
	while(n--)
	{
		fre=0;
		for(int i=start;i<=end;i++)
		{
			if(trie[i]>fre)
			{
				fre=trie[i];
				pos=i;
			}
		}
		if(fre==0)
			break;
		fout<<fre<<endl;
		PosToStr(pos);
		fout<<ans;
		out_flag=1;
		trie[pos]=0;
		end_flag=false;
		for(int i=pos+1;i<=end;i++)
			if(trie[i]==fre)
			{
				PosToStr(i);
				out_flag++;
				if(out_flag==1)
				{
					fout<<ans;
					end_flag=false;
				}
				else if(out_flag<=5)
				{
					fout<<" "<<ans;
					end_flag=false;
				}
				else
				{
					fout<<" "<<ans<<endl;
					out_flag=0;
					end_flag=true;
				}
				trie[i]=0;
			}
		if(!end_flag)
			fout<<endl;
	}
	//system("pause");
	return 0;

}