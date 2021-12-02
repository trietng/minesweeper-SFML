#pragma once
#include <SFML\Graphics.hpp>
#include "consola.h"
const sf::Vector2f button_size = sf::Vector2f(160, 40);


struct menu {
    sf::RectangleShape outer, separator, line40px;
    menu();
};

struct text {
    sf::Text textNew, textResume, textOption, textHighScore, textQuit, textEasy, textMedium, textHard, textCustom, textSave, textTimer, textEnd, textName, textPlayer;
    sf::Font fontConsola;
    text();
    sf::Vector2f posText(float x, float y);
};

struct button {
    sf::RectangleShape GreenRect, TriGreenRect, DuoGreenRect;
    button();
    sf::Vector2f posButton(float x, float y);
    bool isButtonPressed(int x, int y, sf::Event e, sf::Vector2f p);
};