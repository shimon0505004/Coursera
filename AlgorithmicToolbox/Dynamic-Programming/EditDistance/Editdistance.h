#ifndef EDIT_DISTANCE
#define EDIT_DISTANCE
#include <string>
#include <vector>

namespace EditDistance
{
	int editDistance(std::string string1, std::string string2);
};

int EditDistance::editDistance(std::string string1
	, std::string string2)
{
	typedef std::vector<int> Row;
	typedef std::vector<Row> Matrix;

	Matrix editDistMat(string1.length() + 1, Row(string2.length() + 1));
	for (int rowIndex = 0
		; rowIndex <= string1.length()
		; rowIndex++)
	{
		for (int colIndex = 0
			; colIndex <= string2.length()
			; colIndex++)
		{
			editDistMat[rowIndex][colIndex] = 0;
		}

	}


	for (int rowIndex = 1
		; rowIndex <= string1.length()
		; rowIndex++)
	{
		editDistMat[rowIndex][0] = rowIndex;
	}

	for (int colIndex = 1
		; colIndex <= string2.length()
		; colIndex++)
	{
		editDistMat[0][colIndex] = colIndex;
	}

	for (int rowIndex = 1
		; rowIndex <= string1.length()
		; rowIndex++)
	{
		for (int colIndex = 1
			; colIndex <= string2.length()
			; colIndex++)
		{
			int minDistance = editDistMat[rowIndex - 1][colIndex - 1];
			if (string1.at(rowIndex - 1)
				!= string2.at(colIndex - 1))
			{
				minDistance += 1;
			}

			int minDistance1 = editDistMat[rowIndex - 1][colIndex] + 1;
			if (minDistance1 < minDistance)
				minDistance = minDistance1;

			int minDistance2 = editDistMat[rowIndex][colIndex - 1] + 1;
			if (minDistance2 < minDistance)
				minDistance = minDistance2;

			editDistMat[rowIndex][colIndex] = minDistance;
		}

	}

	return editDistMat[string1.length()][string2.length()];
}
#endif EDIT_DISTANCE
