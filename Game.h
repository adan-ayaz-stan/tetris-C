#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <ctime>
#include "Block.h"
#include "Grid.h"

class Game
{
private:
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoMode;

	sf::RectangleShape container;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	std::vector<Block> blocks;

	Block currentBlock;
	Block nextBlock;


	// Init functions
	void initVars();
	void initWindow();
	

	bool IsBlockOutside();
	void RotateBlock();

	void Reset();
public:
	// Constructors and deconstructors
	Grid grid;
	Game();
	virtual ~Game();

	int score;
	// Functions and everything goes here
	const bool isWindowOpen() const;

	bool isGameOver;

	//
	Block GetRandomBlock();
	std::vector<Block> GetAllBlocks();

	// movement
	void MoveBlockLeft();
	void MoveBlockRight();
	void MoveBlockDown();

	void LockBlock();
	bool BlockFits();

	//
	void pollEvents();

	void update();

	void render();
	void renderTextDisplayContainer();
	void renderScoreDisplayContainer();
};