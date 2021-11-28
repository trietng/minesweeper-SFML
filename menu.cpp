﻿#include "menu.h"

menu::menu() {
    bool isClearMenu = false;                                                              //Outer line of menu
    outer.setSize(sf::Vector2f(1000, 356));
    outer.setPosition(sf::Vector2f(12, 524));
    outer.setFillColor(sf::Color::Black);
    outer.setOutlineThickness(4.f);
    outer.setOutlineColor(sf::Color::Green);
    //Separator line
    separator.setSize(sf::Vector2f(1000, 4));
    separator.setPosition(sf::Vector2f(12, 588));
    separator.setFillColor(sf::Color::Green);
}

text::text() {
    fontConsola.loadFromMemory(consola_ttf_font, consola_ttf_font_length);
    textNew.setFont(fontConsola);
    textNew.setString("New game");
    textNew.setCharacterSize(24);
    textNew.setFillColor(sf::Color::Green);
    textNew.setPosition(posText(0, 0));
    textResume.setFont(fontConsola);
    textResume.setString("Resume");
    textResume.setCharacterSize(24);
    textResume.setFillColor(sf::Color::Green);
    textResume.setPosition(posText(0, 1));
    textHighScore.setFont(fontConsola);
    textOption.setFont(fontConsola);
    textOption.setString("Options");
    textOption.setCharacterSize(24);
    textOption.setFillColor(sf::Color::Green);
    textOption.setPosition(posText(0, 2));
    textHighScore.setString("High score");
    textHighScore.setCharacterSize(24);
    textHighScore.setFillColor(sf::Color::Green);
    textHighScore.setPosition(posText(0, 3));
    textOption.setFont(fontConsola);
    textQuit.setString("Quit");
    textQuit.setCharacterSize(24);
    textQuit.setFillColor(sf::Color::Green);
    textQuit.setPosition(posText(0, 4));
    textQuit.setFont(fontConsola);
    textEasy.setString("Easy");
    textEasy.setCharacterSize(24);
    textEasy.setFillColor(sf::Color::Green);
    textEasy.setPosition(posText(1, 0));
    textEasy.setFont(fontConsola);
    textMedium.setString("Medium");
    textMedium.setCharacterSize(24);
    textMedium.setFillColor(sf::Color::Green);
    textMedium.setPosition(posText(2, 0));
    textMedium.setFont(fontConsola);
    textHard.setFont(fontConsola);
    textHard.setString("Hard");
    textHard.setCharacterSize(24);
    textHard.setFillColor(sf::Color::Green);
    textHard.setPosition(posText(3, 0));
    textCustom.setFont(fontConsola);
    textCustom.setString("Custom");
    textCustom.setCharacterSize(24);
    textCustom.setFillColor(sf::Color::Green);
    textCustom.setPosition(posText(4, 0));
    textSave.setFont(fontConsola);
    textSave.setString("Save");
    textSave.setCharacterSize(24);
    textSave.setFillColor(sf::Color::Green);
    textSave.setPosition(posText(0, -1));
    textTimer.setFont(fontConsola);
    textTimer.setCharacterSize(24);
    textTimer.setFillColor(sf::Color::Green);
    textTimer.setPosition(posText(4, -1));
    textEnd.setFont(fontConsola);
    textEnd.setCharacterSize(40);
    
}

sf::Vector2f text::posText(float x, float y) {
    if (y == -1) {
        return sf::Vector2f(36 + x * 204, 540);
    }
    return sf::Vector2f(36 + x * 204, 608 + y * 56);
}

button::button() {
    GreenRect.setSize(button_size);
    GreenRect.setFillColor(sf::Color::Black);
    GreenRect.setOutlineThickness(4.f);
    GreenRect.setOutlineColor(sf::Color::Green);
    TriGreenRect.setSize(sf::Vector2f(568, 40));
    TriGreenRect.setFillColor(sf::Color::Black);
    TriGreenRect.setOutlineThickness(4.f);
    TriGreenRect.setOutlineColor(sf::Color::Green);
    TriGreenRect.setPosition(posButton(1, -1));
}
sf::Vector2f button::posButton(int x, int y) {
    if (y == -1) {
        return sf::Vector2f(24 + x * 204, 536);
    }
    return sf::Vector2f(24 + x * 204, 604 + y * 56);
}

bool button::isButtonPressed(int x, int y, sf::Event e, sf::Vector2f p) {
    int a = p.x - 4, b = a + 168, c = p.y - 4, d = c + 48;
    if ((x > a) && (x < b) && (y > c) && (y < d)) {
        if (e.key.code == sf::Mouse::Left) {
            return true;
        }
    }
    return false;
}