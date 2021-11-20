#include <board.h>

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
        mem_cell.assign(x, std::vector<int>(y, 0));
        cell.assign(x, std::vector<int>(y, 0));
        setMine();
        for (int a = 0; a < x; ++a) {
            for (int b = 0; b < y; ++b) {
                cell[a][b] = 10;
                if (!checkMine(a, b)) {
                    setCellNum(a, b);
                }
            }
        }
    }
    void setMine() {
        for (int a = 0; a < i; ++a) {
            for (int b = 0; b < j; ++b) {
                if ((rand() % 5 + 1) == 1) {
                    mem_cell[a][b] = 9;
                }
                else {
                    mem_cell[a][b] = 0;
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
    bool isFlagged(int x, int y) {
        if (cell[x][y] == 11) {
            return true;
        }
        else {
            return false;
        }
    }
    void unflagCell(int x, int y) {
        if (isFlagged(x, y)) {
            cell[x][y] = 10;
        }
    }
    void DEBUG_revealAll() {
        for (int a = 0; a < i; ++a) {
            for (int b = 0; b < j; ++b) {
                cell[a][b] = mem_cell[a][b];
            }
        }
    }
};