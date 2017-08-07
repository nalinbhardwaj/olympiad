/*
	PROG: COW
	LANG: C++
	ID: nibnalin
*/
//USACO February Contest

#include <fstream>
#include <vector>
using namespace std;

int main(void)
{
	ios_base::sync_with_stdio(0);
	ifstream fin ("cow.in");
	ofstream fout ("cow.out");

	long long n;
	string ins;
	fin >> n;
	fin >> ins;

	vector<long long> combi(3, 0);
	for(long long i = 0;i < n;i++)
	{
		if(ins[i] == 'C')
		{
			combi[0]++;
		}
		else if(ins[i] == 'O')
		{
			combi[1] += combi[0];
		}
		else
		{
			combi[2] += combi[1];
		}
	}

	fout << combi[2] << endl;
}