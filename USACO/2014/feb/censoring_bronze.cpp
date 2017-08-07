/*
	PROG: COW
	LANG: C++
	ID: nibnalin
*/
//USACO February Contest

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main(void)
{
	ios_base::sync_with_stdio(0);
	ifstream fin ("censor.in");
	ofstream fout ("censor.out");
	string S, T;
	fin >> S >> T;

	//Might use K-M-P, but unsure how to implement
	//Using brute force, should probably work

	size_t st = S.find(T);
	while(st != string::npos)
	{
		S.erase(st, int(T.size()));
		st = S.find(T);
	}
	fout << S;
}