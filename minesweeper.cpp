#include <SFML/Graphics.hpp>
#include <ctime>
#include "tiles.h"
#include "consola.h"
const int cell_length = 32;
const sf::Vector2f button_size = sf::Vector2f(160, 40);

struct board {
    std::vector<std::vector<int>> mem_cell, cell;
    int i, j;
    board() {
        i = 0;
        j = 0;
    }
    board(int x, int y) {
        i = x;
        j = y;
        mem_cell.assign(x, std::vector<int>(y,0));
        cell.assign(x, std::vector<int>(y, 0));
        setMine();
        for (int a = 0; a < x; a++) {
            for (int b = 0; b < y; b++) {
                if (!checkMine(a, b)) {
                    setCellNum(a, b);
                }
            }
        }
    }
    void setMine() {
        for (int x = 0; x < i; ++x) {
            for (int y = 0; y < j; ++y) {
                cell[x][y] = 10;
                if ((rand() % 5 + 1) == 1) {
                    mem_cell[x][y] = 9;
                }
                else {
                    mem_cell[x][y] = 0;
                }
            }
        }
    }
    bool checkMine(int x, int y) {
        if (mem_cell[x][y] == 9) {
            return true;
        }
        else {
            return false;
        }
    }
    bool isZero(int x, int y) {
        if (mem_cell[x][y] == 0) {
            return true;
        }
        else {
            return false;
        }
    }
    bool isRevealed(int x, int y) {
        if (cell[x][y] != 10) {
            return true;
        }
        else {
            return false;
        }
    }
    bool isPositive(int x, int y) {
        if ((mem_cell[x][y] >= 1) && (mem_cell[x][y] <= 8)) {
            return true;
        }
        else {
            return false;
        }
    }
    void setCellNum(int x, int y) {
        int n = 0;
        if (y < j - 1) {
            if (checkMine(x, y + 1)) {
                ++n;
            }
        }
        if (x < i - 1) {
            if (checkMine(x + 1, y)) {
                ++n;
            }
        }
        if (x > 0) {
            if (checkMine(x - 1, y)) {
                ++n;
            }
        }
        if (y > 0) {
            if (checkMine(x, y - 1)) {
                ++n;
            }
        }
        if ((x < i - 1) && (y < j - 1)) {
            if (checkMine(x + 1, y + 1)) {
                ++n;
            }
        }
        if ((x > 0) && (y < j - 1)) {
            if (checkMine(x - 1, y + 1)) {
                ++n;
            }
        }
        if ((y > 0) && (x < i - 1)) {
            if (checkMine(x + 1, y - 1)) {
                ++n;
            }
        }
        if ((y > 0) && (x > 0)) {
            if (checkMine(x - 1, y - 1)) {
                ++n;
            }
        }
        mem_cell[x][y] = n;
    }
    void revealCell(int x, int y) {
        if ((x >= 0) && (y >= 0) && (x <= i - 1) && (y <= j - 1)) {
            cell[x][y] = mem_cell[x][y];
        }
    }
    void revealSurroundingZero(int x, int y) {
        if (y < j - 1) {
            if (isZero(x, y + 1) && !isRevealed(x, y + 1)) {
                revealCell(x, y + 1);
                revealSurroundingZero(x, y + 1);
            }
        }
        if (x < i - 1) {
            if (isZero(x + 1, y) && !isRevealed(x + 1, y)) {
                revealCell(x + 1, y);
                revealSurroundingZero(x + 1, y);
            }
        }
        if (x > 0) {
            if (isZero(x - 1, y) && !isRevealed(x - 1, y)) {
                revealCell(x - 1, y);
                revealSurroundingZero(x - 1, y);
            }
        }
        if (y > 0) {
            if (isZero(x, y - 1) && !isRevealed(x, y - 1)) {
                revealCell(x, y - 1);
                revealSurroundingZero(x, y - 1);
            }
        }
        if ((x < i - 1) && (y < j - 1)) {
            if (isZero(x + 1, y + 1) && !isRevealed(x + 1, y + 1)) {
                revealCell(x + 1, y + 1);
                revealSurroundingZero(x + 1, y + 1);
            }
        }
        if ((x > 0) && (y < j - 1)) {
            if (isZero(x - 1, y + 1) && !isRevealed(x - 1, y + 1)) {
                revealCell(x - 1, y + 1);
                revealSurroundingZero(x - 1, y + 1);
            }
        }
        if ((y > 0) && (x < i - 1)) {
            if (isZero(x + 1, y - 1) && !isRevealed(x + 1, y - 1)) {
                revealCell(x + 1, y - 1);
                revealSurroundingZero(x + 1, y - 1);
            }
        }
        if ((y > 0) && (x > 0)) {
            if (isZero(x - 1, y - 1) && !isRevealed(x - 1, y - 1)) {
                revealCell(x - 1, y - 1);
                revealSurroundingZero(x - 1, y - 1);
            }
        }
    }
    void revealNearbyPositive(int x, int y) {
        if (y < j - 1) {
            if (isPositive(x, y + 1) && !isRevealed(x, y + 1)) {
                revealCell(x, y + 1);
            }
        }
        if (x < i - 1) {
            if (isPositive(x + 1, y) && !isRevealed(x + 1, y)) {
                revealCell(x + 1, y);
            }
        }
        if (x > 0) {
            if (isPositive(x - 1, y) && !isRevealed(x - 1, y)) {
                revealCell(x - 1, y);
            }
        }
        if (y > 0) {
            if (isPositive(x, y - 1) && !isRevealed(x, y - 1)) {
                revealCell(x, y - 1);
            }
        }
        if ((x < i - 1) && (y < j - 1)) {
            if (isPositive(x + 1, y + 1) && !isRevealed(x + 1, y + 1)) {
                revealCell(x + 1, y + 1);
            }
        }
        if ((x > 0) && (y < j - 1)) {
            if (!checkMine(x - 1, y + 1) && !isRevealed(x - 1, y + 1)) {
                revealCell(x - 1, y + 1);
            }
        }
        if ((y > 0) && (x < i - 1)) {
            if (isPositive(x + 1, y - 1) && !isRevealed(x + 1, y - 1)) {
                revealCell(x + 1, y - 1);
            }
        }
        if ((y > 0) && (x > 0)) {
            if (isPositive(x - 1, y - 1) && !isRevealed(x - 1, y - 1)) {
                revealCell(x - 1, y - 1);
            }
        }
    }
    void revealCellZero(int x, int y) {
        revealSurroundingZero(x, y);
        for (int a = 0; a < i; ++a) {
            for (int b = 0; b < j; ++b) {
                if (isZero(a, b) && isRevealed(a, b)) {
                    revealNearbyPositive(a, b);
                }
            }
        }
    }
    void flagCell(int x, int y) {
        if (!isRevealed(x, y)) {
            cell[x][y] = 11;
        }
    }
    void hitMine() {

    }
    void DEBUG_revealAll() {
        for (int a = 0; a < i; ++a) {
            for (int b = 0; b < j; ++b) {
                cell[a][b] = mem_cell[a][b];
            }
        }
    }
};

