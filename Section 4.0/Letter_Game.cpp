/*
ID: caiweid3
PROG: lgame
LANG: C++              
*/

#include <iostream>
#include <string>
#include <fstream>
#include <memory.h>
#include <stdlib.h>
#include <algorithm>
#include <map>
#include <set>
#include <vector>

using namespace std;

int points[26]={2, 5, 4, 4, 1, 6, 5, 5, 1, 7, 6, 3, 5,
	2, 3, 5, 7, 2, 1, 2, 4, 6, 6, 7, 5, 7};
map <string, int> m, crash_id;
map <string, string> d;
string s, letter, pre;
int point, pans;
bool used[10], deleted[10];
set <string> ans;
vector <string> crash;
int num_crash = 1;
int f[6000][10];

void dfs(int depth, unsigned int pos)
{
	if (pos > letter.size())
		return;
	if (depth == 0)
	{
		string tmp1, tmp2, tmp, pre_tmp1, pre_tmp2;
		for (unsigned int i = 0; i < letter.size(); i++)
		{
			if (used[i])
				tmp1 += letter[i];
			else
				tmp2 += letter[i];
		}
		pre_tmp1 = tmp1;
		pre_tmp2 = tmp2;
		if (m[tmp1]+m[tmp2] > pans)
		{
			ans.clear();
			pans = m[tmp1] + m[tmp2];
			if (m[tmp1] && m[tmp2])
			{
				if (d[tmp2] < d[tmp1])
					tmp = d[tmp2] + " " + d[tmp1];
				else
					tmp = d[tmp1] + " " + d[tmp2];
				ans.insert(tmp);
				if (crash_id[tmp1] && crash_id[tmp2])
				{
					for (unsigned int j = 0; j < f[crash_id[pre_tmp1]][0]; j++)
					{
						if (j!=0)
							tmp1 = crash[f[crash_id[pre_tmp1]][j]];
						else
							tmp1 = d[pre_tmp1];
						for (unsigned int k = 0; k < f[crash_id[pre_tmp2]][0]; k++)
						{
							tmp2 = crash[f[crash_id[pre_tmp2]][k]];
							if (!k)
								tmp2 = d[pre_tmp2];
							if (tmp2 < tmp1)
								tmp = tmp2 + " " + tmp1;
							else
								tmp = tmp1 + " " + tmp2;
							ans.insert(tmp);
						}
					}
				}
				else
				{
					if (crash_id[tmp1])
					{
						tmp2 = d[tmp2];
						for (unsigned int j = 1; j < f[crash_id[pre_tmp1]][0]; j++)
						{
							tmp1 = crash[f[crash_id[pre_tmp1]][j]];
							if (tmp2 < tmp1)
								tmp = tmp2 + " " + tmp1;
							else
								tmp = tmp1 + " " + tmp2;
							ans.insert(tmp);
						}
					}
					if (crash_id[tmp2])
					{
						tmp1 = d[tmp1];
						for (unsigned int j = 1; j < f[crash_id[pre_tmp2]][0]; j++)
						{
							tmp2 = crash[f[crash_id[pre_tmp2]][j]];
							if (tmp2 < tmp1)
								tmp = tmp2 + " " + tmp1;
							else
								tmp = tmp1 + " " + tmp2;
							ans.insert(tmp);
						}
					}
				}
			}
			else
			{
				if (m[tmp1])
				{
					tmp = d[tmp1];
					ans.insert(tmp);
					if (crash_id[tmp1])
					{
						for (unsigned int j = 1; j < f[crash_id[pre_tmp1]][0]; j++)
							tmp = crash[f[crash_id[pre_tmp1]][j]];
						ans.insert(tmp);
					}
				}
				else
				{
					tmp = d[tmp2];
					ans.insert(tmp);
					if (crash_id[tmp2])
					{
						for (unsigned int j = 1; j < f[crash_id[pre_tmp2]][0]; j++)
							tmp = crash[f[crash_id[pre_tmp2]][j]];
						ans.insert(tmp);
					}
				}
			}
			//ans.insert(tmp1);
			return;
		}
		if (m[tmp1]+m[tmp2] == pans)
		{
			if (m[tmp1] && m[tmp2])
			{
				if (d[tmp2] < d[tmp1])
					tmp = d[tmp2] + " " + d[tmp1];
				else
					tmp = d[tmp1] + " " + d[tmp2];
				ans.insert(tmp);
				if (crash_id[tmp1] && crash_id[tmp2])
				{
					for (unsigned int j = 0; j < f[crash_id[pre_tmp1]][0]; j++)
					{
						//cout << f[crash_id[tmp1]][0] << endl;
						if (j != 0)
							tmp1 = crash[f[crash_id[pre_tmp1]][j]];
						else
							tmp1 = d[pre_tmp1];
						for (unsigned int k = 0; k < f[crash_id[pre_tmp2]][0]; k++)
						{
							tmp2 = crash[f[crash_id[pre_tmp2]][k]];
							if (!k)
								tmp2 = d[pre_tmp2];
							if (tmp2 < tmp1)
								tmp = tmp2 + " " + tmp1;
							else
								tmp = tmp1 + " " + tmp2;
							ans.insert(tmp);
						}
					}
				}
				else
				{
					if (crash_id[tmp1])
					{
						tmp2 = d[tmp2];
						for (unsigned int j = 1; j < f[crash_id[pre_tmp1]][0]; j++)
						{
							//cout << crash[f[crash_id[tmp1]][j]];
							tmp1 = crash[f[crash_id[pre_tmp1]][j]];
							if (tmp2 < tmp1)
								tmp = tmp2 + " " + tmp1;
							else
								tmp = tmp1 + " " + tmp2;
							ans.insert(tmp);
						}
					}
					if (crash_id[tmp2])
					{
						tmp1 = d[tmp1];
						for (unsigned int j = 1; j < f[crash_id[pre_tmp2]][0]; j++)
						{
							
							tmp2 = crash[f[crash_id[pre_tmp2]][j]];
							if (tmp2 < tmp1)
								tmp = tmp2 + " " + tmp1;
							else
								tmp = tmp1 + " " + tmp2;
							ans.insert(tmp);
						}
					}
				}
			}
			else
			{
				if (m[tmp1])
				{
					tmp = d[tmp1];
					ans.insert(tmp);
					if (crash_id[tmp1])
					{
						for (unsigned int j = 1; j < f[crash_id[pre_tmp1]][0]; j++)
							tmp = crash[f[crash_id[pre_tmp1]][j]];
						ans.insert(tmp);
					}
				}
				else
				{
					tmp = d[tmp2];
					ans.insert(tmp);
					if (crash_id[tmp2])
					{
						for (unsigned int j = 1; j < f[crash_id[pre_tmp2]][0]; j++)
							tmp = crash[f[crash_id[pre_tmp2]][j]];
						ans.insert(tmp);
					}
				}
			}
			//ans.insert(tmp1);
			return;
		}
	}
	else
	{
		for (unsigned int i = pos; i < letter.size(); i++)
		{
			if (!used[i])
			{
				used[i] = true;
				dfs(depth - 1, i + 1);
				used[i] = false;
			}
		}
	}
}

