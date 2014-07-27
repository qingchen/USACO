/*
ID: caiweid3
PROG: comehome
LANG: C++              
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>


using namespace std;

ofstream fout ("comehome.out");
ifstream fin ("comehome.in");

int map[60][60];
void Floyd()
{
	for(int k=0;k<52;k++)
		for(int i=0;i<52;i++)
			for(int j=0;j<52;j++)
				if(map[i][k]&&map[k][j]&&i!=j)
					if(map[i][j]==0||map[i][k]+map[k][j]<map[i][j])
						map[i][j]=map[i][k]+map[k][j];
			
}
int main() 
{
	int n,tmp;
	char s,e;
	fin>>n;
	for(int i=0;i<n;i++)
	{
		fin>>s>>e>>tmp;
		if(s>='A'&&s<='Z')
			s-='A';
		else
			s=s-'a'+26;
		if(e>='A'&&e<='Z')
			e-='A';
		else
			e=e-'a'+26;
		if(map[s][e]==0||map[s][e]>tmp)
			map[s][e]=map[e][s]=tmp;
	}
	Floyd();
	int cap,ans=1000000000;
	for(int i=0;i<25;i++)
		if(map[i][25]&&ans>map[i][25])
		{
			cap=i;
			ans=map[i][25];
			
		}
	fout<<char('A'+cap)<<" "<<ans<<endl;
	//system("pause");
	return 0;

}