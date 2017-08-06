/**
 *	Author:	º®½­Ñ©1719
 *	Date:	2017.8.6
 *	Email:	<lkysyzxz@outlook.com>
 *	Detail:	This code show the algorithm named A*.The map is a char matrix.
 *			In the map, '.' means road, 'X' means wall.'S' means the start point.'E' means the end point.
 *			The output is a char matrix.
 *			In the output map, '*' indicate this point has been put into open set.'-' is the shortest path from the start point to the end point.
 *	Other:	Have your fun
 */
#include<iostream>
#include<fstream>
#include<algorithm>
#include<set>
#include<string>
using namespace std;
struct Node
{
	int x, y;
	int f;

	Node(int xx, int yy, int ff) :x(xx), y(yy), f(ff) {

	}

	bool operator<(const Node& t)const {
		return f < t.f;
	}

	bool operator==(const Node& t)const {
		return t.x == x&&t.y == y;
	}
};

struct Point {
	int x;
	int y;
	bool operator<(const Point& t)const {
		if (x != t.x)return x < t.x;
		else return y < t.y;
	}


};


int n, m;
Point startPoint;
Point endPoint;
char mp[555][555] = { 0 };
int G[555][555] = { 0 };
int addX[4] = { 0,-1,0,1 };
int addY[4] = { -1,0,1,0 };
Point path[555][555] = { 0 };
set<Node> openSet;
set<Point> closeSet;
int HValue(int x, int y)
{
	int dx = abs(x - endPoint.x);
	int dy = abs(y - endPoint.y);
	return dx + dy;
}
int FValue(int x, int y, int nx, int ny) {
	return G[x][y] + 1 + HValue(nx, ny);
}

set<Node>::iterator FindNode(const Node& t)
{
	set<Node>::iterator p = openSet.begin();
	while (p != openSet.end())
	{
		if ((*p) == t) {
			return p;
		}
		p++;
	}
	return openSet.end();
}
void BeginAstart()
{
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++)
		{
			G[i][j] = 0x3f3f3f3f;
		}
	}
	G[startPoint.x][startPoint.y] = -1;
	path[startPoint.x][startPoint.y] = startPoint;
	openSet.insert(Node(startPoint.x, startPoint.y, FValue(startPoint.x, startPoint.y, startPoint.x, startPoint.y)));
	do
	{
		set<Node>::iterator pu = openSet.begin();
		Node u = *pu;
		openSet.erase(pu);
		closeSet.insert(Point{ u.x,u.y });
		int ux = u.x;
		int uy = u.y;

		if (ux == endPoint.x&&uy == endPoint.y)
		{
			break;
		}

		int fx = path[ux][uy].x;
		int fy = path[ux][uy].y;
		G[ux][uy] = G[fx][fy] + 1;

		for (int i = 0; i < 4; i++)
		{
			int nx = ux + addX[i];
			int ny = uy + addY[i];
			if (nx >= 1 && nx <= n&&ny >= 1 && ny <= m&&mp[nx][ny] != 'X') {
				int F = FValue(ux, uy, nx, ny);
				Node nxNode(nx, ny, F);
				Point nxPoint{ nx,ny };
				if (closeSet.find(nxPoint) == closeSet.end())
				{
					set<Node>::iterator p = FindNode(nxNode);
					
					if (p == openSet.end())
					{
						//This point not in the open set.
						path[nx][ny] = Point{ ux,uy };
						openSet.insert(nxNode);
						if (mp[nx][ny] != 'E'&&mp[nx][ny] != 'S')
							mp[nx][ny] = '*';
					}
					else
					{
						//This point in the open set.
						Node newNode = *p;
						openSet.erase(p);
						if (F < newNode.f)
							newNode.f = F;
						openSet.insert(newNode);
						if (mp[nx][ny] != 'E'&&mp[nx][ny] != 'S')
							mp[newNode.x][newNode.y] = '*';
					}
				}
				else
				{
					continue;
				}
			}
		}

	} while (!openSet.empty());


}

void PrintPath(int x, int y)
{
	if (x == path[x][y].x && y == path[x][y].y)
	{
		return;

	}
	else
	{
		PrintPath(path[x][y].x, path[x][y].y);
		if (mp[x][y] != 'E' && mp[x][y] != 'S')
			mp[x][y] = '-';
	}
}

void EndAstart()
{
	PrintPath(endPoint.x, endPoint.y);
	fstream fout("out.txt", ios::ios_base::app | ios_base::out);
	fout << "Result Map" << endl;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			fout << mp[i][j];
		}
		fout << endl;
	}
	fout << endl;
	fout.close();
	closeSet.clear();
	openSet.clear();
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			path[i][j] = Point{ 0,0 };
			mp[i][j] = 0;
		}
	}
}

int main()
{
	int T;
	ifstream fin("in.txt", ios_base::in);
	fin >> T;
	while (T--) {
		fin >> n >> m;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				fin >> mp[i][j];
				if (mp[i][j] == 'S')
				{
					startPoint.x = i;
					startPoint.y = j;
				}
				else if (mp[i][j] == 'E')
				{
					endPoint.x = i;
					endPoint.y = j;
				}
			}
			fin.get();
		}
		BeginAstart();

		EndAstart();
	}
	fin.close();
	return 0;
}