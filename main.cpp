#include <SFML/Graphics.hpp>
#include <ctime>
#include "tiles.h"
#include "board.h"
#include "menu.h"
const int cell_length = 32;

int main() {
    srand(time(0));
    sf::RenderWindow game(sf::VideoMode(1024, 768), "Minesweeper");
    game.setFramerateLimit(60);
    sf::Texture b_texture;
    b_texture.loadFromMemory(tiles_png, tiles_png_len);
    sf::Sprite b_sprite;
    b_sprite.setTexture(b_texture);
    board b = board(9,9);
    menu m = menu();
    text txt = text();
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
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 1; ++j) {
                btn.GreenRect.setPosition(btn.posButton(j, i));
                game.draw(btn.GreenRect);
            }
        }
        game.draw(txt.textNew);
        game.draw(txt.textOption);
        game.draw(txt.textHighScore);
        game.draw(txt.textQuit);
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
