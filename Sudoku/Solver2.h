#pragma once

#include <list>
using namespace std;

class Solver2
{
private:
	int table[9][9];
	bool CalcCell(int x, int y);
	int GetSquareStart(int index);
	void LookToFind();
	list<int> GetPossibilitiesForCell(int x, int y);
public:
	Solver2(int table[][9]);
	bool Solve();
	bool IsSolved();
};

