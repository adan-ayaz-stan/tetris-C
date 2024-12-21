#include <iostream>
#include <ctime>
#include <chrono>
#include <random>
#include "Game.h"
#include "Grid.h"
#include "Blocks.cpp"

void Game::initVars()
{
	this->window = nullptr;
	this->score = 0;
	this->blocks = GetAllBlocks();
	this->currentBlock = GetRandomBlock();
	this->nextBlock = GetRandomBlock();
	this->isGameOver = false;
}

void Game::initWindow()
{
	this->videoMode.height = 720;
	this->videoMode.width = 1280;
	this->window = new sf::RenderWindow(this->videoMode, "Spitfire's Tetris", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);


	// Load the texture only once
	if (!backgroundTexture.loadFromFile("Images/background.jpg")) {
		std::cerr << "Error: Could not load background image!" << std::endl;
		return;
	}

	// Set the sprite and scale it
	backgroundSprite.setTexture(backgroundTexture);
	sf::Vector2u textureSize = backgroundTexture.getSize();
	backgroundSprite.setScale(
		float(this->window->getSize().x) / textureSize.x,
		float(this->window->getSize().y) / textureSize.y
	);
}

const bool Game::isWindowOpen() const
{
	return this->window->isOpen();
}

Block Game::GetRandomBlock()
{
	if (this->blocks.empty()) {
		this->blocks = GetAllBlocks();
	}
	int randomIndex = rand() % this->blocks.size();
	Block block = blocks[randomIndex];
	this->blocks.erase(blocks.begin() + randomIndex);
	return block;
}

std::vector<Block> Game::GetAllBlocks() {
	return { LBlock(), TBlock(), JBlock(), ZBlock(), OBlock(), SBlock(), IBlock() };
}

void Game::MoveBlockLeft()
{
	if (!this->isGameOver) {
		this->currentBlock.Move(0, -1);
		if (IsBlockOutside() || BlockFits() == false) {
			this->currentBlock.Move(0, 1);
		}
	}
}

void Game::MoveBlockRight()
{
	if (!this->isGameOver) {
		this->currentBlock.Move(0, 1);
		if (IsBlockOutside() || BlockFits() == false) {
			this->currentBlock.Move(0, -1);
		}
	}
}

void Game::MoveBlockDown()
{
	if (!this->isGameOver) {
		this->currentBlock.Move(1, 0);
		if (IsBlockOutside() || BlockFits() == false) {
			this->currentBlock.Move(-1, 0);
			this->LockBlock();
		}
	}
}

void Game::LockBlock()
{
	std::vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item : tiles) {
		this->grid.grid[item.row][item.column] = this->currentBlock.id;
	}

	this->currentBlock = this->nextBlock;
	if (BlockFits() == false) {
		this->isGameOver = true;
	}
	this->nextBlock = GetRandomBlock();

	int rowsCompleted = this->grid.ClearFullRows();
	this->score += rowsCompleted;
}

bool Game::BlockFits()
{
	std::vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item : tiles) {
		if (this->grid.IsCellEmpty(item.row, item.column) == false) {
			return false;
		}
	}
	return true;
}

bool Game::IsBlockOutside()
{
	std::vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position tile : tiles) {
		if (this->grid.IsCellOutOfBounds(tile.row, tile.column)) {
			return true;
		}
	}
	
	return false;
}

void Game::RotateBlock()
{
	if (!this->isGameOver) {
		this->currentBlock.Rotate();
		if (IsBlockOutside() || BlockFits() == false) {
			this->currentBlock.UndoRotation();
		}
	}
}

void Game::Reset()
{
	this->isGameOver = false;
	this->score = 0;
	grid.Initialize();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev)) {
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;

		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape) this->window->close();

			if (ev.key.code == sf::Keyboard::Up) this->RotateBlock();

			if (ev.key.code == sf::Keyboard::Down) this->MoveBlockDown();
			if (ev.key.code == sf::Keyboard::Left) this->MoveBlockLeft();
			if (ev.key.code == sf::Keyboard::Right) this->MoveBlockRight();

			if (this->isGameOver && ev.key.code == sf::Keyboard::R) {
				this->Reset();
			}

			break;

		default:
			break;
		}
	}
}

