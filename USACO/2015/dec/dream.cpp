#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;

const int inf = 17070509;

int n, m;
vector<vector<int> > matrix;

inline bool valid(int x, int y)
{
	return (x>=0 && y >= 0 && x<n && y<m);
}

inline int orangey(int x, int y)
{
	return (matrix[x][y]==2);
}

int main(void)
{
	ifstream fin("dream.in");
	ofstream fout("dream.out");

	bool done = false;
	fin >> n >> m;

	matrix.clear(); matrix.resize(n, vector<int>(m));

	for(int i = 0;i < n;i++)
	{
		for(int j = 0;j < m;j++) fin >> matrix[i][j];
	}
	
	vector<vector<vector<vector<bool> > > > visited(n, vector<vector<vector<bool> > >(m, vector<vector<bool> >(2, vector<bool>(4, false))));
	int res = inf;
	queue<vector<int> > Q;
	Q.push({0, 0, 0, 0, 0});
	visited[0][0][0][0] = true;
	while(!Q.empty())
	{
		vector<int> top = Q.front();
		Q.pop();
		done = false;
		if(top[0] == n-1 && top[1] == m-1)
		{
			res = min(res, top[4]);
		}
		else if(matrix[top[0]][top[1]] != 0 && !(matrix[top[0]][top[1]] == 3 && !top[2]))
		{
			if(matrix[top[0]][top[1]] == 4)
			{
				if(top[3] == 0)
				{
					if(valid(top[0], top[1]+1))
					{
						if(!visited[top[0]][top[1]+1][0][0])
						{
							visited[top[0]][top[1]+1][0][0] = true;
							Q.push({top[0], top[1]+1, 0, 0, top[4]+1});
							done = true;
						}
					}
				}
				else if(top[3] == 1)
				{
					if(valid(top[0]+1, top[1]))
					{
						if(!visited[top[0]+1][top[1]][0][1])
						{
							visited[top[0]+1][top[1]][0][1] = true;
							Q.push({top[0]+1, top[1], 0, 1, top[4]+1});
							done = true;
						}
					}
				}
				else if(top[3] == 2)
				{
					if(valid(top[0], top[1]-1))
					{
						if(!visited[top[0]][top[1]-1][0][2])
						{
							visited[top[0]][top[1]-1][0][2] = true;
							Q.push({top[0], top[1]-1, 0, 2, top[4]+1});
							done = true;
						}
					}
				}
				else if(top[3] == 3)
				{
					if(valid(top[0]-1, top[1]))
					{
						if(!visited[top[0]-1][top[1]][0][3])
						{
							visited[top[0]-1][top[1]][0][3] = true;
							Q.push({top[0]-1, top[1], 0, 3, top[4]+1});
							done = true;
						}
					}
				}
			}
			if(!done)
			{
				if(valid(top[0], top[1]+1))
				{
					if(!visited[top[0]][top[1]+1][max(top[2], orangey(top[0], top[1]))][top[3]])
					{
						visited[top[0]][top[1]+1][max(top[2], orangey(top[0], top[1]))][top[3]] = true;
						Q.push({top[0], top[1]+1, max(top[2], orangey(top[0], top[1])), top[3], top[4]+1});
					}
				}
				if(valid(top[0], top[1]-1))
				{
					if(!visited[top[0]][top[1]-1][max(top[2], orangey(top[0], top[1]))][top[3]])
					{
						visited[top[0]][top[1]-1][max(top[2], orangey(top[0], top[1]))][top[3]] = true;
						Q.push({top[0], top[1]-1, max(top[2], orangey(top[0], top[1])), top[3], top[4]+1});
					}
				}
				if(valid(top[0]+1, top[1]))
				{
					if(!visited[top[0]+1][top[1]][max(top[2], orangey(top[0], top[1]))][top[3]])
					{
						visited[top[0]+1][top[1]][max(top[2], orangey(top[0], top[1]))][top[3]] = true;
						Q.push({top[0]+1, top[1], max(top[2], orangey(top[0], top[1])), top[3], top[4]+1});
					}
				}
				if(valid(top[0]-1, top[1]))
				{
					if(!visited[top[0]-1][top[1]][max(top[2], orangey(top[0], top[1]))][top[3]])
					{
						visited[top[0]-1][top[1]][max(top[2], orangey(top[0], top[1]))][top[3]] = true;
						Q.push({top[0]-1, top[1], max(top[2], orangey(top[0], top[1])), top[3], top[4]+1});
					}
				}
			}
		}
	}

	if(res == inf) fout << "-1\n";
	else fout << res << "\n";
}