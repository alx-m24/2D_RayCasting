#pragma once
#include "MyVec.hpp"
#include "Common.hpp"

class Rays : public sf::VertexArray {
private:
	sf::Vector2<float>* origin;
	float FOV, angle = 0.0f, increment;
public:
	Rays(sf::Vector2<float>* Origin, float fov, float Increment);
	std::vector<sf::CircleShape*> circles;
public:
	void addRay(float angle);
	void checkCircles(int i, float curr);

	void update();

	float circleSDF(float x, float y, float cx, float cy, float r);
	float lineSDF();
};