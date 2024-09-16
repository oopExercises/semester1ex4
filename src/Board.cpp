#include "Board.h"
#include <fstream>

Board::Board(sf::RenderWindow* window, int x, int y)
{
	m_pacmanUsed = false;
	m_toolbar = Toolbar(window->getSize().x - iconSize, window->getSize().y );

	m_whiteTexture.loadFromFile("white.png");
	sf::Texture transparent;

	//load the images
	transparent.loadFromFile("wall.png");//the virtual sprite is wall
	m_wallTexture.loadFromFile("wall.png");
	m_giftTexture.loadFromFile("gift.png");
	m_demonTexture.loadFromFile("demon.png");
	m_cakeTexture.loadFromFile("cake.png");
	m_keyTexture.loadFromFile("key.png");
	m_doorTexture.loadFromFile("door.png");
	m_pacmanTexture.loadFromFile("pacman.png");

	m_transparentSprite.setTexture(transparent);
	m_transparentSprite.setColor(sf::Color(128, 128, 128, 128));//to make it half transparent

	for (size_t i = 0; i < x * iconSize; i += iconSize)
	{
		for (size_t j = 0; j < y * iconSize; j += iconSize)
		{
			sf::Sprite whiteSprite;
			whiteSprite.setTexture(m_whiteTexture);
			whiteSprite.setPosition((float)i, (float)j);
			m_tiles.push_back(whiteSprite);
			m_whitesPositions.push_back(whiteSprite.getPosition());
		}
	}
}

bool Board::getClearPressed() const
{
	return m_toolbar.getClearPressed();
}

bool Board::getSavePressed() const
{
	return m_toolbar.getSavePressed();
}


void Board::drawObjects(sf::RenderWindow* m_window)
{
	//draw the white tiles
	for (int i = 0; i < m_tiles.size(); i++)
	{
			m_window->draw(m_tiles[i]);
	}
	//draw the toolbar
	for (int i = 0; i < numOfIcons; i++)
	{
		m_window->draw(m_toolbar.drawToolbar(i));
	}
	//to draw the objects that the user put or the objects that were in the input file 
	for (int i = 0; i < m_wantedIcons.size(); i++)
	{
		m_window->draw(m_wantedIcons[i]);
	}
	
	m_window->draw(m_transparentSprite);
}

void Board::boardUpdate(sf::RenderWindow* m_window)
{
	setTransparent(m_transparentSprite, m_window);

	//when the user clickes on icon
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		for (size_t i = 0; i < m_tiles.size(); i++)
		{
			if (m_tiles[i].getGlobalBounds().contains(sf::Vector2f((float)sf::Mouse::getPosition(*m_window).x, (float)sf::Mouse::getPosition(*m_window).y)))
			{
				sf::Sprite wantedSprite;

				//if the clicked icon is erase
				if (m_toolbar.getTouchedIcon() == ERASE)
				{
					eraseFuncion(wantedSprite, m_wantedIcons, m_whitesPositions, i);
				}
				//if the clicked icon is not erase
				else
				{
					puttingIcons(wantedSprite, m_wantedIcons, m_whitesPositions, m_pacmanPosition, i);
				}
			}
		}

	m_toolbar.setToolbar();
	m_toolbar.touchIcon(*m_window);
}


void Board::eraseFuncion(sf::Sprite& wantedSprite, std::vector<sf::Sprite> &wantedIcons, std::vector<sf::Vector2f> &whitesPositions, size_t i)
{
	//if we try to erase a white board, dont do anything
	for(size_t j = 0; j < whitesPositions.size(); j++)
	{ 
		if (m_tiles[i].getPosition() == whitesPositions[j])
			return;
	}
	wantedSprite.setPosition(m_tiles[i].getPosition());
	wantedSprite.setTexture(m_toolbar.getIconTexture(m_toolbar.getTouchedIcon()));//set the texture to white
	//wantedIcons.push_back(wantedSprite);
	whitesPositions.push_back(wantedSprite.getPosition());
	for (size_t index = 0; index < wantedIcons.size(); index++)
	{
		if(m_tiles[i].getPosition() == wantedIcons[index].getPosition())
		wantedIcons.erase(wantedIcons.begin() + index);
	}
	//if we erase the pacman, then we change m_pacmanUsed to false 
	if (wantedSprite.getPosition() == m_pacmanPosition)
	{
		m_pacmanUsed = false;
		m_tiles[i].setTexture(m_whiteTexture);
	}
}

