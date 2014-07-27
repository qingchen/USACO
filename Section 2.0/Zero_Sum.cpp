/*
ID: caiweid3
PROG: zerosum
LANG: C++              
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>


using namespace std;

ofstream fout ("zerosum.out");
ifstream fin ("zerosum.in");

int n;
char ops[10];
void dfs(int data,int sum,int depth)
{
	if(depth==n)
	{
		if(sum==0)
		{
			for(int i=0;i<n-1;i++)
				fout<<i+1<<ops[i];
			fout<<n<<endl;
		}
		return ;
	}
	ops[depth-1]=' ';
	int i=depth-2;
	for(;i>=0;i--)
		if(ops[i]!=' ')
			break;
	if(ops[i]!=' ')
	{
		if(ops[i]=='-')
			dfs(data*10+depth+1,sum+data-data*10-depth-1,depth+1);
		else
			dfs(data*10+depth+1,sum-data+data*10+depth+1,depth+1);
	}
	else
		dfs(data*10+depth+1,sum*10+depth+1,depth+1);
	ops[depth-1]='+';
	dfs(depth+1,sum+depth+1,depth+1);
	ops[depth-1]='-';
	dfs(depth+1,sum-depth-1,depth+1);
}
int main() 
{		
	fin>>n;
	ops[0]=' ';
	dfs(12,12,2);
	ops[0]='+';
	dfs(2,3,2);
	ops[0]='-';
	dfs(2,-1,2);
	
	//system("pause");
    return 0;
	
}
