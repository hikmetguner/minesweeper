#include <algorithm>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#pragma once
class Table
{
	public:
		Table(int row, int col);
		~Table();

		int* hiddenTiles;
		int* currentTiles;

		int row;
		int col;
		int bombCount;
		int currentFlag;

		std::vector<int> flagged;
		std::vector<int> bomb;

		bool check(int n);
		bool win() { return flagged == bomb; };

		int open(int x, int y);

		void flag(int x, int y);
		void print();
		void createBombs(int bombCount, int exclude);
		void fillNumberTiles();
		void openEmpty(int x, int y, int from_x = -32, int from_y = -32);

		
};
