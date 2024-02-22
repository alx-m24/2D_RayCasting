#pragma once
#include <SFML/Graphics.hpp>
#include "Common.hpp"

// setup the main window
bool setupWindow();
// create arial font
void createArialFont();
// FPS display setup
void setupFps(sf::Text* fpsText);
// Update FPS display
void updateFPS(sf::Text* fpsText, unsigned int* Frame, sf::Clock* clock);