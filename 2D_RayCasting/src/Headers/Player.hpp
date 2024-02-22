#pragma once
#include <SFML/Graphics.hpp>
#include "Common.hpp"
#include "MyVec.hpp"
#include "Ray.hpp"

class Player : public sf::CircleShape {
private:
	Rays* rays;
	sf::Vector2<float>* origin;

	bool lastT = false;

	float FOV = PI / 3; // Best Pi/3
	float angle = 0;
	// Denomenator shoulder be a multiple of 2
	float increment = PI / 1024; // bests: 512(220 FPS) | 1024(120 FPS)
public:
	Player(sf::Vector2<float>* Origin);
public:
	bool topView = true;

	void update();
	void draw();
	void move();
};