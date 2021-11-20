#pragma once
#include <SFML\Graphics.hpp>
#include <consola.h>
const sf::Vector2f button_size = sf::Vector2f(160, 40);

struct menu {
    sf::RectangleShape outer;
    menu();
};

struct text {
    sf::Text textNew, textOption, textHighScore, textQuit;
    sf::Font fontConsola;
    text();
};

struct button {
    sf::RectangleShape GreenRect;
    button();
    sf::Vector2f posButton(int x, int y);
};