void Erase(int depth, int pos)
{
	int i;
	string::iterator it;
	if (depth == 0)
	{
		letter = pre;
		for (i=0, it = letter.begin(); i < pre.size(); i++)
		{
			if (deleted[i])
			{
				letter.erase(it);
			}
			else
				it++;
		}
		for (i = 0; i < letter.size(); i++)
		{
			memset(used, false, sizeof(used));
			dfs(i,0);
		}
	}
	else
	{
		for (i = 0; i < pre.size(); i++)
		{
			if (!deleted[i])
			{
				deleted[i] = true;
				Erase(depth-1, i+1);
				deleted[i] = false;
			}
		}
	}
}

int main()
{
	freopen("lgame.in","r",stdin);
	freopen("lgame.out","w",stdout);

	ifstream fin("lgame.dict");
	while (fin>>s && s[0]!='.')
	{
		letter = s;
		sort(s.begin(),s.end());
		point = 0;
		for (int i = 0; i < s.size(); i++)
			point += points[s[i]-'a'];

		//cout << m[s] << endl;
		if (m.count(s))
		{
			if (!crash_id.count(s))
			{
				crash_id.insert(pair<string, int> (s, num_crash));
				crash.push_back(letter);
				f[num_crash][0] = 1;
				f[num_crash][f[num_crash][0]++] = crash.size()-1;
				num_crash++;
			}
			else
			{
				crash.push_back(letter);
				f[crash_id[s]][f[num_crash][0]++] = crash.size()-1;
			}
		}
		else
		{
			m.insert(pair<string, int> (s, point));
			d.insert(pair<string, string> (s, letter));
		}
	}
	cin >> letter;
	sort(letter.begin(), letter.end());
	pans = m[letter];
	ans.insert(d[letter]);
	pre = letter;
	for (int i = 0; i <= pre.size() - 3; i++)
	{
		memset(deleted, false, sizeof(deleted));
		Erase(i, 0);
	}
	vector<string> sort_ans;
	for (set<string>::iterator it = ans.begin(); it != ans.end(); it++)
		sort_ans.push_back(*it);
	sort(sort_ans.begin(), sort_ans.end());
	cout << pans << endl;
	for (int i = 0; i < ans.size(); i++)
		cout << sort_ans[i] << endl;
	//system("pause");
}