void Game::update()
{
    static auto lastMoveTime = std::chrono::steady_clock::now();

    this->pollEvents();

    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastMoveTime).count();

    if (elapsedTime >= 500) {
        this->MoveBlockDown();
        lastMoveTime = currentTime;
    }
}

void Game::render()
{
	//
	this->window->clear(sf::Color(18, 27, 45));
	this->window->draw(backgroundSprite);

	// Rendering here
	this->renderTextDisplayContainer();
	this->renderScoreDisplayContainer();
	this->grid.Draw(*this->window);
	this->currentBlock.Draw(*this->window, this->grid.GetStartPosition(*this->window).first, this->grid.GetStartPosition(*this->window).second);

	//
	this->window->display();
}

void Game::renderTextDisplayContainer()
{
	sf::Font font;
	if (!font.loadFromFile("Fonts/Juvanze-ovw9A.otf")) {
		std::cerr << "Error loading font\n";
		return;
	}
	sf::Font fontText;
	if (!fontText.loadFromFile("Fonts/Raleway-VariableFont_wght.ttf")) {
		std::cerr << "Error loading font\n";
		return;
	}

	sf::Text title;
	title.setFont(font);
	title.setString("TETRIS MANIA");
	title.setCharacterSize(64);
	title.setFillColor(sf::Color::White);
	title.setPosition(20, 50);

	sf::Text subtitle;
	subtitle.setFont(font);
	subtitle.setString("BY Spitfire Kasnoviz ( Adan Ayaz )");
	subtitle.setCharacterSize(24);
	subtitle.setFillColor(sf::Color(200, 200, 200));
	subtitle.setPosition(20, 130);

	sf::Text githubText;
	githubText.setFont(fontText);
	githubText.setString("See my Github (49 Repositories)\nhttps://github.com/adan-ayaz-stan");
	githubText.setCharacterSize(18);
	githubText.setStyle(sf::Text::Bold);
	githubText.setFillColor(sf::Color::White);
	githubText.setPosition(20, 200);

	sf::Text details;
	details.setFont(fontText);
	details.setString("Reg ID: 241447\n\nSubject: Programming Fundamentals\n\nClass: BSAI-F-24-B\n\nInstructor: Dr. Tahir Akram");
	details.setCharacterSize(18);
	details.setStyle(sf::Text::Bold);
	details.setFillColor(sf::Color::White);
	details.setPosition(20, 350);

	this->window->draw(title);
	this->window->draw(subtitle);
	this->window->draw(githubText);
	this->window->draw(details);
}

void Game::renderScoreDisplayContainer()
{
	std::pair<float, float> gridEnd = this->grid.GetEndPosition(*this->window);

	sf::RectangleShape scoreContainer;
	scoreContainer.setSize(sf::Vector2f(400, 50));
	scoreContainer.setFillColor(sf::Color::Cyan);
	scoreContainer.setOutlineColor(sf::Color::Black);
	scoreContainer.setOutlineThickness(2);
	scoreContainer.setPosition(gridEnd.first + 50, 60);

	sf::Font font;
	if (!font.loadFromFile("Fonts/Raleway-VariableFont_wght.ttf")) {
		std::cerr << "Error loading font\n";
		return;
	}

	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setString("Score: " + std::to_string(this->score));
	scoreText.setCharacterSize(24);
	scoreText.setStyle(sf::Text::Bold);
	scoreText.setFillColor(sf::Color::Black);
	scoreText.setPosition(gridEnd.first + 70, 70);

	sf::Text instructionsText;
	instructionsText.setFont(font);
	instructionsText.setString("Press R to reset the game when it's over.\nHave fun!");
	instructionsText.setCharacterSize(18);
	instructionsText.setStyle(sf::Text::Bold);
	instructionsText.setFillColor(sf::Color(150,150,150));
	instructionsText.setPosition(gridEnd.first + 50, 120);

	this->window->draw(scoreContainer);
	this->window->draw(scoreText);
	this->window->draw(instructionsText);
}

Game::Game()
{
	this->initVars();
	this->initWindow();
}

Game::~Game()
{
	delete this->window;
}
