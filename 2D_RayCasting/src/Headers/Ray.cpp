#include "Ray.hpp"

Rays::Rays(sf::Vector2<float>* Origin, float fov, float Increment) : origin(Origin), FOV(fov), increment(Increment)
{
	const sf::Vector2<int> winSize = sf::Vector2<int>(_window->getSize());
	this->setPrimitiveType(sf::Lines);
	for (int i = 0; i < 10; ++i) {
		sf::CircleShape* newCirlce = new sf::CircleShape(rand() % 50);

		newCirlce->setOrigin(newCirlce->getRadius(), newCirlce->getRadius());
		newCirlce->setPosition(rand() % winSize.x, rand() % winSize.y);

		sf::Color color = rand() % 10 < 5 ? sf::Color::Red : sf::Color::Blue;
		newCirlce->setFillColor(color);

		circles.push_back(newCirlce);
	}
}

void Rays::addRay(float angle)
{
	(*this).append(sf::Vertex(*origin));
	(*this).append(sf::Vertex(fromAngle<float>(angle, 200)));
}
#include <iostream>
void Rays::checkCircles(int i, float curr)
{
	float minLength = 1000000;
	for (sf::CircleShape* circle : circles) {
		// get circle pos
		sf::Vector2<float> pos = circle->getPosition();

		// get the smallest distance between the cirlce and the current line
		float dist = circleSDF(origin->x, origin->y, pos.x, pos.y, circle->getRadius());

		//set the pos(not angle) to this calculated point
		sf::Vector2<float> tempPos = *origin + fromAngle<float>(angle + curr, dist + circle->getRadius());

		// check if it collides
		float newdist = circleSDF(tempPos.x, tempPos.y, pos.x, pos.y, circle->getRadius());

		float lenght = getMagnitude(*origin - tempPos);

		if (newdist <= 0) {
			if (lenght < minLength) {
				minLength = lenght;

				float temp = dist + newdist;

				tempPos = *origin + fromAngle<float>(angle + curr, temp);

				newdist = circleSDF(tempPos.x, tempPos.y, pos.x, pos.y, circle->getRadius());

				(*this)[i].position = *origin + fromAngle<float>(angle + curr, temp + newdist);

				//const sf::Color color = sf::Color::Green;
				const sf::Color color = circle->getFillColor();
				(*this)[i].color = color;
				(*this)[i - 1].color = color;

				//break;
			}
		}
	}
}

void Rays::update()
{	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left)) {
		angle -= 0.01;
		float curr = -FOV / 2;
		for (int i = 1; i < this->getVertexCount(); i += 2) {
			(*this)[i].position = *origin + fromAngle<float>(angle + curr, 200);
			curr += increment;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right)) {
		angle += 0.01;
		float curr = -FOV / 2;
		for (int i = 1; i < this->getVertexCount(); i += 2) {
			(*this)[i].position = *origin + fromAngle<float>(angle + curr, 200);
			curr += increment;
		}
	}

	float curr = (-FOV / 2) - increment;
	for (int i = 1; i < this->getVertexCount(); i += 2) {
		curr += increment;

		(*this)[i].color = sf::Color::Black;
		(*this)[i - 1].color = sf::Color::Black;

		checkCircles(i, curr);

		// stop checking other objects if collision is found
		if ((*this)[i].color != sf::Color::Black) continue;

		// check other objects

	}

	//for (sf::CircleShape* c : circles) _window->draw(*c);
}

// returns shortest distance from point to cirlce
float Rays::circleSDF(float x, float y, float cx, float cy, float r)
{
	return (std::sqrt(((x - cx) * (x - cx)) + ((y - cy) * (y - cy)))) - r;
}