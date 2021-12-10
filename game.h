#pragma once
#include <SFML\Graphics.hpp>
#include <ctime>
#include <iostream>
#include "tiles.h"
#include "tiles.color.h"
#include "board.h"
#include "menu.h"
const int cell_length = 32;

struct control {
	bool isNewPressed, isCustomPressed, isModePressed, openNameDialog, isHighscoresPressed, isOptionsPressed, colorState;
	int gamemode;
	control();
};

struct game {
	sf::Texture b_texture_default, b_texture_color;
	sf::Sprite b_sprite;
	sf::Clock clock;
	sf::String playerInput;
	board b;
	menu m;
	text txt;
	button btn;
	custom_value cval;
	control ctrl;
	highscores hscr;
	saveload sl;
	int deltaTime, lastTime, currentTime, realTime;
	game();
};