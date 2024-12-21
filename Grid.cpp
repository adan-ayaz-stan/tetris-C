#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Game.h"
#include "Colors.h"
#include "Blocks.cpp"

Grid::Grid()
{
	numRows = 20;
	numCols = 10;
	cellSize = 30;
	Initialize();

	colors = GetCellColors();
}

void Grid::Initialize()
{
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			grid[i][j] = 0;
		}
	}
}

std::pair<float, float> Grid::GetStartPosition(sf::RenderWindow& window)
{
    // Find the center of the window
    sf::Vector2u windowSize = window.getSize();
    float centerX = windowSize.x / 2.0f;
    float centerY = windowSize.y / 2.0f;

    // Calculate the top left position of the grid
    float gridWidth = numCols * cellSize;
    float gridHeight = numRows * cellSize;
    float gridX = centerX - (gridWidth / 2.0f);
    float gridY = centerY - (gridHeight / 2.0f);

    return std::make_pair(gridX, gridY);
}

std::pair<float, float> Grid::GetEndPosition(sf::RenderWindow& window)
{
    std::pair<float, float> gridStart = this->GetStartPosition(window);
    float endX = gridStart.first + numCols * cellSize;
    float endY = gridStart.second + numRows * cellSize;
    return std::make_pair(endX, endY);
}

bool Grid::IsCellOutOfBounds(int row, int column)
{
    if (row >= 0 && row < this->numRows && column >= 0 && column < this->numCols) return false;
    return true;
}

bool Grid::IsCellEmpty(int row, int column)
{
    if (this->grid[row][column] == 0) return true;
    return false;
}

int Grid::ClearFullRows()
{
    int completed = 0;
    
    for (int row = this->numRows - 1; row >= 0; row--) {
        if (IsRowFull(row)) {
            ClearRow(row);
            completed++;
        }
        else if (completed > 0) {
            MoveRowDown(row, completed);
        }
    }

    return completed;
}

bool Grid::IsRowFull(int row)
{
    for (int column = 0; column < this->numCols; column++) {
        if (this->grid[row][column] == 0) {
            return false;
        }
    }
    return true;
}

void Grid::ClearRow(int row)
{
    for (int column = 0; column < this->numCols; column++) {
        grid[row][column] = 0;
    }
}

void Grid::MoveRowDown(int row, int numRows)
{
    for (int column = 0; column < this->numCols; column++) {
        grid[row + numRows][column] = grid[row][column];
        grid[row][column] = 0;
    }
}

void Grid::Draw(sf::RenderWindow& window)
{
    // Find the center of the window
    sf::Vector2u windowSize = window.getSize();
    float centerX = windowSize.x / 2.0f;
    float centerY = windowSize.y / 2.0f;

    // Calculate the top left position of the grid
    float gridWidth = numCols * cellSize;
    float gridHeight = numRows * cellSize;
    float gridX = centerX - (gridWidth / 2.0f);
    float gridY = centerY - (gridHeight / 2.0f);

    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(gridX + j * cellSize, gridY + i * cellSize);
            cell.setOutlineThickness(1);
            cell.setOutlineColor(sf::Color(100,100,100));
            cell.setFillColor(colors[grid[i][j]]);
            window.draw(cell);
        }
    }
}
