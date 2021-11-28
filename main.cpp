#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
#include "tiles.h"
#include "board.h"
#include "menu.h"
const int cell_length = 32;
using namespace std;

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
    int deltaTime = 0, lastTime = 0, currentTime = 0, realTime = 0;
    sf::Clock clock;
    sf::String playerInput;
    bool isNewPressed = false, isCustomPressed = false, isModePressed = false, openNameDialog = false;
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
                if (e.key.code == sf::Keyboard::D) {
                    b = board(5, 5, 1);
                }
            }
            if (e.type == sf::Event::MouseButtonPressed) {
                if ((bx < b.width) && (by < b.length)) {
                    if (!b.endGame()) {
                        if (e.key.code == sf::Mouse::Left) {                    
                            if (!b.isFlagged(bx, by)) {
                                if (b.isFirstLeftClick) {
                                    b.swapMine(bx, by);
                                }
                                b.revealCell(bx, by);
                                if (b.isMine(bx, by)) {
                                    b.isFailure = true;                                                     //Hit a mine
                                    b.isGameRunning = false;
                                }
                                if (b.isZero(bx, by)) {
                                    b.revealCellZero(bx, by);
                                }
                            }
                        }
                        if (e.key.code == sf::Mouse::Right) {                                               //Flagging
                            if (b.isFlagged(bx, by)) {
                                b.unflagCell(bx, by);
                            }
                            else {
                                b.flagCell(bx, by);
                            }

                        }
                        if (b.mines == b.size - b.countRevealedCells) {                                     //Victory
                            b.isGameRunning = false;
                            if (!b.isFailure) {
                                b.isVictory = true;
                                openNameDialog = true;
                            }
                        }
                    }
                }
                if (btn.isButtonPressed(pos.x, pos.y, e, btn.posButton(0, 0))) {
                    if (!isNewPressed) {
                        isNewPressed = true;
                    }
                    else {
                        isNewPressed = false;
                    }
                }
                if ((isNewPressed) && (btn.isButtonPressed(pos.x, pos.y, e, btn.posButton(1, 0)))) {        //Easy
                    b = board(9, 9, 10);
                    isModePressed = true;
                }
                if ((isNewPressed) && (btn.isButtonPressed(pos.x, pos.y, e, btn.posButton(2, 0)))) {        //Medium
                    b = board(16, 16, 40);
                    isModePressed = true;
                }
                if ((isNewPressed) && (btn.isButtonPressed(pos.x, pos.y, e, btn.posButton(3, 0)))) {        //Hard
                    b = board(32, 16, 99);
                    isModePressed = true;
                }
                if ((isNewPressed) && (btn.isButtonPressed(pos.x, pos.y, e, btn.posButton(4, 0)))) {        //Custom

                }
                if (btn.isButtonPressed(pos.x, pos.y, e, btn.posButton(0,4))) {                             //Quit
                    game.close();
                }
            }
            if (b.isVictory) {
                if (e.type == sf::Event::TextEntered) {
                    if (playerInput.getSize() < 6) {
                        if (e.text.unicode > 32 && e.text.unicode < 127) {
                            playerInput += e.text.unicode;
                            txt.textPlayer.setString(playerInput);
                        }
                    }
                }/*
                if (playerInput.getSize() == 6) {
                    std::cout << playerInput.toAnsiString() << "\n"; //demo text input
                    playerInput.clear();
                    txt.textPlayer.setString("");
                    b.isVictory = false;
                }*/
            }
        }
        game.clear();
        if (b.isGameRunning) {                                                                              //Game is running
            if (isModePressed) {
                clock.restart();
                isNewPressed = false;
                isModePressed = false;
            }
            deltaTime = clock.getElapsedTime().asSeconds();
            lastTime = currentTime;
            currentTime = deltaTime;
            if (currentTime > lastTime) {
                realTime = deltaTime;
            }
        }
        //Draw menu outline
        game.draw(m.outer);
        game.draw(m.separator);

        //Draw save button
        btn.GreenRect.setPosition(btn.posButton(0, -1));
        game.draw(btn.GreenRect);
        game.draw(txt.textSave);

        //Draw time
        btn.GreenRect.setPosition(btn.posButton(4, -1));
        game.draw(btn.GreenRect);
        txt.textTimer.setString(std::to_string(realTime));
        game.draw(txt.textTimer);

        //Draw gamemode menu
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

        for (int i = 0; i < 5; ++i) {                                    //Draw menu buttons
            btn.GreenRect.setPosition(btn.posButton(0, i));
            game.draw(btn.GreenRect);
        }
        game.draw(txt.textNew);
        game.draw(txt.textResume);
        game.draw(txt.textOption);
        game.draw(txt.textHighScore);
        game.draw(txt.textQuit);
                                                                 
        game.draw(btn.TriGreenRect);                                     // Draw status button
                                                                 
        if (b.isFailure) {                                               // Draw victory or failure text
            txt.textEnd.setFillColor(sf::Color::Red);
            txt.textEnd.setPosition(txt.posText(1.8, -1.4));
            txt.textEnd.setString("GAME OVER!");
            game.draw(txt.textEnd);
        }
        if (b.isVictory) {
            txt.textEnd.setFillColor(sf::Color::Yellow);
            txt.textEnd.setPosition(txt.posText(2, -1.4));
            txt.textEnd.setString("VICTORY!");
            game.draw(txt.textEnd);
        }
        if (openNameDialog) {
            game.draw(btn.DuoGreenRect);
            m.line40px.setPosition(btn.posButton(2.06, 0));
            game.draw(m.line40px);
            game.draw(txt.textName);
            game.draw(txt.textPlayer);
            if (playerInput.getSize() == 6) {
                std::cout << playerInput.toAnsiString() << "\n"; //demo text input
                playerInput.clear();
                txt.textPlayer.setString("");
                openNameDialog = false;
            }
        }
        for (int i = 0; i < b.width; i++) {                                                                         //Draw cells
            for (int j = 0; j < b.length; j++) {
                b_sprite.setTextureRect(sf::IntRect(b.cell[i][j] * cell_length, 0, cell_length, cell_length));
                b_sprite.setPosition(i * cell_length, j * cell_length);
                game.draw(b_sprite);
            }
        }
        game.display();
    }
    return 0;
}
