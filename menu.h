#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "consola.h"
const sf::Vector2f button_size = sf::Vector2f(160, 40);


struct menu {
    sf::RectangleShape outer, separator, line40px;
    menu();
};

struct text {
    sf::Text textMainMenu[5], textGamemode[4], textPlayCustom, textSave, textTimer, textEnd, textName, textPlayer, textCustomSetting, textOperator, textCustomValue;
    sf::Font fontConsola;
    text();
    sf::Vector2f posText(const double& x, const double& y);
    std::string MainMenuString(const int& x);
    std::string GamemodeString(const int& x);
    std::string CustomSettingString(const int& x);
    std::string OperatorString(const int& x);
};

struct button {
    sf::RectangleShape GreenRect, TriGreenRect, DuoGreenRect, CustomGreenRect;
    button();
    sf::Vector2f posButton(const double& x, const double& y);
    bool isButtonPressed(const int& x, const int& y, sf::Event& e, sf::Vector2f p);
    bool isOperatorButtonPressed(const int& x, const int& y, sf::Event& e, sf::Vector2f p);
    bool isPlayCustomButtonPressed(const int& x, const int& y, sf::Event& e, sf::Vector2f p);
};

struct custom_value {
    int customWidth, customLength, customMines;
    custom_value();
    void edit_custom_value(const int& value_type, const int& operator_type);
};

struct score_data {
    int rank, score, mode_type;
    std::string name;
    void edit_score(const int& mode_type);
    void save_score(const int& mode_type, const int& point, const int& playerName);
};