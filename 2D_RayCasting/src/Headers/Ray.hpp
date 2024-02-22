#pragma once
#include "MyVec.hpp"
#include "Common.hpp"

class Rays : public sf::VertexArray {
private:
	sf::Vector2<float>* origin;
	sf::Vector2f lastMousePos;

	float FOV, angle = 0.0f, increment;
public:
	Rays(sf::Vector2<float>* Origin, float fov, float Increment);
	std::vector<sf::CircleShape*> circles;
	sf::VertexArray lines;
public:
	void addRay(float angle);
	void checkCircles(int i, float curr, float* minLength);
	void checkLines(int i, float curr, float* minLength);

	float update(bool topView);

	float circleSDF(float x, float y, float cx, float cy, float r);
	// Zero mean no collision, else it return the magnitude betwenn the ray and the point of intersection
	float lineSDF(sf::Vector2f p1, sf::VertexArray line, float angle);
};