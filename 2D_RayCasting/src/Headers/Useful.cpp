#include "Useful.hpp"

bool setupWindow()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	_window = new sf::RenderWindow(sf::VideoMode(1000, 650), "2D_RayCasting", sf::Style::Default, settings);
	_window->setVerticalSyncEnabled(true);

	return (bool)_window;
}

void createArialFont()
{
	_arial.loadFromFile("C:\\\Windows\\Fonts\\arial.ttf");
	_arial.setSmooth(true);
}

void setupFps(sf::Text* fpsText)
{
	fpsText->setFillColor(sf::Color::Red);
	fpsText->setCharacterSize(24);
	fpsText->setFont(_arial);
}

void updateFPS(sf::Text* fpsText, unsigned int* Frame, sf::Clock* clock)
{
	if (clock->getElapsedTime().asSeconds() >= 1.0f) {
		clock->restart();
		fpsText->setString("FPS: " + std::to_string(*Frame));
		*Frame = 0;
	}
	++ *Frame;

	_window->draw(*fpsText);
}
