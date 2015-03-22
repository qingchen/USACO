/*
ID: caiweid3
PROG: buylow
LANG: C++              
*/

#include <iostream>
#include <fstream>
#include <memory.h>
#include <stdlib.h>

using namespace std;

class BIGINT
{
public:
	BIGINT():size(0){}
	BIGINT(long a)
	{
		if (a == 0)
		{
			size = 1;
			s[0] = 0;
		}
		else
		{
			int pos = 0;
			while (a)
			{
				s[pos++] = a % 10;
				a /= 10;
			}
			size = pos;
		}
	}
	BIGINT operator +(const BIGINT &a) const;
	BIGINT operator =(const BIGINT &a);
	int s[100];
	unsigned int size;
};


BIGINT BIGINT::operator+(const BIGINT &a) const
{
	int d = 0;
	int i;
	BIGINT res;

	if (a.size > this->size)
	{
		for (i = 0; i < this->size; i++)
		{	
			res.s[i] = (a.s[i] + this->s[i] + d) % 10;
			d = (a.s[i] + this->s[i] + d) / 10;
		}
		while (d && i < a.size)
		{
			res.s[i] = (d + a.s[i]) % 10;
			d = (d + a.s[i]) / 10;
			i++;
		}
		if (d)
			res.s[i++] = d;
		for(;i < a.size; i++)
			res.s[i] = a.s[i];
		res.size = i;
	}
	else if(a.size == this->size)
	{
		for (i = 0; i < this->size; i++)
		{
			res.s[i] = (a.s[i] + this->s[i] + d) % 10;
			d = (a.s[i] + this->s[i] + d) / 10;
		}
		if (d)
			res.s[i++] = d;
		res.size = i;
	}
	else
	{
		for (i = 0; i < a.size; i++)
		{
			res.s[i] = (a.s[i] + this->s[i] + d) % 10;
			d = (a.s[i] + this->s[i] + d) / 10;
		}
		while (d && i < this->size)
		{
			res.s[i] = (d + this->s[i]) % 10;
			d = (d + this->s[i]) / 10;
			i++;
		}
		if (d)
			res.s[i++] = d;
		for(;i < this->size; i++)
			res.s[i] = this->s[i];
		res.size = i;
	}
	return res;
}

BIGINT BIGINT::operator =(const BIGINT &a)
{
	this->size = a.size;
	for (int i = 0; i < a.size; i++)
		this->s[i] = a.s[i];
	return *this;
}



int main()
{
	freopen("buylow.in","r",stdin);
	freopen("buylow.out","w",stdout);
	long long data[5001];
	int n;
	int dp[5001];
	BIGINT cnt[5001];
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> data[i];
		dp[i] = 1;
		//cnt[i] = BIGINT(1);
	}

	for (int i = 1; i < n; i++)
		for (int j = 0; j < i; j++)
			if (data[i] < data[j])
				dp[i] = max(dp[i],dp[j]+1);
	for (int i = 0; i < n; i++)
	{
		if (dp[i] == 1)
			cnt[i] = BIGINT(1);
		else
			cnt[i] = BIGINT(0);
	}
	bool flag;
	for (int i = 1; i < n; i++)
		for (int j = 0; j < i; j++)
			if (data[i]<data[j] && dp[i]==dp[j]+1)
			{
				flag = true;
				for (int k = j + 1; k < i; k++)
					if (data[k] == data[j])
					{
						flag = false;
						break;
					}
				if (flag)
					cnt[i] = cnt[i] + cnt[j];
			}

	int ans = 0;
	for (int i = 0; i < n; i++)
		ans = max(ans, dp[i]);
	cout << ans << " ";
	BIGINT ans2(0);
	for (int i = 0; i < n; i++)
	{
		if (dp[i] == ans)
		{
			flag = true;
			for (int j = i + 1; j < n; j++)
				if(data[j] == data[i] && dp[j] == dp[i])
				{
					flag = false;
					break;
				}
			if(flag)
				ans2 = ans2 + cnt[i];
		}
			
	}
	for (int i = 0; i < ans2.size; i++)
		cout <<ans2.s[ans2.size-i-1];
	cout << endl;
	//system("pause");
}