void Board::puttingIcons(sf::Sprite& wantedSprite, std::vector<sf::Sprite>& wantedIcons, std::vector<sf::Vector2f>& whitesPositions, sf::Vector2f& pacmanPosition, size_t i)
{
	for (auto j = 0; j < whitesPositions.size(); j++)
	{
		if (m_tiles[i].getPosition() == whitesPositions[j])
		{
			//check if the pacman is already used
			if (m_toolbar.getTouchedIcon() == PACMAN && !m_pacmanUsed)
			{
				m_pacmanUsed = true;
				wantedSprite.setPosition(m_tiles[i].getPosition());
				wantedSprite.setTexture(m_toolbar.getIconTexture(m_toolbar.getTouchedIcon()));
				wantedIcons.push_back(wantedSprite);
				pacmanPosition = wantedSprite.getPosition();
				whitesPositions.erase(whitesPositions.begin() + j);
			}
			else if (m_toolbar.getTouchedIcon() != PACMAN)
			{
				wantedSprite.setPosition(m_tiles[i].getPosition());
				wantedSprite.setTexture(m_toolbar.getIconTexture(m_toolbar.getTouchedIcon()));
				wantedIcons.push_back(wantedSprite);
				whitesPositions.erase(whitesPositions.begin() + j);
			}
			break;
		}
	}
}

void Board::setTransparent(sf::Sprite &transparentSprite, sf::RenderWindow* m_window)
{
	transparentSprite.setTexture(m_toolbar.getIconTexture(m_toolbar.getTouchedIcon()));
	transparentSprite.setPosition(sf::Vector2f((float)sf::Mouse::getPosition(*m_window).x, (float)sf::Mouse::getPosition(*m_window).y));


	for (size_t i = 0; i < m_tiles.size(); i++)
	{
		if (m_tiles[i].getGlobalBounds().contains(sf::Vector2f((float)sf::Mouse::getPosition(*m_window).x, (float)sf::Mouse::getPosition(*m_window).y)))
		{
			transparentSprite.setPosition(m_tiles[i].getPosition());
		}
	}
}

void Board::drawFromFile( std::vector<std::string> map)
{
	sf::Sprite wantedSprite;
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[0].size(); j++)
		{
			wantedSprite.setPosition(j * iconSize, i * iconSize);

			if (map[i][j] == '#')
			{
				wantedSprite.setTexture(m_wallTexture);
			}
			else if (map[i][j] == '$')
			{
				wantedSprite.setTexture(m_giftTexture);
			}
			else if (map[i][j] == '*')
			{
				wantedSprite.setTexture(m_cakeTexture);
			}
			else if (map[i][j] == '&')
			{
				wantedSprite.setTexture(m_demonTexture);
			}
			else if (map[i][j] == '%')
			{
				wantedSprite.setTexture(m_keyTexture);
			}
			else if (map[i][j] == 'D')
			{
				wantedSprite.setTexture(m_doorTexture);
			}
			else if (map[i][j] == 'a')
			{
				m_pacmanUsed = true;
				wantedSprite.setTexture(m_pacmanTexture);
			}

			for (size_t index = 0; index < m_whitesPositions.size(); index++)
			{
				if (m_whitesPositions[index] == wantedSprite.getPosition())
				{
					m_whitesPositions.erase(m_whitesPositions.begin() + index);
					break;
				}
			}
			 if (map[i][j] == ' ')
			{
				wantedSprite.setTexture(m_whiteTexture);
				m_whitesPositions.push_back(wantedSprite.getPosition());
			}
			 else
				 m_wantedIcons.push_back(wantedSprite);
		}
		
	}
}

//draw the map to the output file
void Board::drawToFile(std::vector<std::string>& map)
{
	int x = 0;
	int y = 0;

	for (size_t i = 0; i < m_whitesPositions.size(); i++)
	{
		x = m_whitesPositions[i].x / iconSize;
		y = m_whitesPositions[i].y / iconSize;

		map[y][x] = ' ';
	}
	for (size_t i = 0; i < m_wantedIcons.size(); i++)
	{
		x = m_wantedIcons[i].getPosition().x / iconSize;
		y = m_wantedIcons[i].getPosition().y / iconSize;

		if (m_wantedIcons[i].getTexture() == &m_wallTexture)
		{
			map[y][x] = '#';
		}
		else if (m_wantedIcons[i].getTexture() == &m_doorTexture)
		{
			map[y][x] = 'D';
		}
		else if (m_wantedIcons[i].getTexture() == &m_cakeTexture)
		{
			map[y][x] = '*';
		}
		else if (m_wantedIcons[i].getTexture() == &m_demonTexture)
		{
			map[y][x] = '&';
		}
		else if (m_wantedIcons[i].getTexture() == &m_keyTexture)
		{
			map[y][x] = '%';
		}
		else if (m_wantedIcons[i].getTexture() == &m_giftTexture)
		{
			map[y][x] = '$';
		}
		else if (m_wantedIcons[i].getTexture() == &m_pacmanTexture)
		{
			map[y][x] = 'a';
		}
	}

	std::ofstream output("Board.txt");
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[0].size(); j++)
			output << map[i][j];
		output << std::endl;
	}

	exit (EXIT_SUCCESS);
}



