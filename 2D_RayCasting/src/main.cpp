#include <SFML/Graphics.hpp>
// My headers
#include "Headers/Useful.hpp"
#include "Headers/MainLoop.hpp"

sf::RenderWindow* _window;
sf::Font _arial;

int main() {
	if (!setupWindow()) return EXIT_FAILURE;
	createArialFont();

	srand(time(0));

	World world;

	sf::Text fpsText;
	setupFps(&fpsText);

	sf::Text control("Press T to change view", _arial, 24);
	control.setPosition(15, _window->getSize().y - 30);

	unsigned int Frame = 0;
	sf::Clock fpsClock;
	while (_window->isOpen()) {
		world.input();

		world.update();

		updateFPS(&fpsText, &Frame, &fpsClock);
		_window->draw(control);
		world.render();
	}

	delete _window;
	return EXIT_SUCCESS;
}