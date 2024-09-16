#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

enum Toolbar_t
{
	PACMAN , DEMON, WALL, CAKE, GIFT, KEY, DOOR, CLEAR, SAVE, ERASE, WHITE
};
const int numOfIcons = 10;
const int iconSize = 64;

class Toolbar
{
private:
	Toolbar_t m_touchedIconTexture = WALL;//the virtual icon is wall

	bool m_clearPressed;
	bool m_savePressed;
	bool m_mouseReleased;

	sf::Vector2f m_positions[numOfIcons]; //saves the positions of the icons
	sf::Texture m_textures[numOfIcons + 1];//the +1 is to save the white tile texture
	sf::Sprite m_sprites[numOfIcons]; //saves the sprites of the icons

public:
	Toolbar() = default;
	Toolbar(int, int);

	sf::Texture& getIconTexture(Toolbar_t iconName);
	sf::Sprite drawToolbar(int index);

	Toolbar_t getTouchedIcon()const;
	Toolbar_t getIconName(sf::Vector2f vector)const;

	void setToolbar();
	void touchIcon(sf::RenderWindow& window);
	bool getClearPressed() const;
	bool getSavePressed()const;
};

