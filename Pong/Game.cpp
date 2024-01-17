#include "Game.h"

Game::Game() {
	width = 1600;
	height = 1200;
	fps = 60;
	title = "SMFL Pong Game";
	barspeed = 17.f;
	ballspeedx = 10.f;
	ballspeedy = 10.f;
	Maxbounceangle = (5 * 3.14159 / 12);

	initWindow();
	initBall();
	initBars();
}

Game:: ~Game() 
{
	delete window;
	
}

void Game::initWindow() {
	window = new sf::RenderWindow(sf::VideoMode(width, height), title);
	window->setFramerateLimit(fps);
	running = true;
}

void Game::pollevents()
{
	while (window->pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed)
		{
			window->close();
			running = false;
		}

	}
}
void Game::initBars()
{
	//left bar
	bar1.setFillColor(sf::Color::White);
	bar1.setSize(sf::Vector2f(30.0f, 200.0f));
	bar1.setPosition(sf::Vector2f(140.0f, 500.0f));
	//right bar
	bar2.setFillColor(sf::Color::White);
	bar2.setSize(sf::Vector2f(30.0f, 200.0f));
	bar2.setPosition(sf::Vector2f(1400.0f, 500.0f));
}

void Game::updateBars()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		bar1.move(0.f, -barspeed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		bar1.move(0.f , barspeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		bar2.move(0.f, -barspeed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		bar2.move(0.f, barspeed);
	}
		
}

void Game::updateWindowBounds()
{
	sf::FloatRect barBounds = bar1.getGlobalBounds();
	if (barBounds.top <= 0.f)
	{
		bar1.setPosition(barBounds.left, 0.f);
	}
	else if (barBounds.top + barBounds.height >= 1200)
	{
		bar1.setPosition(barBounds.left, 1200 - barBounds.height);
	}
	sf::FloatRect bar2Bounds = bar2.getGlobalBounds();
	if (bar2Bounds.top <= 0.f)
	{
		bar2.setPosition(bar2Bounds.left, 0.f);
	}
	else if (bar2Bounds.top + bar2Bounds.height >= 1200)
	{
		bar2.setPosition(bar2Bounds.left, 1200 - bar2Bounds.height);
	}

	
}

void Game::initBall()
{
	ball.setFillColor(sf::Color::White);
	ball.setRadius(24.f);
	ball.setPosition(sf::Vector2f(800.0f, 550.0f));
}

void Game::updateball()
{
	sf::Clock clock;
	time = clock.getElapsedTime().asSeconds();
	if (score == true)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			ball.move(ballspeedx, ballspeedy);
			score = false;
		}
	}
	else
	{
		ball.move(ballspeedx, ballspeedy);
	}
	
}

void Game::updateballBounds()
{
	sf::FloatRect ballBounds = ball.getGlobalBounds();
	sf::FloatRect bar2Bounds = bar2.getGlobalBounds();
	sf::FloatRect barBounds = bar1.getGlobalBounds();
	if (ballBounds.top <= 0.f)
	{
		ballspeedy = -ballspeedy;
	}
	else if (ballBounds.top + ballBounds.height >= 1200)
	{
		ballspeedy = -ballspeedy;
	}
	if (bar1.getGlobalBounds().intersects(ball.getGlobalBounds()))
	{
		ballspeedx = -ballspeedx;
	}
	else if (bar2.getGlobalBounds().intersects(ball.getGlobalBounds()))
	{
		ballspeedx = -ballspeedx;
	}
	if (ballBounds.left <= barBounds.left - 5)
	{
		ball.setPosition(sf::Vector2f(800.0f, 550.0f));
		score = true;
		
	}
	else if (ballBounds.left + ballBounds.width >= bar2Bounds.width + bar2Bounds.left + 5)
	{
		ball.setPosition(sf::Vector2f(800.0f, 550.0f));
		score = true;
	}
	
}

void Game::update()
{
	pollevents();
	updateBars();
	updateball();
	updateballBounds();
	updateWindowBounds();
}

void Game::render()
{
	window->clear();

	window->draw(ball);
	window->draw(bar1);
	window->draw(bar2);

	window->display();
}