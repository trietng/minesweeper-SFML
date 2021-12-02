#pragma once
#include <SFML\Graphics.hpp>
#include <ctime>
#include <iostream>
#include "tiles.h"
#include "board.h"
#include "menu.h"
const int cell_length = 32;

struct game {
	sf::Texture b_texture;
	sf::Sprite b_sprite;
	sf::Clock clock;
	sf::String playerInput;
	board b;
	menu m;
	text txt;
	button btn;
	custom_value cval;
	int deltaTime, lastTime, currentTime, realTime;
	bool isNewPressed, isCustomPressed, isModePressed, openNameDialog;
	game();
};

