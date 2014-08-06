/*
ID: caiweid3
PROG: rect1
LANG: C++              
*/
/*
 ¿Î…¢ªØ …®√Ëœﬂ œﬂ∂Œ ˜
*/
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <memory>

using namespace std;

ofstream fout ("rect1.out");
ifstream fin ("rect1.in");

struct TREENODE
{
	int a,b,color;
	int lc,rc;
};

struct REC
{
	int llx,lly,urx,ury,color;
};

TREENODE t[40000];
REC rec[1001];
bool flag[10001];
int line[1001];
int ans[2501];
bool ansflag[2501];

int cmp(const void *a,const void *b)
{
	return (*(REC*)a).color-(*(REC*)b).color;
}

void BuildTree(int a,int b,int pos)
{
	t[pos].a=a;
	t[pos].b=b;
	t[pos].color=0;
	if(a+1<b)
	{
		t[pos].lc=pos*2;
		t[pos].rc=pos*2+1;
		BuildTree(a,(a+b)/2,pos*2);
		BuildTree((a+b)/2,b,pos*2+1);
	}
	else
		t[pos].lc=t[pos].rc=-1;
}

void Insert(int a,int b,int color,int root)
{
	if(t[root].a>=a&&t[root].b<=b)
	{
		t[root].color=color;
		return;
	}
	if(t[root].color>0)
	{
		t[t[root].lc].color=t[root].color;
		t[t[root].rc].color=t[root].color;
		t[root].color=0;
	}
	int mid=(t[root].a+t[root].b)/2;
	if(a<mid)
		Insert(a,b,color,root*2);
	if(b>mid)
		Insert(a,b,color,root*2+1);
}

void GetAera(int a,int b,int root)
{
	if(t[root].color)
		ans[t[root].color]+=(b-a)*(t[root].b-t[root].a);
	else
	{
		GetAera(a,b,root*2);
		GetAera(a,b,root*2+1);
	}
}

int main() 
{
	int a,b,n;
	fin>>a>>b>>n;
	for(int i=0;i<n;i++)
	{
		fin>>rec[i].llx>>rec[i].lly>>rec[i].urx>>rec[i].ury>>rec[i].color;
		flag[rec[i].llx]=flag[rec[i].urx]=true;
	}
	BuildTree(0,b,1);
	int pos=0;
	line[pos++]=0;
	for(int i=1;i<=10000;i++)
		if(flag[i])
			line[pos++]=i;
	if(line[pos-1]!=a)
		line[pos++]=a;
	for(int i=0;i<pos-1;i++)
	{
		Insert(0,b,1,1);
		for(int j=0;j<n;j++)
			if(line[i]>=rec[j].llx&&line[i+1]<=rec[j].urx)
				Insert(rec[j].lly,rec[j].ury,rec[j].color,1);
		GetAera(line[i],line[i+1],1);
	}
	qsort(rec,n,sizeof(REC),cmp);
	if(ans[1]&&rec[0].color!=1)
	{
		fout<<1<<" "<<ans[1]<<endl;
		ansflag[1]=true;
	}
	for(int i=0;i<n;i++)
		if(ans[rec[i].color]&&!ansflag[rec[i].color])
		{
			fout<<rec[i].color<<" "<<ans[rec[i].color]<<endl;
			ansflag[rec[i].color]=true;
		}
	//system("pause");
	return 0;

}