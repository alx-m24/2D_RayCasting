#include "MainLoop.hpp"

World::World()
{
	p = new Player(&origin);
	control = sf::Text("Press T to change view", _arial, 24);
	control.setPosition(15, _window->getSize().y - 30);

	setupFps(&fpsText);
}

void World::input()
{
	sf::Event event;
	while (_window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed: {
			_window->close();
			break;
		}
		case sf::Event::Resized: {
			_window->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
			control.setPosition(15, _window->getSize().y - 30);
			break;
		}
		case sf::Event::MouseMoved: {
			if (p->topView) origin = sf::Vector2f(sf::Mouse::getPosition(*_window).x, sf::Mouse::getPosition(*_window).y);
			break;
		}
		case sf::Event::MouseButtonPressed: {
			showMouse = true;
			break;
		}
		default:
			break;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		_window->setMouseCursorVisible(true);
		showMouse = true;
	}
}

void World::update()
{
	_window->clear();
	p->update();
}

void World::render()
{
	p->draw();
	updateFPS(&fpsText, &Frame, &fpsClock);
	_window->draw(control);
	_window->display();
}
