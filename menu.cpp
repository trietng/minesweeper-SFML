#include "menu.h"

highscore::highscore() {
    point = 0;
    mode_type = -1;
}

bool comp_score(const highscore& hs1, const highscore& hs2) {
    return (hs1.point > hs2.point) ? true : false;
}

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
    for (int j = 0; j < 3; ++j) {
        for (int i = 0; i < 9; ++i) {
            textHighscores[j][i].setFont(fontConsola);
            textHighscores[j][i].setCharacterSize(24);
            textHighscores[j][i].setFillColor(sf::Color::Green);
            textHighscores[j][i].setPosition(posText(j, i - 10));
        }
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

custom_value::custom_value() {
    customLength = 10;
    customWidth = 10;
    customMines = 10;
}

void custom_value::edit_custom_value(const int& value_type, const int& operator_type) {
    switch (operator_type) {
    case 0:
        switch (value_type) {
        case 1:
            if (customWidth > 7) {
                customWidth -= 5;
            }
            break;
        case 2:
            if (customLength > 7) {
                customLength -= 5;
            }
            break;
        case 3:
            if (customMines > 5) {
                customMines -= 5;
            }
            break;
        default:
            break;
        }
        break;
    case 1:
        switch (value_type) {
        case 1:
            if (customWidth > 3) {
                --customWidth;
            }
            break;
        case 2:
            if (customLength > 3) {
                --customLength;
            }
            break;
        case 3:
            if (customMines > 1) {
                --customMines;
            }
            break;
        default:
            break;
        }
        break;
    case 2:
        switch (value_type) {
        case 1:
            if (customWidth < 32) {
                ++customWidth;
            }
            break;
        case 2:
            if (customLength < 16) {
                ++customLength;
            }
            break;
        case 3:
            if (customMines < customWidth * customLength - 2) {
                ++customMines;
            }
            break;
        default:
            break;
        }
        break;
    case 3:
        switch (value_type) {
        case 1:
            if (customWidth < 28) {
                customWidth += 5;
            }
            break;
        case 2:
            if (customLength < 12) {
                customLength += 5;
            }
            break;
        case 3:
            if (customMines < customWidth * customLength - 6) {
                customMines += 5;
            }
            break;
        default:
            break;
        }
        break;
    }
    if (customMines > customWidth * customLength) {
        customMines = customWidth * customLength - 2;
    }
}

int highscores::to_int(const std::string& str) {
    int result = 0;
    for (int i = 0; i < str.size(); ++i) {
        if (isdigit(str[i])) {
            result = result * 10 + (str[i] - '0');
        }
    }
    return result;
}

int highscores::to_int(const char& ch) {
    return (isdigit(ch)) ? (ch - '0') : -1;
}

int highscores::calc_point(const int& mode_type, const int& time) {
    return 0;
}

void highscores::proc_score(const std::string& value) {
    highscore assigned_value;
    assigned_value.mode_type = to_int(value[0]);
    assigned_value.playerName = value.substr(2, 6);
    assigned_value.point = to_int(value.substr(9, 4));
    switch (assigned_value.mode_type) {
    case 0:
        easy.push_back(assigned_value);
        break;
    case 1:
        medium.push_back(assigned_value);
        break;
    case 2:
        hard.push_back(assigned_value);
        break;
    default:
        break;
    }
}

void highscores::save_score(const int& mode_type, const int& point, const std::string& playerName) {
    std::ofstream output("highscores.txt", std::ios_base::app);
    if (output.is_open()) {
        output << mode_type << ' ' << playerName << ' ' << point << "\n";
        output.close();
    }
}

void highscores::load_score() {
    std::ifstream input("highscores.txt");
    std::string load_value;
    easy.clear();
    medium.clear();
    hard.clear();
    if (input.is_open()) {
        while (!input.eof()) {
            std::getline(input, load_value);
            proc_score(load_value);
        }
        input.close();
    }
    vector_hs_sort();
}

void highscores::vector_hs_sort() {
    if (easy.size() != 0) {
        std::sort(easy.begin(), easy.end(), comp_score);
    }
    if (medium.size() != 0) {
        std::sort(medium.begin(), medium.end(), comp_score);
    }
    if (hard.size() != 0) {
        std::sort(hard.begin(), easy.end(), comp_score);
    }
}

void highscores::set_print_value(const std::vector<highscore> hs) {
    print_value.clear();
    for (int i = 0; i < hs.size(); i++) {
        print_value.push_back(hs[i].playerName + " " + std::to_string(hs[i].point));
    }
}
