#pragma once
#include "Toolbar.h" 
#include <iostream>

class Board
{
private:
	bool m_pacmanUsed; //because we only ca put one pacman

	Toolbar m_toolbar; 

	//the icons textures
	sf::Texture m_whiteTexture;
	sf::Texture m_wallTexture;
	sf::Texture m_doorTexture;
	sf::Texture m_keyTexture;
	sf::Texture m_cakeTexture;
	sf::Texture m_demonTexture;
	sf::Texture m_pacmanTexture;
	sf::Texture m_giftTexture;

	
	std::vector<sf::Sprite> m_tiles; //vector for white tiles
	std::vector<sf::Sprite> m_wantedIcons; //contains the icons that the user clicks to draw
	sf::Vector2f m_pacmanPosition; //the position of the pacman
	std::vector<sf::Vector2f> m_whitesPositions;

	sf::Texture m_transparentTexture;
	sf::Sprite m_transparentSprite;//the sprite that drawn when the mouse is on a tile

public:

	Board() = default;
	Board( sf::RenderWindow* window, int, int);

	bool getClearPressed() const;
	bool getSavePressed() const;
	void drawObjects(sf::RenderWindow* m_window); //to draw the objects on the window
	void boardUpdate(sf::RenderWindow* m_window); //the updates that happen on the board like clicking the mouse
	void eraseFuncion(sf::Sprite &wantedSprite, std::vector<sf::Sprite> &wantedIcons , std::vector<sf::Vector2f> &whitesPositions, size_t i);
	void puttingIcons(sf::Sprite& wantedSprite, std::vector<sf::Sprite>& wantedIcons,
											std::vector<sf::Vector2f>& whitesPositions, sf::Vector2f &pacmanPosition, size_t i);//to put objects on the window
	void setTransparent(sf::Sprite &transparentSprite, sf::RenderWindow *m_window);//to draw half transparent sprite when the mouse is on a white tile
	void drawFromFile(std::vector<std::string> map);//when there is an input file then draw it
	void drawToFile(std::vector<std::string>& map); //to save the map on output file
};