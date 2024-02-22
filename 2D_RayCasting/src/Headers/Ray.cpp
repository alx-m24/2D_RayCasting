#include "Ray.hpp"
#include <iostream>

Rays::Rays(sf::Vector2<float>* Origin, float fov, float Increment) : origin(Origin), FOV(fov), increment(Increment)
{
	const sf::Vector2<int> winSize = sf::Vector2<int>(_window->getSize());
	this->setPrimitiveType(sf::Lines);

	lines.setPrimitiveType(sf::Lines);

	for (int i = 0; i < 10; ++i) {
		sf::Color color = rand() % 10 < 5 ? sf::Color::Red : sf::Color::Blue;

		sf::Vertex p1(sf::Vector2f(rand() % winSize.x, rand() % winSize.y));
		sf::Vertex p2(sf::Vector2f(rand() % winSize.x, rand() % winSize.y));

		p1.color = color;
		p2.color = color;

		lines.append(p1);
		lines.append(p2);
	}
	
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

void Rays::checkCircles(int i, float curr, float* minLength)
{
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
			if (lenght < *minLength) {
				*minLength = lenght;

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

void Rays::checkLines(int i, float curr, float* minLength)
{
	for (int j = 0; j < lines.getVertexCount(); j += 2) {
		sf::Vector2<float> tempPos = *origin + fromAngle<float>(angle + curr, 100);

		sf::Vertex p1 = lines[j];
		sf::Vertex p2 = lines[j + 1];
		sf::VertexArray line;
		line.setPrimitiveType(sf::Lines);
		line.append(p1);
		line.append(p2);

		float length = lineSDF(tempPos, line, angle + curr);

		if (length > 0.0f) {
			if (length < *minLength) {
				*minLength = length;

				(*this)[i].position = *origin + fromAngle<float>(angle + curr, length);

				const sf::Color color = p1.color;
				(*this)[i].color = color;
				(*this)[i - 1].color = color;
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

		float minLength = 1000000;

		checkCircles(i, curr, &minLength);
		checkLines(i, curr, &minLength);
	}

	//for (sf::CircleShape* c : circles) _window->draw(*c);
}

// returns shortest distance from point to cirlce
float Rays::circleSDF(float x, float y, float cx, float cy, float r)
{
	return (std::sqrt(((x - cx) * (x - cx)) + ((y - cy) * (y - cy)))) - r;
}

float Rays::lineSDF(sf::Vector2f p1, sf::VertexArray line, float angle)
{
	sf::Vector2f p2 = line[0].position;

	float m1 = (p1.y - origin->y) / (p1.x - origin->x);
	float m2 = (line[1].position.y - p2.y) / (line[1].position.x - p2.x);

	if (m1 == m2) return 0.0f;

	// y = mx + c
	float c1 = p1.y - (m1 * p1.x);
	float c2 = p2.y - (m2 * p2.x);

	float x = (c2 - c1) / (m1 - m2);
	float y = m1 * x + c1;

	if (!line.getBounds().contains(x, y)) return 0.0f;

	float length = getMagnitude(*origin - sf::Vector2f(x, y));

	// if the length is smaller than the pos of the ray - the pos of the line, it is not collision
	sf::Vector2f temp = *origin + fromAngle<float>(angle, length);

	if (getMagnitude(sf::Vector2f(x, y) - temp) > length) return 0.0f;

	return length;
}


