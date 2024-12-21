#pragma once

#include <vector>
#include <map>
#include "Position.h"
#include "Colors.h"

class Block
{
public:
	Block();
	int id; 

	std::map<int, std::vector<Position>> cells;

	void Draw(sf::RenderWindow& window, float startX, float startY);
	void Move(int rows, int columns);
	void Rotate();
	void UndoRotation();
	std::vector<Position> GetCellPositions();
private:
	int cellSize;
	int rotationState;

	int rowOffset;
	int columnOffset;

	std::vector<sf::Color> colors;
};

