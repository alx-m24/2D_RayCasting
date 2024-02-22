#pragma once
#include <SFML/Graphics.hpp>
#include "Common.hpp"
#include "MyVec.hpp"
#include "Ray.hpp"

class Player : public sf::CircleShape {
private:
	Rays* rays;
	sf::Vector2<float>* origin;

	bool topView = false, lastT = false;

	float mag = 250.0f;
	float FOV = PI / 3;
	float angle = 0;
	float increment = PI / 512;
public:
	Player(sf::Vector2<float>* Origin);
public:
	void update();
	void draw();
};