/// <summary>
/// Ruslan Gavrilov
/// 
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game


	sf::Sprite m_smallPlane;
	sf::Texture m_smallPlaneTexture;
	sf::Vector2f m_smallPlaneLocation;
	void setUpSprites();

	sf::Vector2f m_smallVelocity{ -2.0f,2.0f };
	float m_smallPlaneHeading = 225.0f;
	void MovePlanes();

	void checkBoundary(sf::Vector2f& t_location);
};

#endif // !GAME_HPP

