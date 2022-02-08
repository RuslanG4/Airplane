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
	void processMouse(sf::Event t_event);
	void processMouseSecond(sf::Event t_event);
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
	sf::Sprite m_bigPlane;
	sf::Texture m_bigPlaneTexture;
	sf::Vector2f m_bigPlaneLocation;
	void setUpSprites();

	sf::Vector2f m_bigVelocity{ 1.f,-1.f };
	sf::Vector2f m_smallVelocity{ -2.0f,2.0f };
	float m_smallPlaneHeading = 225.0f;
	float m_bigPlaneHeading = 45.0f;
	void MovePlanes();

	void checkBoundary(sf::Vector2f& t_location);

	sf::Vector2f releaseClick{ 0, 0 };
	sf::Vector2f click{ 0, 0 };
};

#endif // !GAME_HPP

