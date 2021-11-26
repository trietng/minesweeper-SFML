#pragma once
#include <vector>

struct board {
	std::vector<std::vector<int>> mem_cell, cell;
	int width, length;
	board();
	board(int x, int y, int z);
	void setMine(int mines, int &count);
	bool checkMine(int x, int y);
	bool isZero(int x, int y);
	bool isRevealed(int x, int y);
	bool isPositive(int x, int y);
	void setCellNum(int x, int y);
	void revealCell(int x, int y);
	void revealSurroundingZero(int x, int y);
	void revealNearbyPositive(int x, int y);
	void revealCellZero(int x, int y);
	void flagCell(int x, int y);
	bool isFlagged(int x, int y);
	void unflagCell(int x, int y);
	void DEBUG_revealAll();
};