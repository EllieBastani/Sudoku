#include "SodukoSolver.h"
#include <functional> 

#include <vector>
#define UNASSIGNED 0

SodukoSolver::SodukoSolver(int sTable[][9])
{
	memcpy(table, sTable, sizeof(table));
}

bool SodukoSolver::Solve()
{
	bool hasChanged = true;
	int counter = 0;

	while (hasChanged)
	{
		hasChanged = false;
		for (int i = 0; i < 9; ++i)
		{
			for (int j = 0; j < 9; j++)
			{
				if (table[i][j] == UNASSIGNED)
				{
					if (CalcCell(i, j))
					{
						hasChanged = true;
						counter++;
					}
				}
			}
			// if we could not find a single possibility for a cell,
			// we look for more possibilities in the places with less empty cell
			if (i == 8 && !hasChanged)
			{ 
				bool didFind = LookForMorePossibilities();
				if (didFind)
				{
					hasChanged = true;
				}
				else
				{
					// the last solution . by this point,  most Sudokus are solved.
					 //the ones that are not , most of the cells are filled, so the recursive won't be very expensive.
					SolveRecursively(0, 0);
				}
			}
				
		}
	}

	return IsSolved();
}

bool SodukoSolver::IsSolved()
{
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; j++)
		{
			if (table[i][j] == UNASSIGNED)
			{
				return false;
			}
		}
	}
	return true;
}

bool SodukoSolver::CalcCell(int x, int y)
{
	list<int> possibilityies = GetPossibilitiesForCell(x, y);
	int p = possibilityies.size();
	if (possibilityies.size() == 1)
	{
		table[x][y] = possibilityies.front();
		return true;
	}
	else
	{
		return false;
	}
}

bool SodukoSolver::LookForMorePossibilities()
{
	vector<vector<int>> orderedPosLis;
	//<row or col,num row or col,number of empties>

	for (int i = 0; i < 9; ++i)
	{
		int count = std::count(std::begin(table[i]), std::end(table[i]), 0);
		
		int addIndex = 0;
		for (; addIndex < orderedPosLis.size(); ++addIndex)
		{
			if (orderedPosLis[addIndex][2] > count)
			{
				addIndex;
				break;
			}
		}

		vector<int> newV{ 0, i, count };
		auto it = orderedPosLis.begin();
		orderedPosLis.insert(it+ addIndex, newV);

	}

	for (int i = 0; i < 9; ++i)
	{
		int count = 0;
		for (int j = 0; j < 9; j++)
		{
			if (table[j][i] == UNASSIGNED)
				count++;
		}

		int addIndex = 0;
		for (; addIndex < orderedPosLis.size(); ++addIndex)
		{
			if (orderedPosLis[addIndex][2] > count)
			{
				addIndex;
				break;
			}
		}
		
		vector<int> newV{ 1, i, count };
		auto it = orderedPosLis.begin();
		orderedPosLis.insert(it+addIndex, newV);

	}

	for (int index=0; index< orderedPosLis.size(); index++)
	{
		vector<int> posItem = orderedPosLis[index];

		vector<vector<int>> posibList;

		for (int i = 0; i < 9; i++)
		{
			if (posItem[0] == 0)
			{
				if (table[posItem[1]][i] == UNASSIGNED)
				{
					list<int> pCells = GetPossibilitiesForCell(posItem[1], i);
					vector<int> v(pCells.begin(), pCells.end());
					posibList.push_back( v );
				}

			}
			else
			{

				if (table[i][posItem[1]] == UNASSIGNED)
				{
					list<int> pCells = GetPossibilitiesForCell( i, posItem[1]);
					vector<int> v(pCells.begin(), pCells.end());
					posibList.push_back(v);
				}

			}
		}

		//got all possibilities for one row or one column
		//check if there is one value with one possiblity

		for (int i = 1; i < 10; ++i)
		{
			int count = 0;
			int emptyCellPos, possibInx;

			for (int a = 0; a < posibList.size(); ++a)
			{
				for (int b = 0; b < posibList[a].size(); ++b)
				{
					if (posibList[a][b] == i)
					{
						count++;
						emptyCellPos = a;
						possibInx = b;
					}
				}
			}
			if (count == 1)
			{
				int emptyIndex = -1;
				int xInx, yInx;
				for (int j = 0; j < 9; ++j)
				{
					if (posItem[0] == 0)
					{
						xInx = posItem[1];
						yInx = j;
					}
					else
					{
						xInx = j;
						yInx = posItem[1];
					}

					if (table[xInx][yInx] == UNASSIGNED)
					{
						++emptyIndex;
						if (emptyIndex == emptyCellPos)
						{
							table[xInx][yInx] = i;
							return true;
						}
					}
				}
			}
		}

	}

	return false;
}

list<int> SodukoSolver::GetPossibilitiesForCell(int x, int y)
{
	list<int> possibilityies{ 1,2,3,4,5,6,7,8,9 };
	int squareX = x-x%3;
	int squareY = y-y%3;

	// check the Square
	for (int i = squareX; i < squareX + 3; ++i)
	{
		for (int j = squareY; j < squareY + 3; j++)
		{
			if (table[i][j] != UNASSIGNED) // it is not the current cell since is not zero
			{
				possibilityies.remove(table[i][j]);
			}
		}
	}

	//check the horizental line
	for (int i = 0; i < 9; ++i)
	{
		if (table[x][i] != UNASSIGNED)
		{
			possibilityies.remove(table[x][i]);
		}
	}

	//check vertical line
	for (int i = 0; i < 9; ++i)
	{
		if (table[i][y] != 0)
		{
			possibilityies.remove(table[i][y]);
		}
	}
	return possibilityies;
}

bool SodukoSolver::SolveRecursively(int x, int y)
{
	int nextX,nextY;
	list<int> possibilityies;
	bool foundCell;

	//if it is the first time we call this recursive function , find the firts empty cell
	if (x==0 && y==0)
	  findNextCell(0, 0, x, y);

	possibilityies = GetPossibilitiesForCell(x, y);

	while (possibilityies.size() > 0)
	{
		//possibilityies = GetPossibilitiesForCell(x, y);
		//if (possibilityies.size() == 0)
		//	return false;

		int val = possibilityies.front();

		table[x][y] = val;
		foundCell = findNextCell(x, y+1, nextX, nextY);
		if (foundCell)
		{
			bool solved =  SolveRecursively(nextX, nextY);
			if (solved)
				return true;
		}
		else if (IsSolved())
		{
			return true;
		}

		table[x][y] = UNASSIGNED;
		possibilityies.pop_front();
	}

	return false;
}

bool SodukoSolver::findNextCell(int curX, int curY, int& nextX, int& nextY)
{
	int startY = curY;

	for (int i = curX ; i < 9; ++i)
	{
		for (int j = startY; j < 9; j++)
		{
			if ( table[i][j] == UNASSIGNED)
			{
				nextX = i;
				nextY = j;
				return true;
			}
		}
		startY = 0;
	}

	return false;
}