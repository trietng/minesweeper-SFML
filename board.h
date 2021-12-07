#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

struct board {
	std::vector<std::vector<int>> mem_cell, cell;
	int width, length, countRevealedCells, mines, size;
	bool isFirstLeftClick, isVictory, isFailure, isGameRunning;
	board();
	board(const int& x, const int& y, const int& z);
	void setMine(const int& mines, int &count);
	void resetCellNum();
	bool isMine(const int& x, const int& y);
	bool isZero(const int& x, const int& y);
	bool isRevealed(const int& x, const int& y);
	bool isPositive(const int& x, const int& y);
	void countSurroundingMines(const int& x, const int& y);
	void revealCell(const int& x, const int& y);
	void revealSurroundingZero(const int& x, const int& y);
	void revealNearbyPositive(const int& x, const int& y);
	void revealCellZero(const int& x, const int& y);
	void flagCell(const int& x, const int& y);
	bool isFlagged(const int& x, const int& y);
	void unflagCell(const int& x, const int& y);
	void swapMine(const int& x, const int& y);
	bool endGame();
	void DEBUG_revealAll();
	void DEBUG_winGame();
	int to_int(const std::string& str);
	std::vector<int> to_vector_int(const std::string& str);
	void edit_board(const int& value_type, const int& value, int& time);
	void edit_board(const int& value_type, const std::string& value);
	void save_game(const int& time);
	void load_game(int& time);
};