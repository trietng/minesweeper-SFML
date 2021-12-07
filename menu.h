#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "consola.h"
const sf::Vector2f button_size = sf::Vector2f(160, 40);

struct highscore {
    int point, mode_type;
    std::string playerName;
    highscore();
};

static bool comp_score(const highscore& hs1, const highscore& hs2);

struct menu {
    sf::RectangleShape outer, separator, line40px;
    menu();
};

struct text {
    sf::Text textPlayCustom, textSave, textTimer, textEnd, textName, textPlayer, textCustomSetting, textOperator, textCustomValue;
    sf::Text textMainMenu[5], textGamemode[4], textHighscores[3][10], textOptions[2];
    sf::Font fontConsola;
    text();
    sf::Vector2f posText(const double& x, const double& y);
    std::string MainMenuString(const int& x);
    std::string GamemodeString(const int& x);
    std::string CustomSettingString(const int& x);
    std::string OperatorString(const int& x);
    std::string OptionsString(const int& x);
};

struct button {
    sf::RectangleShape GreenRect, TriGreenRect, DuoGreenRect, CustomGreenRect, HSGreenRect;
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

struct highscores {
    std::vector<highscore> easy, medium, hard;
    std::vector<std::string> print_value;
    int to_int(const std::string& str);
    int to_int(const char& ch);
    int calc_point(const int& mode_type, const int& time);
    void proc_score(const std::string& value);
    void save_score(const int& mode_type, const int& point, const std::string& playerName);
    void load_score();
    void vector_hs_sort();
};