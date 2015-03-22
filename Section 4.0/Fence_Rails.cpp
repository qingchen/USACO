/*
ID: caiweid3
PROG: fence8
LANG: C++              
*/


#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <algorithm>

using namespace std;


int n, r;
int boards[51], tboards[51], rails[1024], lenth[1024];
int total_boards, residual;
int mid;

bool Search(int depth, int pos)
{
	if (depth == 0)
		return true;
	if (total_boards < residual + lenth[mid])
		return false;

	for (int i = n; i >= pos; i--)
	{
		if (tboards[i] >= rails[depth])
		{
			tboards[i] -= rails[depth];
			if(tboards[i] < rails[1])
				residual += tboards[i];

			if(rails[depth] == rails[depth+1])
			{
				if(Search(depth-1, i))
					return true;
			}
			else if(Search(depth-1,1))
				return true;

			if(tboards[i] < rails[1])
				residual -= tboards[i];
			tboards[i] += rails[depth];
			
		}
	}
	return false;
}

int main() 
{
	freopen("fence8.in","r",stdin);
    freopen("fence8.out","w",stdout);

	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> boards[i];
		total_boards += boards[i];
	}
	cin >> r;
	for (int i = 1; i <= r; i++)
		cin >> rails[i];
		
	sort(boards+1, boards+n+1);
	sort(rails+1, rails+r+1);

	for (int i = 1; i <= r; i++)
		lenth[i] += lenth[i-1]+rails[i];

	while (rails[r] > boards[n])
		r--;
	
	int left, right;
	left = 0;
	right = r;
	mid = (left + right) / 2;

	while (left <= right)
	{
		for (int i = 1; i <= n; i++)
			tboards[i] = boards[i];
		residual = 0;

		if (Search(mid, 1))
			left = mid + 1;
		else
			right = mid - 1;
		mid = (left + right) / 2;
	}
	
	cout << mid << endl;
//	system("pause");
	return 0;
	
}
