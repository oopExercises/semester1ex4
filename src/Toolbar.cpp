#include "Toolbar.h"
#include <iostream>

Toolbar::Toolbar(int x, int y)
{
	m_clearPressed = false;
	m_savePressed = false;
	m_mouseReleased = true;

	//to put the toolbar on the right of the window
	for (size_t i = 0; i < numOfIcons; i++)
	{
		m_positions[i] = sf::Vector2f(x, i*(y/numOfIcons));
	}
}

void Toolbar::setToolbar()
{
	m_textures[PACMAN].loadFromFile("pacman.png");
	m_textures[DEMON].loadFromFile("demon.png");
	m_textures[CAKE].loadFromFile("cake.png");
	m_textures[DOOR].loadFromFile("door.png");
	m_textures[GIFT].loadFromFile("gift.png");
	m_textures[KEY].loadFromFile("key.png");
	m_textures[WALL].loadFromFile("wall.png");
	m_textures[SAVE].loadFromFile("save.png");
	m_textures[ERASE].loadFromFile("erase.png");
	m_textures[CLEAR].loadFromFile("clear.png");
	m_textures[WHITE].loadFromFile("white.png");

	for (size_t i = 0; i < numOfIcons; i++)
	{
		m_sprites[i].setTexture(m_textures[i]);
		m_sprites[i].setPosition(m_positions[i]);
	}
}

sf::Sprite Toolbar::drawToolbar( int index)
{
	return m_sprites[index];
}

//function that gets a vector and returns the name of the clicked icon
Toolbar_t Toolbar::getIconName(sf::Vector2f vector)const
{
	for (size_t i = 0; i <= numOfIcons; i++)
	{
		if (m_positions[i] == vector)
			return (Toolbar_t)i;
	}
	return (Toolbar_t)0;
}

//function that returns the texture of the clicked icon
sf::Texture& Toolbar::getIconTexture(Toolbar_t iconName)
{
	if (iconName == ERASE)
		return m_textures[numOfIcons]; //to return the white texture
	return m_textures[iconName];
}

//function that updates the touched icon
void Toolbar::touchIcon(sf::RenderWindow& window)
{
	sf::Sprite clickedIcon;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_mouseReleased)
	{
		sf::Texture texture;
		
		for (size_t i = 0; i < numOfIcons; i++)
		{
			if (m_sprites[i].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)))
			{
				texture = m_textures[i];
				
				m_touchedIconTexture = (Toolbar_t)i;
				if (m_touchedIconTexture == CLEAR)
				{
					m_clearPressed = true;
				}
				else if (m_touchedIconTexture == SAVE)
				{
					m_savePressed = true;
					exit(EXIT_SUCCESS);
				}
			}
		}
		m_mouseReleased = false;
	}
	//to check if the mouse button is released to let the user to choose another icon
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		m_mouseReleased = true;
}

Toolbar_t Toolbar::getTouchedIcon()const
{
	return m_touchedIconTexture;
}

bool Toolbar::getClearPressed()const
{
	return m_clearPressed;
}

bool Toolbar::getSavePressed()const
{
	return m_savePressed;
}
	
