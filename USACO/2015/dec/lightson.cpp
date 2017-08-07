#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>
#include <queue>
using namespace std;

typedef pair<int, int> ii;

int n, m;

inline bool valid(int a, int b)
{
	return (a>=0 && b>=0 && a<n && b<n);
}

int main(void)
{
	ifstream fin("lightson.in");
	ofstream fout("lightson.out");

	fin >> n >> m;
	vector<vector<vector<ii> > > switches(n+1, vector<vector<ii> >(n+1));
	ii st, en;
	while(m--)
	{
		fin >> st.first >> st.second >> en.first >> en.second;
		switches[st.first-1][st.second-1].push_back({en.first-1, en.second-1});
	}

	vector<vector<bool> > visited(n+1, vector<bool>(n+1, false)), light(n+1, vector<bool>(n+1, false));
	queue<ii> Q;
	Q.push({0, 0});
	visited[0][0] = true;
	light[0][0] = true;

	while(!Q.empty())
	{
		ii top = Q.front();
		Q.pop();

		for(auto it: switches[top.first][top.second])
		{
			light[it.first][it.second] = true;

			if(!visited[it.first][it.second])
			{
				if(valid(it.first-1, it.second))
				{
					if(visited[it.first-1][it.second])
					{
						visited[it.first][it.second] = true;
						Q.push({it.first, it.second});
					}
				}

				if(valid(it.first+1, it.second))
				{
					if(visited[it.first+1][it.second])
					{
						visited[it.first][it.second] = true;
						Q.push({it.first, it.second});
					}
				}

				if(valid(it.first, it.second-1))
				{
					if(visited[it.first][it.second-1])
					{
						visited[it.first][it.second] = true;
						Q.push({it.first, it.second});
					}
				}
				
				if(valid(it.first, it.second+1))
				{
					if(visited[it.first][it.second+1])
					{
						visited[it.first][it.second] = true;
						Q.push({it.first, it.second});
					}
				}
			}
		}

		if(valid(top.first-1, top.second))
		{
			if(light[top.first-1][top.second] && !visited[top.first-1][top.second])
			{
				visited[top.first-1][top.second] = true;
				Q.push({top.first-1, top.second});
			}
		}
		if(valid(top.first+1, top.second))
		{
			if(light[top.first+1][top.second] && !visited[top.first+1][top.second])
			{
				visited[top.first+1][top.second] = true;
				Q.push({top.first+1, top.second});
			}
		}
		if(valid(top.first, top.second-1))
		{
			if(light[top.first][top.second-1] && !visited[top.first][top.second-1])
			{
				visited[top.first][top.second-1] = true;
				Q.push({top.first, top.second-1});
			}
		}
		if(valid(top.first, top.second+1))
		{
			if(light[top.first][top.second+1] && !visited[top.first][top.second+1])
			{
				visited[top.first][top.second+1] = true;
				Q.push({top.first, top.second+1});
			}
		}
	}

	int res = 0;

	for(int i = 0;i < n;i++)
	{
		for(int j = 0;j < n;j++) res += light[i][j];
	}
	
	fout << res << "\n";
}