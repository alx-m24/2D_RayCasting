#include "MainLoop.hpp"

World::World()
{
	p = new Player(&origin);
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
			break;
		}
		case sf::Event::MouseMoved: {
			origin = sf::Vector2f(sf::Mouse::getPosition(*_window).x, sf::Mouse::getPosition(*_window).y);
			break;
		}
		default:
			break;
		}
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
	_window->display();
}
