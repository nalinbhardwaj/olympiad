#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
using namespace std;

int n;

char cur[int(1e7)+50], tmp[int(1e7)+50];

string Arep = "abcbacbcabcba", Brep = "bcacbacabcacb", Crep = "cabacbabcabac";

void recurse()
{
	cur[0] = 'a'; tmp[0] = 'z';
	for(int i = 1;i < int(1e7)+20;i++) cur[i] = 'z', tmp[i] = 'z';
	while(true)
	{
		int curidx = 0;
		for(int i = 0;cur[i] != 'z';i++)
		{
			if(cur[i] == 'a')
			{
				for(int j = 0;j < int(Arep.size());j++) tmp[curidx++] = Arep[j];
			}
			else if(cur[i] == 'b')
			{
				for(int j = 0;j < int(Arep.size());j++) tmp[curidx++] = Brep[j];
			}
			else
			{
				for(int j = 0;j < int(Arep.size());j++) tmp[curidx++] = Crep[j];
			}

			if(curidx >= int(1e7))
			{
				for(int i = 0;i < n;i++) printf("%c", tmp[i]);
				printf("\n");
				exit(0);
			}
		}
		//cout << curidx << "\n";
		if(curidx >= n-1)
		{
			for(int i = 0;i < n;i++) printf("%c", tmp[i]);
			printf("\n");
			exit(0);
		}
		else memcpy(&cur, &tmp, sizeof(tmp));
	}
}

int main(void)
{
	scanf("%d", &n);
	//printf("%d\n", min(DP(n), 4));
	if(n == 1)
	{
		printf("1\na\n");
	}
	else if(n == 2)
	{
		printf("2\nab\n");
	}
	else if(n == 3) printf("2\naba\n");
	else
	{
		printf("3\n");
		//string t = "a";
		recurse();
		//for(int i = 0;i < n;i++) cout << S[i];
		//cout << "\n";
	}
}