/*
ID: caiweid3
PROG: starry
LANG: C++              
*/

#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <stdlib.h>
#include <vector>
#include <algorithm>

using namespace std;

struct POINT
{
	POINT(){};
	POINT(int i, int j):x(i),y(j){};
	int x, y;
};

struct PATTERN
{
	int w, h;
	char hash;
	vector<POINT> pic;
};

bool visited[101][101];
int mov[8][2] = {{-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}};
char sky_map[101][101];
int h, w, num_pattern;
PATTERN patt[30];
char hash_num = 'a';


bool cmp (const POINT &a, const POINT &b)
{
	if (a.x == b.x)
		return a.y < b.y;
	else
		return a.x < b.x;
}

bool Compare(const PATTERN &a, const PATTERN &b)
{
	if (a.pic.size() != b.pic.size() || a.w != b.w || a.h != b.h)
		return false;
	for (unsigned int i = 0; i < a.pic.size(); i++)
		if (a.pic[i].x != b.pic[i].x || a.pic[i].y != b.pic[i].y)
			return false;
	return true;
}

void Rotate(PATTERN &p)
{
	int tmp;
	for (unsigned int i = 0; i < p.pic.size(); i++)
	{
		tmp = p.pic[i].y;
		p.pic[i].y = p.h-p.pic[i].x+1;
		p.pic[i].x = tmp;
	}
	sort(p.pic.begin(), p.pic.end(), cmp);
	tmp = p.h;
	p.h = p.w;
	p.w = tmp;
}

void Flip(PATTERN &p)
{
	for (unsigned int i = 0; i < p.pic.size(); i++)
		p.pic[i].y = p.w-p.pic[i].y+1;
	sort(p.pic.begin(), p.pic.end(), cmp);
}

void FloodFill(const POINT &p)
{
	int left, right, down, up, nexti, nextj, num;
	POINT tmp;
	PATTERN cluster;
	queue <POINT> q;
	cluster.pic.push_back(p);
	q.push(p);
	left = right = p.y;
	up = down = p.x;
	visited[p.x][p.y] = true;
	num = 1;

	while (!q.empty())
	{
		tmp = q.front();
		q.pop();
		for (int i = 0; i < 8; i++)
		{
			nexti = tmp.x+mov[i][0];
			nextj = tmp.y+mov[i][1];
			if (nexti>=0 && nexti<=h && nextj>=0 && nextj<=w && sky_map[nexti][nextj]=='1' && !visited[nexti][nextj])
			{
				visited[nexti][nextj] = true;
				num++;
				if (nexti < up)
					up = nexti;
				if (nexti > down)
					down = nexti;
				if (nextj < left)
					left = nextj;
				if (nextj > right)
					right = nextj;
				q.push(POINT(nexti, nextj));
				cluster.pic.push_back(POINT(nexti, nextj));
			}
		}
	}
	cluster.h = down-up+1;
	cluster.w = right-left+1;
	for (unsigned int i = 0; i < cluster.pic.size(); i++)
	{
		cluster.pic[i].x -= up-1;
		cluster.pic[i].y -= left-1;
	}
	sort(cluster.pic.begin(), cluster.pic.end(), cmp);
	bool flag = true;
	for (int i = 0; i < num_pattern; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (Compare(patt[i], cluster))
			{
				cluster.hash = patt[i].hash;
				flag = false;
				break;
			}
			Rotate(patt[i]);
		}
		Flip(patt[i]);
		for (int j = 0; j < 4; j++)
		{
			if (Compare(patt[i], cluster))
			{
				cluster.hash = patt[i].hash;
				flag = false;
				break;
			}
			Rotate(patt[i]);
		}
	}

	if (flag)
	{
		cluster.hash = hash_num;
		hash_num++;
		patt[num_pattern] = cluster;
		num_pattern++;
	}
	for (unsigned int i = 0; i < cluster.pic.size(); i++)
	{
		//cout << cluster.pic[i].x << " " << cluster.pic[i].y << endl;
		sky_map[cluster.pic[i].x+up-1][cluster.pic[i].y+left-1] = cluster.hash;
		//cout << cluster.pic[i].x+up-1 << " " << cluster.pic[i].y+left-1 << endl;;
	}
}

int main()
{
	freopen("starry.in","r",stdin);
	freopen("starry.out","w",stdout);
	cin >> w >> h;
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			cin >> sky_map[i][j];
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
		{
			if (sky_map[i][j] == '1')
				FloodFill(POINT(i, j));
		}
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
			cout << sky_map[i][j];
		cout << endl;
	}
	//system("pause");
}