#include <menu.h>

menu::menu() {
    outer.setSize(sf::Vector2f(1000, 232));
    outer.setPosition(sf::Vector2f(12, 524));
    outer.setFillColor(sf::Color::Black);
    outer.setOutlineThickness(4.f);
    outer.setOutlineColor(sf::Color::Green);
}

text::text() {
    fontConsola.loadFromMemory(consola_ttf_font, consola_ttf_font_length);
    textNew.setFont(fontConsola);
    textNew.setString("New game");
    textNew.setCharacterSize(24);
    textNew.setFillColor(sf::Color::Green);
    textNew.setPosition(36, 540);
    textHighScore.setFont(fontConsola);
    textHighScore.setString("High score");
    textHighScore.setCharacterSize(24);
    textHighScore.setFillColor(sf::Color::Green);
    textHighScore.setPosition(36, 652);
    textOption.setFont(fontConsola);
    textOption.setString("Option");
    textOption.setCharacterSize(24);
    textOption.setFillColor(sf::Color::Green);
    textOption.setPosition(36, 596);
    textQuit.setFont(fontConsola);
    textQuit.setString("Quit");
    textQuit.setCharacterSize(24);
    textQuit.setFillColor(sf::Color::Green);
    textQuit.setPosition(36, 708);
}

button::button() {
    GreenRect.setSize(button_size);
    GreenRect.setFillColor(sf::Color::Black);
    GreenRect.setOutlineThickness(4.f);
    GreenRect.setOutlineColor(sf::Color::Green);
}
sf::Vector2f button::posButton(int x, int y)
{
    return sf::Vector2f(24 + x * 204, 536 + y * 56);
}