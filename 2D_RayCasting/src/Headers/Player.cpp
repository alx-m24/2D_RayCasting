#include "Player.hpp"

Player::Player(sf::Vector2<float>* Origin) : origin(Origin)
{
	rays = new Rays(origin, FOV, increment);

	this->setRadius(20.0f);
	this->setOrigin(this->getRadius(), this->getRadius());
	this->update();

	for (float i = -FOV / 2; i < FOV / 2; i += increment) {
		rays->addRay(i);
	}
}

void Player::update()
{
	sf::Vector2f lastPos = this->getPosition();

	move();

	this->setPosition(*origin);

	for (int i = 0; i < rays->getVertexCount(); ++i) {
		(*rays)[i].position += (*origin - lastPos);
	}

	angle = rays->update(topView);
}


void Player::draw()
{
	sf::Vector2<float> winSize = sf::Vector2<float>(_window->getSize());

	bool T = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::T);
	if (T && !lastT) {
		topView = !topView;
		_window->setMouseCursorVisible(topView);
		showMouse = topView;
	}
	lastT = T;

	if (!topView) {
		std::vector<sf::RectangleShape*> lines;

		int rayNum = rays->getVertexCount() / 2;
		float xSize = winSize.x / rayNum;
		float xPos = (xSize / 2.0f) - xSize;

		for (int i = 1; i < rayNum * 2; i += 2) {
			xPos += xSize;

			sf::Vertex curr = (*rays)[i];
			if (curr.color == sf::Color::Black) continue;

			float length = getMagnitude(sf::Vector2<float>(*origin - curr.position)) / 50.0f;

			float ySize = winSize.y / length;

			sf::RectangleShape* line = new sf::RectangleShape(sf::Vector2<float>(xSize, ySize));

			line->setOrigin(line->getSize() / 2.0f);

			sf::Color color = sf::Color(curr.color.r / length, curr.color.g / length, curr.color.b / length);
			line->setFillColor(color);

			line->setPosition(xPos, winSize.y / 2.0f);

			lines.push_back(line);
		}

		for (sf::RectangleShape* l : lines) {
			_window->draw(*l);
			delete l;
		}
		lines.clear();
	}
	else {
		for (sf::CircleShape* c : rays->circles) _window->draw(*c);
		_window->draw(rays->lines);
		_window->draw(*rays);
		_window->draw(*this);
	}
}

void Player::move()
{
	if (!topView) {
		float speed = 1.0f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) speed = 2.0f;
		sf::Vector2f Velocity = { 0, 0 };

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			Velocity += fromAngle<float>(angle);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			Velocity -= fromAngle<float>(angle);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			Velocity += fromAngle<float>(angle - (PI / 2));
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			Velocity += fromAngle<float>(angle + (PI / 2));
		}

		*origin += normalize<float>(Velocity) * speed;
	}
}
