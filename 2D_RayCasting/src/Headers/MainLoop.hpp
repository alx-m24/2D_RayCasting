#pragma once
#include "Common.hpp"
#include "Player.hpp"

class World {
private:
	Player* p;

private:
	sf::Vector2<float> origin = { 0, 0 };

public:
	World();

public:
	void input();
	void update();
	void render();
};