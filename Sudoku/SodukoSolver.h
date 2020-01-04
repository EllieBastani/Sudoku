#pragma once

#include <list>
using namespace std;

class SodukoSolver
{
private:
	int table[9][9];
	bool CalcCell(int x, int y);
	bool LookForMorePossibilities();
	list<int> GetPossibilitiesForCell(int x, int y);
	bool SolveRecursively(int curX, int curY);
	bool findNextCell(int curX, int curY, int& nextX, int& nextY);

public:
	SodukoSolver(int table[][9]);
	bool Solve();
	bool IsSolved();
};

