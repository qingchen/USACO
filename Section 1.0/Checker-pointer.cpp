/*
ID: caiweid3
PROG: checker
LANG: C++              
*/


#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

ofstream fout ("checker.out");
ifstream fin ("checker.in");

int n;

struct Node
{
	Node *U,*D,*L,*R,*C;
	int S,NAME;
}*h;

Node *ans[20];
int path[3][20];
int count;

void Cover(Node *c)
{
	c->R->L=c->L;
	c->L->R=c->R;
	for(Node *i=c->D;i!=c;i=i->D)
	{
		for(Node *j=i->R;j!=i;j=j->R)
		{
			j->U->D=j->D;
			j->D->U=j->U;
			j->C->S--;
		}
	}
}

void Uncover(Node *c)
{
	for(Node* i=c->U;i!=c;i=i->U)
		for(Node* j=i->L;j!=i;j=j->L)
		{
			j->D->U=j;
			j->U->D=j;
			j->C->S++;
		}
		c->R->L=c;
		c->L->R=c;
}

void Search(int k)
{
	if(k==n)
	{
		count++;
		int tmp[20],datatmp;
		for(int i=0;i<n;i++)
			tmp[ans[i]->C->NAME-1]=ans[i]->R->C->NAME-n;
		for(int i=0;i<n;i++)
		{
			if(tmp[i]>path[0][i])
				break;
			if(tmp[i]<path[0][i])
			{
				for(int j=0;j<n;j++)
				{
					datatmp=tmp[j];
					tmp[j]=path[0][j];
					path[0][j]=datatmp;
				}
				break;
			}
		}
		for(int i=0;i<n;i++)
		{
			if(tmp[i]>path[1][i])
				break;
			if(tmp[i]<path[1][i])
			{
				for(int j=0;j<n;j++)
				{
					datatmp=tmp[j];
					tmp[j]=path[1][j];
					path[1][j]=datatmp;
				}
				break;
			}
		}
		for(int i=0;i<n;i++)
		{
			if(tmp[i]>path[2][i])
				break;
			if(tmp[i]<path[2][i])
			{
				for(int j=0;j<n;j++)
				{
					datatmp=tmp[j];
					tmp[j]=path[2][j];
					path[2][j]=datatmp;
				}
				break;
			}
		}
		return;
	}
	Node *c;
	int s=100;
	for(Node* j=h->R;j->NAME<=n;j=j->R)
	{
		if(j->S<s)
		{
			c=j;
			s=j->S;
		}
	}
	Cover(c);
	for(Node* r=c->D;r!=c;r=r->D)
	{
		ans[k]=r;
		for(Node* j=r->R;j!=r;j=j->R)
			Cover(j->C);
		Search(k+1);
		r=ans[k],c=r->C;
		for(Node *j=r->L;j!=r;j=j->L)
			Uncover(j->C);
	}
	Uncover(c);
}

int main() 
{
	
#if 1
    
    //int a, b;
    //fin >> a >> b;
    //fout << a+b << endl;
#endif
	int max_column;
	fin >> n;
	max_column=n+n+n*2-3+n*2-3;
	h=new Node;
	Node *tmp,*start=NULL,*pre=h;
	for(int i=0;i<max_column;i++)
	{
		tmp=new Node;
		tmp->L=pre;
		pre->R=tmp;
		tmp->U=tmp;
		tmp->D=tmp;
		tmp->S=0;
		tmp->NAME=i+1;
		pre=tmp;
	}
	tmp->R=h;
	h->L=tmp;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			for(Node* k=h->R;k!=h;k=k->R)
			{
				if(k->NAME==i)
				{
					start=new Node;
					start->C=k;
					start->U=k->U;
					start->D=k;
					k->U->D=start;
					k->U=start;
					k->S++;
					pre=start;
				}
				if(k->NAME==j+n)
				{
					tmp=new Node;
					tmp->L=pre;
					pre->R=tmp;
					tmp->C=k;
					tmp->U=k->U;
					tmp->D=k;
					k->U->D=tmp;
					k->U=tmp;
					k->S++;
					pre=tmp;
				}
				if((k->NAME==i+j-2+2*n)&&(i+j!=2)&&(i+j!=2*n))
				{
					tmp=new Node;
					tmp->L=pre;
					pre->R=tmp;
					tmp->C=k;
					tmp->U=k->U;
					tmp->D=k;
					k->U->D=tmp;
					k->U=tmp;
					k->S++;
					if((i==1&&j==n)||(i==n&&j==1))
					{
						tmp->R=start;
						start->L=tmp;
					}
					pre=tmp;
				}
				//cout<<k->NAME<<" "<<5*n-j+i-1<<endl;
				if((k->NAME==5*n-j+i-4)&&((i!=n||j!=1)&&(i!=1||j!=n)))
				{
					tmp=new Node;
					tmp->L=pre;
					pre->R=tmp;
					tmp->C=k;
					tmp->U=k->U;
					tmp->D=k;
					k->S++;
					k->U->D=tmp;
					k->U=tmp;		
					tmp->R=start;
					start->L=tmp;
				}
			}
		}
	for(int i=0;i<n;i++)
		path[0][i]=path[1][i]=path[2][i]=n;
	Search(0);
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<n-1;j++)
			fout<<path[i][j]<<" ";
		fout<<path[i][n-1]<<endl;
	}
	fout<<count<<endl;
	//printf("%d\n",count);
	//system("pause");
    return 0;
	
}
