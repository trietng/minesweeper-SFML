#include <SFML/Graphics.hpp>
#include <ctime>
#include "tiles.h"
#include "consola.h"
#include "board.h"
const int cell_length = 32;
const sf::Vector2f button_size = sf::Vector2f(160, 40);

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
                        if (b.isFlagged(bx, by)) {
                            b.unflagCell(bx, by);
                        }
                        else {
                            b.flagCell(bx, by);
                        }
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
