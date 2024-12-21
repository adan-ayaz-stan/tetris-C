#include "Block.h"

Block::Block()
{
	cellSize = 30;
	rotationState = 0;
	colors = GetCellColors();

	rowOffset = 0;
	columnOffset = 0;
}

void Block::Draw(sf::RenderWindow& window, float startX, float startY)
{
	std::vector<Position> tiles = GetCellPositions();
	for (Position p : tiles)
	{
		sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));
		cell.setPosition(startX + p.column * cellSize + 1, startY + p.row * cellSize + 1);
		cell.setFillColor(colors[id]);
		window.draw(cell);
	}
}

void Block::Move(int rows, int columns)
{
	rowOffset += rows;
	columnOffset += columns;
}

void Block::Rotate()
{
	this->rotationState++;
	if (this->rotationState == (int)cells.size()) this->rotationState = 0;
}

void Block::UndoRotation()
{
	this->rotationState--;
	if (this->rotationState == -1) {
		this->rotationState = (int)cells.size() - 1;
	}
}

std::vector<Position> Block::GetCellPositions() {
	std::vector<Position> tiles = cells[rotationState];
	std::vector<Position> newTiles;

	for (Position p : tiles)
	{
		newTiles.push_back(Position(p.row + rowOffset, p.column + columnOffset));
	}

	return newTiles;
}
