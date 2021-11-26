#include <SFML/Graphics.hpp>
#include <ctime>
#include "tiles.h"
#include "board.h"
#include "menu.h"
const int cell_length = 32;

int main() {
    srand(time(0));
    sf::RenderWindow game(sf::VideoMode(1024, 892), "Minesweeper", sf::Style::Titlebar | sf::Style::Close);
    game.setFramerateLimit(60);
    sf::Texture b_texture;
    b_texture.loadFromMemory(tiles_png, tiles_png_len);
    sf::Sprite b_sprite;
    b_sprite.setTexture(b_texture);
    board b = board();
    menu m = menu();
    text txt = text();
    button btn = button();
    bool isNewPressed = false, isCustomPressed = false;
    while (game.isOpen())
    {
        sf::Vector2i pos = sf::Mouse::getPosition(game);
        int bx = pos.x / cell_length;
        int by = pos.y / cell_length;
        sf::Event e;
        while (game.pollEvent(e))
        {
            if (e.type == sf::Event::Closed) {
                game.close();
            }
            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::R) {
                    b.DEBUG_revealAll();
                }
            }
            if (e.type == sf::Event::MouseButtonPressed) {
                if ((bx < b.width) && (by < b.length)) {
                    if (e.key.code == sf::Mouse::Left) {
                        if (!b.isFlagged(bx, by)) {
                            b.revealCell(bx, by);
                            if (b.isZero(bx, by)) {
                                b.revealCellZero(bx, by);
                            }
                        }
                    }
                    if (e.key.code == sf::Mouse::Right) {       //Flagging
                        if (b.isFlagged(bx, by)) {
                            b.unflagCell(bx, by);
                        }
                        else {
                            b.flagCell(bx, by);
                        }
                    }
                }
                if (btn.isButtonPressed(pos.x, pos.y, e, btn.posButton(0, 0))) {
                    isNewPressed = true;
                }
                if ((isNewPressed) && (btn.isButtonPressed(pos.x, pos.y, e, btn.posButton(1, 0)))) {        //Easy
                    b = board(9, 9);
                    //clear menu
                    //isNewPressed = false;
                }
                if ((isNewPressed) && (btn.isButtonPressed(pos.x, pos.y, e, btn.posButton(2, 0)))) {        //Medium
                    b = board(16, 16);
                }
                if ((isNewPressed) && (btn.isButtonPressed(pos.x, pos.y, e, btn.posButton(3, 0)))) {        //Hard
                    b = board(32, 16);
                }
                if (btn.isButtonPressed(pos.x, pos.y, e, btn.posButton(0,4))) {                             //Quit
                    game.close();
                }
            }
        }
        game.clear();
        game.draw(m.outer);
        game.draw(m.separator);
        //draw save button
        btn.GreenRect.setPosition(btn.posButton(0, -1));
        game.draw(btn.GreenRect);
        game.draw(txt.textSave);
        //draw gamemode menu
        if (isNewPressed) {
            for (int i = 1; i < 5; ++i) {
                btn.GreenRect.setPosition(btn.posButton(i, 0));
                game.draw(btn.GreenRect);
            }
            game.draw(txt.textEasy);
            game.draw(txt.textMedium);
            game.draw(txt.textHard);
            game.draw(txt.textCustom);
        }
        for (int i = 0; i < 5; ++i) {
            btn.GreenRect.setPosition(btn.posButton(0, i));
            game.draw(btn.GreenRect);
        }
        game.draw(txt.textNew);
        game.draw(txt.textResume);
        game.draw(txt.textOption);
        game.draw(txt.textHighScore);
        game.draw(txt.textQuit);
        for (int i = 0; i < b.width; i++) {
            for (int j = 0; j < b.length; j++) {
                b_sprite.setTextureRect(sf::IntRect(b.cell[i][j] * cell_length, 0, cell_length, cell_length));
                b_sprite.setPosition((i + 1) * cell_length - cell_length, (j + 1) * cell_length - cell_length);
                game.draw(b_sprite);
            }
        }
        game.display();
    }
    return 0;
}
