#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <vector>


class Board {
public:
	// Constructors
	Board();
	Board(int width, int height, int mineCount);

	// Destructor
	~Board();

	// Copy assignment operator
	Board& operator=(const Board& rhs);

	vector<int> GenerateRandomBomb();
	void GenerateBinary2DArray(vector<int> randomBombLocation);
	void NumberOfBombs();
	void SetUpTiles();

	void RevealAround(Tile tile);
	void InputFile(string fileName);


	// board info
	int width;
	int height;
	int bombCount;

	// Binary Board (dynamic 2d array of ints)
	int** binaryBoard;

	// Tile list (dyamic 2d array of Tile)
	Tile** tileList;

};