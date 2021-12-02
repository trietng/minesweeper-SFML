#include "game.h"

game::game() {
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(1024, 892), "Minesweeper", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    b_texture.loadFromMemory(tiles_png, tiles_png_len);
    b_sprite.setTexture(b_texture);
    deltaTime = 0;
    lastTime = 0;
    currentTime = 0;
    realTime = 0;
    isNewPressed = false; 
    isCustomPressed = false; 
    isModePressed = false;
    openNameDialog = false;
    while (window.isOpen())
    {
        sf::Vector2i pos = sf::Mouse::getPosition(window);
        int bx = pos.x / cell_length;
        int by = pos.y / cell_length;
        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed) {
                window.close();
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
                        isCustomPressed = false;
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
                    if (!isCustomPressed) {
                        isCustomPressed = true;
                    }
                    else {
                        isCustomPressed = false;
                    }
                }
                if (isCustomPressed) {
                    for (int i = 1; i < 4; ++i) {
                        if (btn.isOperatorButtonPressed(pos.x, pos.y, e, btn.posButton(4, i))) {
                            cval.edit_custom_value(i, false);
                        }
                        if (btn.isOperatorButtonPressed(pos.x, pos.y, e, btn.posButton(4.6, i))) {
                            cval.edit_custom_value(i, true);
                        }
                    }
                }
                
                if (btn.isButtonPressed(pos.x, pos.y, e, btn.posButton(0, 4))) {                             //Quit
                    window.close();
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
                }
            }
        }
        window.clear();
        //Clock starts
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
        window.draw(m.outer);
        window.draw(m.separator);
        //Draw save button
        btn.GreenRect.setPosition(btn.posButton(0, -1));
        window.draw(btn.GreenRect);
        window.draw(txt.textSave);
        //Draw timer
        btn.GreenRect.setPosition(btn.posButton(4, -1));
        window.draw(btn.GreenRect);
        txt.textTimer.setString(std::to_string(realTime));
        window.draw(txt.textTimer);
        //Draw gamemode menu
        if (isNewPressed) {
            for (double i = 1; i < 5; ++i) {
                btn.GreenRect.setPosition(btn.posButton(i, 0));
                window.draw(btn.GreenRect);
                txt.textGamemode.setPosition(txt.posText(i, 0));
                txt.textGamemode.setString(txt.GamemodeString(i));
                window.draw(txt.textGamemode);
            }
        }
        // Draw custom gamemode menu
        if (isCustomPressed) {
            for (double i = 1; i < 4; ++i) {
                btn.CustomGreenRect.setPosition(btn.posButton(3, i));
                window.draw(btn.CustomGreenRect);
                m.line40px.setPosition(btn.posButton(3.5, i));
                window.draw(m.line40px);
                m.line40px.setPosition(btn.posButton(3.696, i));
                window.draw(m.line40px);
                m.line40px.setPosition(btn.posButton(4.196, i));
                window.draw(m.line40px);
                m.line40px.setPosition(btn.posButton(4.5686, i));
                window.draw(m.line40px);
                txt.textCustomSetting.setString(txt.CustomSettingString(i));
                txt.textCustomSetting.setPosition(txt.posText(3, i));
                window.draw(txt.textCustomSetting);
                txt.textOperator.setString(txt.OperatorString(0));
                txt.textOperator.setPosition(txt.posText(4, i));
                window.draw(txt.textOperator);
                txt.textOperator.setString(txt.OperatorString(1));
                txt.textOperator.setPosition(txt.posText(4.6, i));
                window.draw(txt.textOperator);
            }
            txt.textCustomValue.setPosition(txt.posText(4.2, 1));
            txt.textCustomValue.setString(std::to_string(cval.customWidth));
            window.draw(txt.textCustomValue);
            txt.textCustomValue.setPosition(txt.posText(4.2, 2));
            txt.textCustomValue.setString(std::to_string(cval.customLength));
            window.draw(txt.textCustomValue);
            txt.textCustomValue.setPosition(txt.posText(4.2, 3));
            txt.textCustomValue.setString(std::to_string(cval.customMines));
            window.draw(txt.textCustomValue);
        }
        //Draw main menu buttons
        for (double i = 0; i < 5; ++i) {                                    
            btn.GreenRect.setPosition(btn.posButton(0, i));
            window.draw(btn.GreenRect);
            txt.textMainMenu.setPosition(txt.posText(0, i));
            txt.textMainMenu.setString(txt.MainMenuString(i));
            window.draw(txt.textMainMenu);
        }
        // Draw status button
        window.draw(btn.TriGreenRect);                                     
        // Draw victory or failure text
        if (b.isFailure) {                             
            txt.textEnd.setFillColor(sf::Color::Red);
            txt.textEnd.setPosition(txt.posText(1.8, -1.4));
            txt.textEnd.setString("GAME OVER!");
            window.draw(txt.textEnd);
        }
        if (b.isVictory) {
            txt.textEnd.setFillColor(sf::Color::Yellow);
            txt.textEnd.setPosition(txt.posText(2, -1.4));
            txt.textEnd.setString("VICTORY!");
            window.draw(txt.textEnd);
        }
        // draw name dialog
        if (openNameDialog) {
            window.draw(btn.DuoGreenRect);
            m.line40px.setPosition(btn.posButton(2.06, 0));
            window.draw(m.line40px);
            window.draw(txt.textName);
            window.draw(txt.textPlayer);
            if (playerInput.getSize() == 6) {
                std::cout << playerInput.toAnsiString() << "\n"; //demo text input
                playerInput.clear();
                txt.textPlayer.setString("");
                openNameDialog = false;
            }
        }
        //Draw board game
        for (double i = 0; i < b.width; ++i) {                                                                         //Draw cells
            for (double j = 0; j < b.length; ++j) {
                b_sprite.setTextureRect(sf::IntRect(b.cell[i][j] * cell_length, 0, cell_length, cell_length));
                b_sprite.setPosition(i * cell_length, j * cell_length);
                window.draw(b_sprite);
            }
        }
        window.display();
    }
}
