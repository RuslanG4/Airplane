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
	if (sf::Keyboard::F1 == t_event.key.code)
	{
		m_debugGraphis = !m_debugGraphis;
	}
}
/// <summary>
/// gets initial click pos
/// </summary>
/// <param name="t_event"></param>
void Game::processMouse(sf::Event t_event)
{
	click.x = t_event.mouseButton.x;
	click.y = t_event.mouseButton.y;	
}
/// <summary>
/// gets second click pos , then determines the planes speed directiopn and rotates accordingly
/// </summary>
/// <param name="t_event"></param>
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
	if (sf::Mouse::Left == t_event.mouseButton.button)
	{
		m_bigVelocity = velocity / 50.0f;
		m_bigPlaneHeading = headingDegree;
		m_bigPlane.setRotation(headingDegree);
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
	checkBoundary(m_bigPlaneLocation);
	checkforCollision(m_bigPlaneLocation, m_bigPlaneRadius, m_smallPlaneLocation, m_smallPaneRadius);

}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_skySprite);
	m_window.draw(m_smallPlane);
	m_window.draw(m_bigPlane);
	if (m_debugGraphis)
	{
		debugSprite(m_bigPlane);
		debugSprite(m_smallPlane);
	}
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
/// <summary>
/// sets up all game sprites
/// </summary>
void Game::setUpSprites()
{
	sf::IntRect smallPlaneRect{ 362,115,87,69 };     //finds rect in sheet
	sf::Vector2f smallPlaneStart{ 100.0f, 100.0f };
	sf::IntRect bigPlaneRect{ 3,11,104,93 };
	sf::Vector2f bigPlaneStart{ 300.0f, 500.0f };

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
	if (!m_bigPlaneTexture.loadFromFile("ASSETS//IMAGES//planes.png"))
	{
		std::cout << "Error loading big plane" << std::endl;
	}
	m_bigPlane.setTexture(m_bigPlaneTexture);
	m_bigPlane.setTextureRect(bigPlaneRect);
	m_bigPlane.setPosition(bigPlaneStart);
	m_bigPlane.setOrigin(bigPlaneRect.width / 2.0f, bigPlaneRect.height / 2.0f);
	m_bigPlane.setRotation(m_bigPlaneHeading);
	m_bigPlaneLocation = bigPlaneStart;

	if (!m_skyTexture.loadFromFile("ASSETS\\IMAGES\\sky.jpg"))
	{
		std::cout << "problem loading sky" << std::endl;
	}
	m_skyTexture.setRepeated(true);
	m_skySprite.setTexture(m_skyTexture);
	m_skySprite.setTextureRect(sf::IntRect(0, 0, 800, 1000));

	if (!m_skyTexture.loadFromFile("ASSETS\\IMAGES\\sky.jpg"))
	{
		std::cout << "problem loading sky" << std::endl;
	}
	m_skyTexture.setRepeated(true);
}
/// <summary>
/// method for planes to move on their own at the start
/// </summary>
void Game::MovePlanes()
{
	m_smallPlaneLocation += m_smallVelocity;
	m_smallPlane.setPosition(m_smallPlaneLocation);
	m_bigPlaneLocation += m_bigVelocity;
	m_bigPlane.setPosition(m_bigPlaneLocation);
}
/// <summary>
/// makes sure the planes stay on the screen
/// </summary>
/// <param name="t_location">takes in our planes</param>
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
/// <summary>
/// debug mode for sprites, draws 2 rectangles and a ring, they help to detect for size and collision
/// </summary>
/// <param name="t_sprite"></param>
void Game::debugSprite(sf::Sprite& t_sprite)
{
	sf::CircleShape dot;
	sf::CircleShape ring;
	sf::RectangleShape localBox;
	sf::RectangleShape globalBox;
	float radius;

	globalBox.setFillColor(sf::Color::Transparent);
	globalBox.setOutlineColor(sf::Color::Green);
	globalBox.setOutlineThickness(2.0f);
	globalBox.setPosition(t_sprite.getPosition());
	globalBox.setSize(sf::Vector2f(t_sprite.getGlobalBounds().width, t_sprite.getGlobalBounds().height));     //sprite rect intial
	globalBox.setOrigin(t_sprite.getGlobalBounds().width / 2.0f, t_sprite.getGlobalBounds().height / 2.0f);

	localBox.setFillColor(sf::Color::Transparent);
	localBox.setOutlineColor(sf::Color::Black);
	localBox.setOutlineThickness(2.0f);                            //sprite rect smaller for edges
	localBox.setOrigin(t_sprite.getOrigin());
	localBox.setRotation(t_sprite.getRotation());
	localBox.setPosition(t_sprite.getPosition());
	localBox.setSize(sf::Vector2f{ t_sprite.getLocalBounds().width, t_sprite.getLocalBounds().height });


	ring.setFillColor(sf::Color::Transparent);
	ring.setOutlineColor(sf::Color::Red);
	ring.setOutlineThickness(3.0f);                    //circle for better detection
	ring.setPosition(t_sprite.getPosition());
	if (t_sprite.getLocalBounds().height < t_sprite.getLocalBounds().width)
	{
		radius = t_sprite.getLocalBounds().width / 2.0f;
	}
	else
	{
		radius = t_sprite.getLocalBounds().height / 2.0f;
	}
	ring.setRadius(radius);
	ring.setOrigin(t_sprite.getOrigin());

	dot.setFillColor(sf::Color::Yellow);
	dot.setRadius(4.0f);                         //dot for shooting
	dot.setPosition(t_sprite.getPosition());
	dot.setOrigin(4.0f, 4.0f);

	float stretch = 38.0f;
	float angleAdjust = 36.0f;
	sf::Vector2f displace;
	float myangle = (t_sprite.getRotation() - 90.0f + angleAdjust) / 180 * 3.14;        
	displace.x = std::cos(myangle) * stretch;
	displace.y = std::sin(myangle) * stretch;

	dot.setPosition(t_sprite.getPosition() + displace);


	m_window.draw(globalBox);
	m_window.draw(localBox);
	m_window.draw(ring);
	m_window.draw(dot);
}
/// <summary>
/// checks collision if the red rings touch eachother when the planes meet
/// </summary>
/// <param name="t_locationOne">bigplane location</param>
/// <param name="t_radiusOne">big plane circle radius</param>
/// <param name="t_locationTwo">small location</param>
/// <param name="t_radiusTwo">small radius</param>
/// <returns></returns>
bool Game::checkforCollision(sf::Vector2f t_locationOne, float t_radiusOne, sf::Vector2f t_locationTwo, float t_radiusTwo)
{
	float distance = 0.0f;
	sf::Vector2f gap = t_locationOne - t_locationTwo;
	distance = vector2fLenght(gap);
	sf::FloatRect big = m_bigPlane.getGlobalBounds();
	sf::FloatRect small = m_smallPlane.getGlobalBounds();

	if (big.intersects(small))
	{
		std::cout << "kaboom" << std::endl;
	}
	return false;
}
/// <summary>
/// method for length of vector
/// </summary>
/// <param name="t_vector">vector</param>
/// <returns>length</returns>
float Game::vector2fLenght(sf::Vector2f t_vector)
{
	float result = std::sqrtf(t_vector.x * t_vector.x + t_vector.y * t_vector.y);
	return result;
}
