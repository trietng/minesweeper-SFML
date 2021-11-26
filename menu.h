#pragma once
#include <SFML\Graphics.hpp>
#include "consola.h"
const sf::Vector2f button_size = sf::Vector2f(160, 40);

struct menu {
    sf::RectangleShape outer, BlackRect, separator;
    menu();
};

struct text {
    sf::Text textNew, textResume, textOption, textHighScore, textQuit, textEasy, textMedium, textHard, textCustom, textSave;
    sf::Font fontConsola;
    text();
    sf::Vector2f posText(int x, int y);
};

struct button {
    sf::RectangleShape GreenRect;
    button();
    sf::Vector2f posButton(int x, int y);
    bool isButtonPressed(int x, int y, sf::Event e, sf::Vector2f p);
};