#pragma once
#include <SFML\Graphics.hpp>
#include "consola.h"
#include <SFML\System\Time.hpp>
#include <iostream>
const sf::Vector2f button_size = sf::Vector2f(160, 40);


struct menu {
    sf::RectangleShape outer, BlackRect, separator;
    menu();
};

struct text {
    sf::Text textNew, textResume, textOption, textHighScore, textQuit, textEasy, textMedium, textHard, textCustom, textSave, textTimer, textEnd;
    sf::Font fontConsola;
    text();
    sf::Vector2f posText(float x, float y);
};

struct button {
    sf::RectangleShape GreenRect, TriGreenRect;
    button();
    sf::Vector2f posButton(int x, int y);
    bool isButtonPressed(int x, int y, sf::Event e, sf::Vector2f p);
};

