#include "grader.h"
#include <vector>
using namespace std;

const int maxn = int(1e6)+5, maxlog = 21;

int A[maxn], H[maxn], T[maxn][maxlog], node = 0;

void Init()
{
	node = 0;
	for(int i = 0;i < maxn;i++)
	{
		for(int j = 0;j < maxlog;j++) T[i][j] = -1;
	}
}

void TypeLetter(char l)
{
	//cout << node << "\n";
	A[node] = l, T[node][0] = node-1;
	if(node) H[node] = H[node-1]+1;
	else H[node] = 0;
	for(int j = 1;j < maxlog;j++)
	{
		if(T[node][j-1] != -1) T[node][j] = T[T[node][j-1]][j-1];
		else break;
	}
	node++;
	//cout << node << "\n";
}

void UndoCommands(int u)
{
	int rep = node-u-1;
	A[node] = A[rep];
	T[node][0] = T[rep][0], H[node] = H[rep];
	for(int j = 1;j < maxlog;j++)
	{
		if(T[node][j-1] != -1) T[node][j] = T[T[node][j-1]][j-1];
		else break;
	}
	node++;
}

char GetLetter(int p)
{
	int jump = H[node-1]-p;
	//cout << jump << "\n";
	int cur = node-1;
	for(int j = maxlog;j >= 0;j--)
	{
		if(jump&(1<<j)) cur = T[cur][j];
	}
	return char(A[cur]);
}


