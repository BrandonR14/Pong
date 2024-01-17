#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>

class Game
{
private:
	int width, height, fps;
	const char* title;

	sf::RenderWindow* window;
	sf::Event ev;

	sf::RectangleShape bar1;
	sf::RectangleShape bar2;
	sf::CircleShape ball;

	sf::Vector2f position;

	bool score = true;

	float barspeed;
	float ballspeedx;
	float ballspeedy;
	float time;
	float bounceangle;
	float Maxbounceangle;

	void initWindow();
	void initBars();
	void initBall();

public:
	Game();
	~Game();

	bool running = false;

	void updateBars();
	void updateWindowBounds();
	void updateball();
	void updateballBounds();
	void pollevents();
	void update();
	void render();
	
};

