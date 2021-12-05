#include "board.h"

board::board() {
    width = 0;
    length = 0;
    size = 0;
    countRevealedCells = 0;
    mines = 0;
    isFailure = false;
    isVictory = false;
    isFirstLeftClick = false;
    isGameRunning = false;
}
board::board(const int& x, const int& y, const int& z) {
    isGameRunning = true;
    width = x;
    length = y;
    size = x * y;
    mines = z;
    countRevealedCells = 0;
    mem_cell.assign(x, std::vector<int>(y, 0));
    cell.assign(x, std::vector<int>(y, 0));
    isFailure = false;
    isVictory = false;
    isFirstLeftClick = true;
    int count = 0;
    setMine(z, count);
    for (int a = 0; a < x; ++a) {
        for (int b = 0; b < y; ++b) {
            cell[a][b] = 10;
            if (!isMine(a, b)) {
                countSurroundingMines(a, b);
            }
        }
    }
}
void board::setMine(const int& mines, int &count) {
    for (int a = 0; a < width; ++a) {
        for (int b = 0; b < length; ++b) {
            if ((count < mines) && !isMine(a, b)) {
                if ((rand() % 10 + 1) == 1) {
                    mem_cell[a][b] = 9;
                    count++;
                }
            }
            if (mines == count) {
                break;
            }
        }
    }
    if (count < mines) {
        setMine(mines, count);
    }
}
void board::resetCellNum() {
    for (int a = 0; a < width; ++a) {
        for (int b = 0; b < length; ++b) {
            if (!isMine(a, b)) {
                countSurroundingMines(a, b);
            }
        }
    }
}
bool board::isMine(const int& x, const int& y) {
    if (mem_cell[x][y] == 9) {
        return true;
    }
    else {
        return false;
    }
}
bool board::isZero(const int& x, const int& y) {
    if (mem_cell[x][y] == 0) {
        return true;
    }
    else {
        return false;
    }
}
bool board::isRevealed(const int& x, const int& y) {
    if (cell[x][y] == 10) {
        return false;
    }
    else {
        return true;
    }
}
bool board::isPositive(const int& x, const int& y) {
    if ((mem_cell[x][y] >= 1) && (mem_cell[x][y] <= 8)) {
        return true;
    }
    else {
        return false;
    }
}
void board::countSurroundingMines(const int& x, const int& y) {
    int n = 0;
    if (y < length - 1) {
        if (isMine(x, y + 1)) {
            ++n;
        }
    }
    if (x < width - 1) {
        if (isMine(x + 1, y)) {
            ++n;
        }
    }
    if (x > 0) {
        if (isMine(x - 1, y)) {
            ++n;
        }
    }
    if (y > 0) {
        if (isMine(x, y - 1)) {
            ++n;
        }
    }
    if ((x < width - 1) && (y < length - 1)) {
        if (isMine(x + 1, y + 1)) {
            ++n;
        }
    }
    if ((x > 0) && (y < length - 1)) {
        if (isMine(x - 1, y + 1)) {
            ++n;
        }
    }
    if ((y > 0) && (x < width - 1)) {
        if (isMine(x + 1, y - 1)) {
            ++n;
        }
    }
    if ((y > 0) && (x > 0)) {
        if (isMine(x - 1, y - 1)) {
            ++n;
        }
    }
    mem_cell[x][y] = n;
}
void board::revealCell(const int& x, const int& y) {
    if ((x >= 0) && (y >= 0) && (x <= width - 1) && (y <= length - 1) && !isRevealed(x, y)) {
        cell[x][y] = mem_cell[x][y];
        countRevealedCells++;
    }
}
void board::revealSurroundingZero(const int& x, const int& y) {
    if (y < length - 1) {
        if (isZero(x, y + 1) && !isRevealed(x, y + 1)) {
            revealCell(x, y + 1);
            revealSurroundingZero(x, y + 1);
        }
    }
    if (x < width - 1) {
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
    if ((x < width - 1) && (y < length - 1)) {
        if (isZero(x + 1, y + 1) && !isRevealed(x + 1, y + 1)) {
            revealCell(x + 1, y + 1);
            revealSurroundingZero(x + 1, y + 1);
        }
    }
    if ((x > 0) && (y < length - 1)) {
        if (isZero(x - 1, y + 1) && !isRevealed(x - 1, y + 1)) {
            revealCell(x - 1, y + 1);
            revealSurroundingZero(x - 1, y + 1);
        }
    }
    if ((y > 0) && (x < width - 1)) {
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
void board::revealNearbyPositive(const int& x, const int& y) {
    if (y < length - 1) {
        if (isPositive(x, y + 1) && !isRevealed(x, y + 1)) {
            revealCell(x, y + 1);
        }
    }
    if (x < width - 1) {
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
    if ((x < width - 1) && (y < length - 1)) {
        if (isPositive(x + 1, y + 1) && !isRevealed(x + 1, y + 1)) {
            revealCell(x + 1, y + 1);
        }
    }
    if ((x > 0) && (y < length - 1)) {
        if (!isMine(x - 1, y + 1) && !isRevealed(x - 1, y + 1)) {
            revealCell(x - 1, y + 1);
        }
    }
    if ((y > 0) && (x < width - 1)) {
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
void board::revealCellZero(const int& x, const int& y) {
    revealSurroundingZero(x, y);
    for (int a = 0; a < width; ++a) {
        for (int b = 0; b < length; ++b) {
            if (isZero(a, b) && isRevealed(a, b)) {
                revealNearbyPositive(a, b);
            }
        }
    }
}
void board::flagCell(const int& x, const int& y) {
    if (!isRevealed(x, y)) {
        cell[x][y] = 11;
    }
}
bool board::isFlagged(const int& x, const int& y) {
    if (cell[x][y] == 11) {
        return true;
    }
    else {
        return false;
    }
}
void board::unflagCell(const int& x, const int& y) {
    if (isFlagged(x, y)) {
        cell[x][y] = 10;
    }
}
void board::swapMine(const int& x, const int& y) {
    int mx = rand() % width, my = rand() % length;
    if (isFirstLeftClick) {
        if (isMine(x, y)) {
            mem_cell[x][y] = 0;
            while ((mx == x) || (my == y) || isMine(mx, my)) {
                mx = rand() % width;
                my = rand() % length;
            }
            mem_cell[mx][my] = 9;
            resetCellNum();
        }
        isFirstLeftClick = false;
    }
}
bool board::endGame() {
    if ((isFailure) || (isVictory)) {
        return true;
    }
    return false;
}
void board::DEBUG_revealAll() {
    for (int a = 0; a < width; ++a) {
        for (int b = 0; b < length; ++b) {
            cell[a][b] = mem_cell[a][b];
        }
    }
}

int board::to_int(const std::string& str) {
    int result = 0;
    for (int i = 0; i < str.size(); ++i) {
        if (isdigit(str[i])) {
            result = result * 10 + (str[i] - '0');
        }
    }
    return result;
}

std::vector<int> board::to_vector_int(const std::string & str) {
    std::vector<int> converted_value;
    int last = 0, current = 0;
    for (int i = 1; i < str.size(); ++i) {
        if (str[i] == ' ') {
            last = current;
            current = i;
            converted_value.push_back(to_int(str.substr(last + 1, current - last)));
        }
    }
    return converted_value;
}

void board::edit_board(const int& value_type, const int& value, int& time) {
    switch (value_type) {
    case 0:
        time = value;
        break;
    case 1:
        width = value;
        break;
    case 2:
        length = value;
        break;
    case 3:
        mines = value;
        break;
    case 4:
        countRevealedCells = value;
        break;
    case 5:
        isFirstLeftClick = value;
        break;
    case 6:
        isVictory = value;
        break;
    case 7:
        isFailure = value;
        break;
    case 8:
        isGameRunning = value;
        break;
    default:
        break;
    }
}

void board::edit_board(const int& value_type, const std::string& value) {
    std::vector<int> converted_value = to_vector_int(value);
    int k = 0;
    switch (value_type) {
    case 9:
        mem_cell.resize(width, std::vector<int>(length));
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < length; j++) {
                mem_cell[i][j] = converted_value[k];
                k++;
            }
        }
        break;
    case 10:
        cell.resize(width, std::vector<int>(length));
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < length; j++) {
                cell[i][j] = converted_value[k];
                k++;
            }
        }
        break;
    default:
        break;
    }
}

void board::save_game(const int& time) {
    std::ofstream output("save.txt");
    if (output.is_open()) {
        output << "TIME " << time << "\n";
        output << "WIDTH " << width << "\n";
        output << "LENGTH " << length << "\n";
        output << "MINES " << mines << "\n";
        output << "COUNTREVEALEDCELLS " << countRevealedCells << "\n";
        output << "ISFIRSTLEFTCLICK " << isFirstLeftClick << " \n";
        output << "ISVICTORY " << isVictory << "\n";
        output << "ISFAILURE " << isFailure << "\n";
        output << "ISGAMERUNNING " << isGameRunning << "\n";
        output << "MEM_CELL  ";
        for (int i = 0; i < mem_cell.size(); ++i) {
            for (int j = 0; j < mem_cell[i].size(); ++j) {
                output << mem_cell[i][j] << " ";
            }
        }
        output << "\nCELL  ";
        for (int i = 0; i < cell.size(); ++i) {
            for (int j = 0; j < cell[i].size(); ++j) {
                output << cell[i][j] << " ";
            }
        }
        output.close();
    }
}

void board::load_game(int& time) {
    std::ifstream input("save.txt");
    std::string load_value;
    int itr_line = 0;
    if (input.is_open())
    {
        while (!input.eof()) {
            while (itr_line < 9) {
                input.ignore(20, ' ');
                std::getline(input, load_value);
                edit_board(itr_line, to_int(load_value), time);
                itr_line++;
            }
            while (itr_line < 11) {
                input.ignore(20, ' ');
                std::getline(input, load_value);
                edit_board(itr_line, load_value);
                itr_line++;
            }
        }
        input.close();
    }
}