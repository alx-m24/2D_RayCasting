#pragma once
#include "Common.hpp"
#include "Player.hpp"
#include "Useful.hpp"

class World {
private:
	Player* p;
	sf::Text control;
	sf::Text fpsText;
	
private:
	unsigned int Frame = 0;
	sf::Clock fpsClock;

private:
	sf::Vector2<float> origin = { 0, 0 };

public:
	World();

public:
	void input();
	void update();
	void render();
};