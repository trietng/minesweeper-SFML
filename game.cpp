#include "game.h"

control::control() {
    isNewPressed = false;
    isCustomPressed = false;
    isModePressed = false;
    openNameDialog = false;
    isHighscoresPressed = false;
    isOptionsPressed = false;
    colorState = false; //true if color, false if default (green)
    gamemode = -1;
}

game::game() {
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(1024, 892), "Minesweeper", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    b_texture_default.loadFromMemory(tiles_png, tiles_png_len);
    b_texture_color.loadFromMemory(tiles_color_jpg, tiles_color_jpg_len);
    b_sprite.setTexture(b_texture_default);
    deltaTime = 0;
    lastTime = 0;
    currentTime = 0;
    realTime = 0;
    while (window.isOpen()) {
        sf::Vector2i pos = sf::Mouse::getPosition(window);
        int bx = pos.x / cell_length;
        int by = pos.y / cell_length;
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                window.close();
            }
            if (txt.isSplash) {
                if (e.type == sf::Event::KeyPressed) {
                    if (e.key.code == sf::Keyboard::Enter) {
                        txt.isSplash = false;
                    }
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
                    }
                }
                if (!ctrl.openNameDialog) {
                    if (btn.isButtonPressed(pos.x, pos.y, e, btn.posButton(0, 0))) {
                        if (!ctrl.isNewPressed) {
                            ctrl.isNewPressed = true;
                        }
                        else {
                            ctrl.isCustomPressed = false;
                            ctrl.isNewPressed = false;
                        }
                    }
                    if ((ctrl.isNewPressed) && (btn.isButtonPressed(pos.x, pos.y, e, btn.posButton(1, 0)))) {        //Easy
                        b = board(9, 9, 10);
                        ctrl = control();
                        ctrl.isModePressed = true;
                        ctrl.gamemode = 0;
                    }
                    if ((ctrl.isNewPressed) && (btn.isButtonPressed(pos.x, pos.y, e, btn.posButton(2, 0)))) {        //Medium
                        b = board(16, 16, 40);
                        ctrl = control();
                        ctrl.isModePressed = true;
                        ctrl.gamemode = 1;
                    }
                    if ((ctrl.isNewPressed) && (btn.isButtonPressed(pos.x, pos.y, e, btn.posButton(3, 0)))) {        //Hard
                        b = board(32, 16, 99);
                        ctrl = control();
                        ctrl.isModePressed = true;
                        ctrl.gamemode = 2;
                    }
                    if ((ctrl.isNewPressed) && (btn.isButtonPressed(pos.x, pos.y, e, btn.posButton(4, 0)))) {        //Custom
                        if (!ctrl.isCustomPressed) {
                            ctrl.isCustomPressed = true;
                        }
                        else {
                            ctrl.isCustomPressed = false;
                        }
                    }
                    if (ctrl.isCustomPressed) {
                        ctrl.isOptionsPressed = false;
                        for (int i = 1; i < 4; ++i) {
                            if (btn.isOperatorButtonPressed(pos.x, pos.y, e, btn.posButton(3.5, i))) {
                                cval.edit_custom_value(i, 0);
                            }
                            if (btn.isOperatorButtonPressed(pos.x, pos.y, e, btn.posButton(3.7, i))) {
                                cval.edit_custom_value(i, 1);
                            }
                            if (btn.isOperatorButtonPressed(pos.x, pos.y, e, btn.posButton(4.392, i))) {
                                cval.edit_custom_value(i, 2);
                            }
                            if (btn.isOperatorButtonPressed(pos.x, pos.y, e, btn.posButton(4.59, i))) {
                                cval.edit_custom_value(i, 3);
                            }
                        }
                        if (btn.isPlayCustomButtonPressed(pos.x, pos.y, e, btn.posButton(3, 4))) {
                            b = board(cval.customWidth, cval.customLength, cval.customMines);
                            ctrl.gamemode = 3;
                            ctrl.isModePressed = true;
                            ctrl.isCustomPressed = true;
                        }
                    }
                    if (btn.isButtonPressed(pos.x, pos.y, e, btn.posButton(0, -1))) {
                        sl.save_game(b, realTime);
                    }
                    if (btn.isButtonPressed(pos.x, pos.y, e, btn.posButton(0, 1))) {
                        ctrl = control();
                        clock.restart();
                        sl.load_game(b, realTime);
                    }
                    if (btn.isButtonPressed(pos.x, pos.y, e, btn.posButton(0, 2))) {
                        ctrl.isNewPressed = false;
                        ctrl.isCustomPressed = false;
                        if (!ctrl.isOptionsPressed) {
                            ctrl.isOptionsPressed = true;
                        }
                        else {
                            ctrl.isOptionsPressed = false;
                        }
                    }
                    if (ctrl.isOptionsPressed && btn.isButtonPressed(pos.x, pos.y, e, btn.posButton(1, 2))) {
                        ctrl.isCustomPressed = false;
                        if (!ctrl.colorState) {
                            ctrl.colorState = true;
                            txt.textOptions[0].setString(txt.OptionsString(1));
                            b_sprite.setTexture(b_texture_color);
                        }
                        else {
                            ctrl.colorState = false;
                            txt.textOptions[0].setString(txt.OptionsString(0));
                            b_sprite.setTexture(b_texture_default);
                        }
                    }
                    if (ctrl.isOptionsPressed && btn.isPlayCustomButtonPressed(pos.x, pos.y, e, btn.posButton(2, 2))) {
                        hscr.delete_score();
                        //txt.textHighscores
                    }
                    if (btn.isButtonPressed(pos.x, pos.y, e, btn.posButton(0, 3))) {
                        if (!ctrl.isHighscoresPressed) {
                            ctrl = control();
                            ctrl.isHighscoresPressed = true;
                            realTime = 0;
                            hscr.load_score();
                            txt.textHighscores[0][0].setString("Easy");
                            for (int i = 0; i < std::min((int)hscr.easy.size(), 7); ++i) {
                                txt.textHighscores[0][i + 1].setString(std::to_string(i + 1) + ". " + hscr.easy[i].playerName + " " + std::to_string(hscr.easy[i].point));
                            }
                            txt.textHighscores[1][0].setString("Medium");
                            for (int i = 0; i < std::min((int)hscr.medium.size(), 7); ++i) {
                                txt.textHighscores[1][i + 1].setString(std::to_string(i + 1) + ". " + hscr.medium[i].playerName + " " + std::to_string(hscr.medium[i].point));
                            }
                            txt.textHighscores[2][0].setString("Hard");
                            for (int i = 0; i < std::min((int)hscr.hard.size(), 7); ++i) {
                                txt.textHighscores[2][i + 1].setString(std::to_string(i + 1) + ". " + hscr.hard[i].playerName + " " + std::to_string(hscr.hard[i].point));
                            }
                            b = board();
                        }
                        else {
                            ctrl.isHighscoresPressed = false;
                        }
                    }
                }
                if (btn.isButtonPressed(pos.x, pos.y, e, btn.posButton(0, 4))) {                             //Quit
                    window.close();
                }
            }
            if (b.isVictory && ctrl.gamemode != 3) {
                if (e.type == sf::Event::TextEntered) {
                    if (playerInput.getSize() < 6) {
                        if (e.text.unicode > 32 && e.text.unicode < 127) {
                            playerInput += e.text.unicode;
                            txt.textPlayer.setString(playerInput);
                        }
                        if ((e.text.unicode == '\b') && (playerInput.getSize() != 0)) {
                            playerInput.erase(playerInput.getSize() - 1, 1);
                            txt.textPlayer.setString(playerInput);
                        }
                    }
                }
            }
        }
        window.clear();
        //Clock starts
        if (b.isGameRunning) {                                                                              //Game is running
            if (ctrl.isModePressed) {
                clock.restart();
                realTime = 0;
                ctrl.isNewPressed = false;
                ctrl.isCustomPressed = false;
                ctrl.isModePressed = false;
            }
            deltaTime = clock.getElapsedTime().asSeconds();
            lastTime = currentTime;
            currentTime = deltaTime;
            if (currentTime > lastTime) {
                realTime++;
            }
            if (b.mines == b.size - b.countRevealedCells) {                                     //Victory
                b.isGameRunning = false;
                if (!b.isFailure) {
                    b.isVictory = true;
                    if (ctrl.gamemode != 3) {
                        ctrl.isNewPressed = false;
                        ctrl.isOptionsPressed = false;
                        ctrl.openNameDialog = true;
                    }
                }
            }
        }
        //Draw splash screen
        if (txt.isSplash) {
            window.draw(txt.textTitle);
            window.draw(txt.textAuthor1);
            window.draw(txt.textAuthor2);
            window.draw(txt.textPressKey);
        }
        else {
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
            if (ctrl.isNewPressed) {
                for (int i = 1; i < 5; ++i) {
                    btn.GreenRect.setPosition(btn.posButton(i, 0));
                    window.draw(btn.GreenRect);
                    window.draw(txt.textGamemode[i - 1]);
                }
            }
            // Draw custom gamemode menu
            if (ctrl.isCustomPressed) {
                for (double i = 1; i < 4; ++i) {
                    btn.CustomGreenRect.setPosition(btn.posButton(3, i));
                    window.draw(btn.CustomGreenRect);
                    m.line40px.setPosition(btn.posButton(3.5, i));
                    window.draw(m.line40px);
                    m.line40px.setPosition(btn.posButton(3.696, i));
                    window.draw(m.line40px);
                    m.line40px.setPosition(btn.posButton(3.892, i));
                    window.draw(m.line40px);
                    m.line40px.setPosition(btn.posButton(4.392, i));
                    window.draw(m.line40px);
                    m.line40px.setPosition(btn.posButton(4.59, i));
                    window.draw(m.line40px);
                    txt.textCustomSetting.setString(txt.CustomSettingString(i));
                    txt.textCustomSetting.setPosition(txt.posText(3, i));
                    window.draw(txt.textCustomSetting);
                    txt.textOperator.setString(txt.OperatorString(0));
                    txt.textOperator.setPosition(txt.posText(3.48, i));
                    window.draw(txt.textOperator);
                    txt.textOperator.setString(txt.OperatorString(1));
                    txt.textOperator.setPosition(txt.posText(3.7, i));
                    window.draw(txt.textOperator);
                    txt.textOperator.setString(txt.OperatorString(2));
                    txt.textOperator.setPosition(txt.posText(4.4, i));
                    window.draw(txt.textOperator);
                    txt.textOperator.setString(txt.OperatorString(3));
                    txt.textOperator.setPosition(txt.posText(4.5686, i));
                    window.draw(txt.textOperator);
                }
                //display custom values
                txt.textCustomValue.setPosition(txt.posText(4.02, 1));
                txt.textCustomValue.setString(std::to_string(cval.customWidth));
                window.draw(txt.textCustomValue);
                txt.textCustomValue.setPosition(txt.posText(4.02, 2));
                txt.textCustomValue.setString(std::to_string(cval.customLength));
                window.draw(txt.textCustomValue);
                txt.textCustomValue.setPosition(txt.posText(4.02, 3));
                txt.textCustomValue.setString(std::to_string(cval.customMines));
                window.draw(txt.textCustomValue);
                //display "Play"
                btn.CustomGreenRect.setPosition(btn.posButton(3, 4));
                window.draw(btn.CustomGreenRect);
                window.draw(txt.textPlayCustom);
            }
            //Draw main menu buttons
            for (int i = 0; i < 5; ++i) {
                btn.GreenRect.setPosition(btn.posButton(0, i));
                window.draw(btn.GreenRect);
                window.draw(txt.textMainMenu[i]);
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
            if ((ctrl.openNameDialog) && (ctrl.gamemode != 3)) {
                btn.DuoGreenRect.setPosition(btn.posButton(1, 0));
                window.draw(btn.DuoGreenRect);
                m.line40px.setPosition(btn.posButton(2.06, 0));
                window.draw(m.line40px);
                window.draw(txt.textName);
                window.draw(txt.textPlayer);
                if (playerInput.getSize() == 6) {
                    hscr.save_score(ctrl.gamemode, hscr.calc_point(ctrl.gamemode, realTime), playerInput.toAnsiString());
                    playerInput.clear();
                    txt.textPlayer.setString("");
                    ctrl.openNameDialog = false;
                }
            }
            // draw OPTIONS
            if (ctrl.isOptionsPressed) {
                btn.GreenRect.setPosition(btn.posButton(1, 2));
                window.draw(btn.GreenRect);
                window.draw(txt.textOptions[0]);
                btn.DuoGreenRect.setPosition(btn.posButton(2, 2));
                window.draw(btn.DuoGreenRect);
                window.draw(txt.textOptions[1]);
            }
            // draw highscores display
            if (ctrl.isHighscoresPressed) {
                window.draw(btn.HSGreenRect);
                window.draw(txt.textHighscores[0][0]);
                for (int i = 0; i < hscr.easy.size(); ++i) {
                    window.draw(txt.textHighscores[0][i + 1]);
                }
                window.draw(txt.textHighscores[1][0]);
                for (int i = 0; i < hscr.medium.size(); ++i) {
                    window.draw(txt.textHighscores[1][i + 1]);
                }
                window.draw(txt.textHighscores[2][0]);
                for (int i = 0; i < hscr.hard.size(); ++i) {
                    window.draw(txt.textHighscores[2][i + 1]);
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
        }

        window.display();
    }
}