#include <SFML/Graphics.hpp>
// My headers
#include "Headers/Useful.hpp"
#include "Headers/MainLoop.hpp"

sf::RenderWindow* _window;
sf::Font _arial;
bool showMouse;

int main() {
	if (!setupWindow()) return EXIT_FAILURE;
	createArialFont();

	srand(time(0));

	World world;

	while (_window->isOpen()) {
		world.input();

		world.update();

		world.render();
	}

	delete _window;
	return EXIT_SUCCESS;
}