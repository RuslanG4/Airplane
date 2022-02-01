/// <summary>
/// Ruslan Gavrilov
/// 26-01-2022
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setUpSprites(); 
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		if (sf::Event::MouseButtonPressed == newEvent.type)
		{
			processMouse(newEvent);
		}
		if (sf::Event::MouseButtonReleased == newEvent.type)
		{
			processMouseSecond(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

void Game::processMouse(sf::Event t_event)
{
	click.x = t_event.mouseButton.x;
	click.y = t_event.mouseButton.y;	
}

void Game::processMouseSecond(sf::Event t_event)
{
	releaseClick.x = t_event.mouseButton.x;
	releaseClick.y = t_event.mouseButton.y;
	sf::Vector2f velocity = click - releaseClick;
	float headingRadians = std::atan2(velocity.y, velocity.x);
	float headingDegree = 180.0f * headingRadians / static_cast<float>(3.14);
	headingDegree += 90.0f;

	if (sf::Mouse::Right == t_event.mouseButton.button)
	{
		m_smallVelocity = velocity / 50.0f;
		m_smallPlaneHeading = headingDegree;
		m_smallPlane.setRotation(headingDegree);
	}

}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	MovePlanes();
	checkBoundary(m_smallPlaneLocation);
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_smallPlane);
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("SFML Game");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(40.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(80U);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);

}

void Game::setUpSprites()
{
	sf::IntRect smallPlaneRect{ 362,115,87,69 };
	sf::Vector2f smallPlaneStart{ 100.0f, 100.0f };

	if (!m_smallPlaneTexture.loadFromFile("ASSETS//IMAGES//planes.png"))
	{
		std::cout << "Error loading small plane" << std::endl;
	}
	m_smallPlane.setTexture(m_smallPlaneTexture);
	m_smallPlane.setTextureRect(smallPlaneRect);
	m_smallPlane.setPosition(smallPlaneStart);
	m_smallPlane.setOrigin(smallPlaneRect.width / 2.0f, smallPlaneRect.height / 2.0f);
	m_smallPlane.setRotation(m_smallPlaneHeading);
	m_smallPlaneLocation = smallPlaneStart;
}

void Game::MovePlanes()
{
	m_smallPlaneLocation += m_smallVelocity;
	m_smallPlane.setPosition(m_smallPlaneLocation);
}

void Game::checkBoundary(sf::Vector2f& t_location)
{
	
	if (t_location.x < 0.f)
	{
		t_location.x = 0.f;
	}
	if (t_location.x > 800.f)
	{
		t_location.x = 800.f;
	}
	if (t_location.y < 0.f)
	{
		t_location.y = 0.f;
	}
	if (t_location.y > 600.0f)
	{
		t_location.y = 600.f;
	}
}
