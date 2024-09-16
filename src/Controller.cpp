#include "Controller.h"

void Controller::runGame()
{
	//the input file
	std::ifstream mapFile("Board.txt");
	std::vector<std::string> map;
	int x, y; //the width and the height that we get from the user
	int gameX = 0, gameY = 0; //the window width and height after checking
	
	//if there is no input file
	if (!mapFile.is_open())
	{
		//std::cerr << "Failed to open map file!" << std::endl;
		std::cout << "please insert the width then the height" << std::endl;
		std::cin >> x >> y;
	}
	else
	{
		readTheMap(map, mapFile);
		x = map[0].size();
		y = map.size();
		m_boardFileExist = true;
	}

	
	checkSizes(x, y, gameX, gameY);
	m_window = new sf::RenderWindow(sf::VideoMode((gameX+1)* iconSize, gameY* iconSize), "pacman level editor", sf::Style::Close);
	Board board(m_window, x, y);

	if (m_boardFileExist)
	{
		board.drawFromFile(map);
	}


	while (m_window->isOpen())
	{
		m_window->clear();
		sf::Event event;

		while (m_window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window->close();
				break;
			}
		}
		
		
		board.boardUpdate(m_window);
		board.drawObjects(m_window);

		//if the user pressed clear
		if (board.getClearPressed())
		{
			//to draw the clear message
			m_window->clear();
			font.loadFromFile("arial.ttf");
			text.setFont(font);
			text.setString("please insert the width then the height");
			text.setPosition(200, 200);
			text.setCharacterSize(16);
			text.setStyle(sf::Text::Bold);
			m_window->draw(text);
			m_window->display();

			std::cout << "please insert the width then the height" << std::endl;

			//to get the new sizes after the clear
			std::cin >> x >> y;
			checkSizes(x, y, gameX, gameY);
			m_window->close();
			//to draw a new window with the new sizes
			m_window = new sf::RenderWindow(sf::VideoMode((gameX + 1) * iconSize, gameY * iconSize), "SFML project", sf::Style::Close);
			 board = Board(m_window, x, y);
		}
		m_window->display();
	}
}

void Controller::checkSizes(int x, int y, int& gameX, int& gameY)
{
	if (x >= 10 && y >= 10)
	{
		gameX = x;
		gameY = y;
	}
	else if (x < 10 && y < 10)
	{
		gameX = 10;
		gameY = 10;
	}

	else if (x < 10)
	{
		gameX = 10;
		gameY = y;
	}
	else if (y < 10)
	{
		gameX = x;
		gameY = 10;
	}
}

//read the map from a file
void Controller::readTheMap(std::vector<std::string>& map, std::ifstream& mapFile)
{
	for (auto line = std::string(); std::getline(mapFile, line);)
	{
		map.push_back(line);
	}
}


