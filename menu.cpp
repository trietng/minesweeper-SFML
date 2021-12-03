#include "menu.h"

menu::menu() {                                                            //Outer line of menu
    outer.setSize(sf::Vector2f(1000, 356));
    outer.setPosition(sf::Vector2f(12, 524));
    outer.setFillColor(sf::Color::Black);
    outer.setOutlineThickness(4.f);
    outer.setOutlineColor(sf::Color::Green);
    //Separator line
    separator.setSize(sf::Vector2f(1000, 4));
    separator.setPosition(sf::Vector2f(12, 588));
    separator.setFillColor(sf::Color::Green);
    //40 px vertical line
    line40px.setSize(sf::Vector2f(4, 40));
    line40px.setFillColor(sf::Color::Green);
}

text::text() {
    fontConsola.loadFromMemory(consola_ttf_font, consola_ttf_font_length);

    for (int i = 0; i < 5; ++i) {
        textMainMenu[i].setFont(fontConsola);
        textMainMenu[i].setCharacterSize(24);
        textMainMenu[i].setFillColor(sf::Color::Green);
        textMainMenu[i].setPosition(posText(0, i));
        textMainMenu[i].setString(MainMenuString(i));
    }

    for (int i = 0; i < 4; ++i) {
        textGamemode[i].setFont(fontConsola);
        textGamemode[i].setCharacterSize(24);
        textGamemode[i].setFillColor(sf::Color::Green);
        textGamemode[i].setPosition(posText(i + 1, 0));
        textGamemode[i].setString(GamemodeString(i + 1));
    }

    textPlayCustom.setFont(fontConsola);
    textPlayCustom.setString("Play custom");
    textPlayCustom.setCharacterSize(24);
    textPlayCustom.setFillColor(sf::Color::Green);
    textPlayCustom.setPosition(posText(3.5, 4));

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
    
    textName.setFont(fontConsola);
    textName.setCharacterSize(24);
    textName.setFillColor(sf::Color::Green);
    textName.setPosition(posText(1, 0));
    textName.setString("Enter your name");
    
    textPlayer.setFont(fontConsola);
    textPlayer.setCharacterSize(24);
    textPlayer.setFillColor(sf::Color::Green);
    textPlayer.setPosition(posText(2.2, 0));
    
    textCustomSetting.setFont(fontConsola);
    textCustomSetting.setCharacterSize(24);
    textCustomSetting.setFillColor(sf::Color::Green);

    textOperator.setFont(fontConsola);
    textOperator.setCharacterSize(24);
    textOperator.setFillColor(sf::Color::Green);

    textCustomValue.setFont(fontConsola);
    textCustomValue.setCharacterSize(24);
    textCustomValue.setFillColor(sf::Color::Green);
}

sf::Vector2f text::posText(const double& x, const double& y) {
    if (y == -1) {
        return sf::Vector2f(36 + x * 204, 540);
    }
    return sf::Vector2f(36 + x * 204, 608 + y * 56);
}

std::string text::MainMenuString(const int& x) {
    switch (x) {
    case 0:
        return "New game";
        break;
    case 1:
        return "Load game";
        break;
    case 2:
        return "Options";
        break;
    case 3:
        return "Highscores";
        break;
    case 4:
        return "Quit";
        break;
    default:
        break;
    }
}

std::string text::GamemodeString(const int& x) {
    switch (x) {
    case 1:
        return "Easy";
        break;
    case 2:
        return "Medium";
        break;
    case 3:
        return "Hard";
        break;
    case 4:
        return "Custom";
        break;
    default:
        break;
    }
}

std::string text::CustomSettingString(const int& x) {
    switch (x) {
        case 1:
            return "Width";
            break;
        case 2:
            return "Length";
            break;
        case 3:
            return "Mines";
            break;
        default:
            break;
    }
}

std::string text::OperatorString(const int& x) {
    switch (x) {
        case 0:
            return "-5";
            break;
        case 1:
            return "-";
            break;
        case 2:
            return "+";
            break;
        case 3:
            return "+5";
            break;
        default:
            break;
    }
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
    
    DuoGreenRect.setSize(sf::Vector2f(364, 40));
    DuoGreenRect.setFillColor(sf::Color::Black);
    DuoGreenRect.setOutlineThickness(4.f);
    DuoGreenRect.setOutlineColor(sf::Color::Green);
    DuoGreenRect.setPosition(posButton(1, 0));
    
    CustomGreenRect.setSize(sf::Vector2f(364, 40));
    CustomGreenRect.setFillColor(sf::Color::Black);
    CustomGreenRect.setOutlineThickness(4.f);
    CustomGreenRect.setOutlineColor(sf::Color::Green);
}
sf::Vector2f button::posButton(const double& x, const double& y) {
    if (y == -1) {
        return sf::Vector2f(24 + x * 204, 536);
    }
    return sf::Vector2f(24 + x * 204, 604 + y * 56);
}

bool button::isButtonPressed(const int& x, const int& y, sf::Event& e, sf::Vector2f p) {
    int a = p.x - 4, b = a + 168, c = p.y - 4, d = c + 48;
    if ((x > a) && (x < b) && (y > c) && (y < d)) {
        if (e.key.code == sf::Mouse::Left) {
            return true;
        }
    }
    return false;
}

bool button::isOperatorButtonPressed(const int& x, const int& y, sf::Event& e, sf::Vector2f p) {
    int a = p.x, b = a + 40, c = p.y, d = c + 40;
    if ((x > a) && (x < b) && (y > c) && (y < d)) {
        if (e.key.code == sf::Mouse::Left) {
            return true;
        }
    }
    return false;
}

bool button::isPlayCustomButtonPressed(const int& x, const int& y, sf::Event& e, sf::Vector2f p) {
    int a = p.x - 4, b = a + 372, c = p.y - 4, d = c + 48;
    if ((x > a) && (x < b) && (y > c) && (y < d)) {
        if (e.key.code == sf::Mouse::Left) {
            return true;
        }
    }
    return false;
}