struct menu {
    sf::RectangleShape outer, lineNew;
    sf::Text textNew, textOption, textHighScore, textQuit;
    sf::Font fontConsola;
    menu() {
        outer.setSize(sf::Vector2f(1000, 232));
        outer.setPosition(sf::Vector2f(12, 524));
        outer.setFillColor(sf::Color::Black);
        outer.setOutlineThickness(4.f);
        outer.setOutlineColor(sf::Color::Green);
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
        lineNew.setSize(sf::Vector2f(40, 4));
        lineNew.setPosition(sf::Vector2f(188, 556));
        lineNew.setFillColor(sf::Color::Green);
    }
};

struct button {
    sf::RectangleShape GreenRect;
    button() {
        GreenRect.setSize(button_size);
        GreenRect.setFillColor(sf::Color::Black);
        GreenRect.setOutlineThickness(4.f);
        GreenRect.setOutlineColor(sf::Color::Green);
    }
    sf::Vector2f posButton(int x, int y) {
        return sf::Vector2f(24 + x * 204, 536 + y * 56);
    }
};

int main()
{
    srand(time(0));
    sf::RenderWindow game(sf::VideoMode(1024, 768), "Minesweeper");
    game.setFramerateLimit(60);
    sf::Texture b_texture;
    b_texture.loadFromMemory(tiles_png, tiles_png_len);
    sf::Sprite b_sprite;
    b_sprite.setTexture(b_texture);
    board b = board(9,9);
    menu m = menu();
    button btn = button();
    while (game.isOpen())
    {
        sf::Vector2i pos = sf::Mouse::getPosition(game);
        int bx = pos.x / cell_length;
        int by = pos.y / cell_length;
        sf::Event e;
        while (game.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                game.close();
            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::R) {
                    b.DEBUG_revealAll();
                }
                if (e.key.code == sf::Keyboard::N) {
                    b = board(32, 16);
                }
            }
            if (e.type == sf::Event::MouseButtonPressed) {
                if ((bx < b.i) && (by < b.j)) {
                    if (e.key.code == sf::Mouse::Left) {
                        b.revealCell(bx, by);
                        if (b.isZero(bx, by)) {
                            b.revealCellZero(bx, by);
                        }
                    }
                    if (e.key.code == sf::Mouse::Right) {
                        b.flagCell(bx, by);
                    }
                }
                if ((pos.x > 20) && (pos.x < 188) && (pos.y > 700) && (pos.y < 748)) {
                    if (e.key.code == sf::Mouse::Left) {
                        game.close();
                    }
                }
            }
        }
        game.clear();
        game.draw(m.outer);
        //game.draw(m.lineNew);
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 1; ++j) {
                btn.GreenRect.setPosition(btn.posButton(j, i));
                game.draw(btn.GreenRect);
            }
        }
        game.draw(m.textNew);
        game.draw(m.textOption);
        game.draw(m.textHighScore);
        game.draw(m.textQuit);
        for (int i = 0; i < b.i; i++) {
            for (int j = 0; j < b.j; j++) {
                b_sprite.setTextureRect(sf::IntRect(b.cell[i][j] * cell_length, 0, cell_length, cell_length));
                b_sprite.setPosition((i + 1) * cell_length - cell_length, (j + 1) * cell_length - cell_length);
                game.draw(b_sprite);
            }
        }
        game.display();
    }
    return 0;
}
