#include "Colors.h"
#include <SFML/Graphics.hpp>

const sf::Color DARK_GREY = sf::Color(18, 27, 45);
const sf::Color GREEN = sf::Color(204, 255, 51);
const sf::Color RED = sf::Color(255, 179, 193);
const sf::Color BLUE = sf::Color(144, 224, 239);
const sf::Color YELLOW = sf::Color(255, 255, 63);
const sf::Color ORANGE = sf::Color(255, 120, 90);
const sf::Color PURPLE = sf::Color(255, 175, 204);
const sf::Color CYAN = sf::Color(196, 255, 249);


std::vector<sf::Color> GetCellColors()
{
	std::vector<sf::Color> colors;
	colors.push_back(DARK_GREY);
	colors.push_back(GREEN);
	colors.push_back(RED);
	colors.push_back(BLUE);
	colors.push_back(YELLOW);
	colors.push_back(ORANGE);
	colors.push_back(PURPLE);
	colors.push_back(CYAN);
	return colors;
}
