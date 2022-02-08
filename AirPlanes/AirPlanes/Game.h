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
	sf::Texture m_smallPlaneTexture;     //small plane
	sf::Vector2f m_smallPlaneLocation;

	sf::Sprite m_bigPlane;
	sf::Texture m_bigPlaneTexture;      //big plane
	sf::Vector2f m_bigPlaneLocation;

	sf::Sprite m_skySprite;
	sf::Texture m_skyTexture;        //sky
	void setUpSprites();      //draw our sprites

	sf::Vector2f m_bigVelocity{ 1.f,-1.f };       //which way going, flips sprites
	sf::Vector2f m_smallVelocity{ -2.0f,2.0f };

	float m_smallPlaneHeading = 225.0f;      //angle at heading
	float m_bigPlaneHeading = 45.0f;
	void MovePlanes();

	void checkBoundary(sf::Vector2f& t_location); //checks boundary to make sure they stay 

	void debugSprite(sf::Sprite& t_sprite); //debug mode

	float m_bigPlaneRadius = 52.0f;   // radius of bounding circle for big plane
	float m_smallPaneRadius = 44.0f; // bounding radius of small plane

	bool checkforCollision(sf::Vector2f t_locationOne, float t_radiusOne,sf::Vector2f t_locationTwo, float t_radiusTwo); //collision check
	float vector2fLenght(sf::Vector2f t_vector); //methos for vector length

	sf::Vector2f releaseClick{ 0, 0 }; //second click
	sf::Vector2f click{ 0, 0 };   //initial click

	bool m_debugGraphis{ true }; 
};

#endif // !GAME_HPP

