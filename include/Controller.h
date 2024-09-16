#pragma once

#include "Board.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Toolbar.h"

class Controller
{
private:
	sf::RenderWindow* m_window;
	sf::Text text;
	sf::Font font;
	bool m_boardFileExist = false;
public:
	Controller() = default;
	void runGame();
	//void getWindowSize(sf::RenderWindow* m_window, Board& board);
	void checkSizes(int x, int y, int& gameX, int& gameY);
	void readTheMap(std::vector<std::string>& map, std::ifstream& mapFile);
};