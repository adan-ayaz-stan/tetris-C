#pragma once
#include <stdlib.h>

class Grid
{
public:
	Grid();
	int grid[20][10];

	void Initialize();
	
	std::pair<float, float> GetStartPosition(sf::RenderWindow& window);
	std::pair<float, float> GetEndPosition(sf::RenderWindow& window);
	
	void Draw(sf::RenderWindow& window); // Added parameter for target window
	bool IsCellOutOfBounds(int row, int column);
	bool IsCellEmpty(int row, int column);

	int ClearFullRows();

private:
	int numRows;
	int numCols;
	int cellSize;
	bool IsRowFull(int row);
	void ClearRow(int row);
	void MoveRowDown(int row, int numRows);

	std::vector<sf::Color> colors;
};
