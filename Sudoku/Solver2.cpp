#include "Solver2.h"
#include <functional> 

#include <vector>

Solver2::Solver2(int sTable[][9])
{
	//std::copy(sTable, sTable + 81, table);
	memcpy(table, sTable, sizeof(table));
	//table = sTable;
	int a = sTable[0][0];
	int b = sTable[0][1];
	//std::copy(std::begin(sTable), std::end(sTable), std::begin(table));
	//table = sTable;
}

bool Solver2::Solve()
{
	LookToFind();
	return IsSolved();
}

bool Solver2::IsSolved()
{
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; j++)
		{
			if (table[i][j] == 0)
			{
				return false;
			}
		}
	}
	return true;
}

bool Solver2::CalcCell(int x, int y)
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

int Solver2::GetSquareStart(int index)
{
	if (index < 3)
		return 0;
	else if (index < 6)
		return 3;
	else
		return 6;
}

void Solver2::LookToFind()
{
	vector<vector<int>> possibList;
	vector<int> indexes;

	bool hasChanged = true;

	while (hasChanged)
	{
		hasChanged = false;

		for (int row = 0; row < 9; ++row)
		{
			for (int col = 0; col < 9; col++)
			{
					if (table[row][col] == 0)
					{
						list<int> pCells = GetPossibilitiesForCell(row, col);
						vector<int> v(pCells.begin(), pCells.end());
						possibList.push_back(v);
						indexes.push_back(col);
					}
			}
			
			//check whether there is one number possibilities
			bool foundOne = false;
			for (int num = 1; num < 10; num++)
			{
				int count = 0;
				for (int i = 0; i < possibList.size(); ++i)
				{
					for (int j = 0; j < possibList[i].size(); j++)
					{
						if (possibList[i][j] == num)
						{
							++count;
						}
					}
				}

				if (count == 1)
				{
					for (int i = 0; i < possibList.size(); ++i)
					{
						for (int j = 0; j < possibList[i].size(); j++)
						{
							if (possibList[i][j] == num)
							{
								table[row][indexes[i]] = num;
								foundOne = true;
								hasChanged = true;
							}
						}
					}
				}

				if (foundOne)
				{
					--row;
					break;
				}
			}
			possibList.clear();
			indexes.clear();
		} // end of row loop

		for (int col = 0; col < 9; ++col)
		{
			for (int row = 0; row < 9; row++)
			{
				if (table[row][col] == 0)
				{
					list<int> pCells = GetPossibilitiesForCell(row, col);
					vector<int> v(pCells.begin(), pCells.end());
					possibList.push_back(v);
					indexes.push_back(row);
				}
			}

			//check whether there is one number possibilities
			bool foundOne = false;
			for (int num = 1; num < 10; num++)
			{
				int count = 0;
				for (int i = 0; i < possibList.size(); ++i)
				{
					for (int j = 0; j < possibList[i].size(); j++)
					{
						if (possibList[i][j] == num)
						{
							++count;
						}
					}
				}

				if (count == 1)
				{
					for (int i = 0; i < possibList.size(); ++i)
					{
						for (int j = 0; j < possibList[i].size(); j++)
						{
							if (possibList[i][j] == num)
							{
								table[indexes[i]][col] = num;
								foundOne = true;
								hasChanged = true;
							}
						}
					}
				}

				if (foundOne)
				{
					--col;
					break;
				}
				possibList.clear();
				indexes.clear();
			}
		} // end of col loop

	} // end of while (hasChanged)

	
}

list<int> Solver2::GetPossibilitiesForCell(int x, int y)
{
	list<int> possibilityies{ 1,2,3,4,5,6,7,8,9 };
	int squareX = GetSquareStart(x);
	int squareY = GetSquareStart(y);

	// check the Square
	for (int i = squareX; i < squareX + 3; ++i)
	{
		for (int j = squareY; j < squareY + 3; j++)
		{
			if (table[i][j] != 0) // it is not the current cell since is not zero
			{
				possibilityies.remove(table[i][j]);
			}
		}
	}

	//check the horizental line
	for (int i = 0; i < 9; ++i)
	{
		if (table[x][i] != 0)
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