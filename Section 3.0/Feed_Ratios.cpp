/*
ID: caiweid3
PROG: ratios
LANG: C++              
*/
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

ofstream fout ("ratios.out");
ifstream fin ("ratios.in");

int x[4],y[4],z[4],p[4];

inline int gcd(int a,int b)
{
	return b==0?a:gcd(b,a%b);
}

int main() 
{	
	for(int i=1;i<4;i++)
		fin>>p[i];
	for(int i=1;i<4;i++)
		fin>>x[i];
	for(int i=1;i<4;i++)
		fin>>y[i];
	for(int i=1;i<4;i++)
		fin>>z[i];
	int det;
	det=(x[1]*y[2]*z[3]+y[1]*z[2]*x[3]+z[1]*x[2]*y[3])
       -(x[1]*z[2]*y[3]+y[1]*x[2]*z[3]+z[1]*y[2]*x[3]);
	if(det==0)
	{
		fout<<"NONE"<<endl;
		return 0;
	}
	int a,b,c;
	a=(p[1]*y[2]*z[3]+y[1]*z[2]*p[3]+z[1]*p[2]*y[3])
     -(p[1]*z[2]*y[3]+p[2]*y[1]*z[3]+p[3]*y[2]*z[1]);
    b=(x[1]*p[2]*z[3]+p[1]*z[2]*x[3]+z[1]*x[2]*p[3])
     -(x[1]*z[2]*p[3]+p[1]*x[2]*z[3]+z[1]*p[2]*x[3]);
    c=(x[1]*y[2]*p[3]+y[1]*p[2]*x[3]+y[3]*x[2]*p[1])
     -(x[2]*y[1]*p[3]+y[2]*x[3]*p[1]+x[1]*y[3]*p[2]);
    if(det<0)
    {
        a=-a;
        b=-b;
        c=-c;
        det=-det;
    }
    if(a<0||b<0||c<0)
	{
		fout<<"NONE"<<endl;
		return 0;
	}
    int tmp = gcd(gcd(c,gcd(a,b)),det);
	fout<<a/tmp<<" "<<b/tmp<<" "<<c/tmp<<" "<<det/tmp<<endl;
	//system("pause");
	return 0;
}