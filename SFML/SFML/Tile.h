#pragma once
#include <vector>

using namespace std;

class Tile {
public:
	// Constructor
	Tile();
	Tile(int type, bool hidden, bool flag, bool stay);


	// Member Variables
	int type;
	bool hidden;
	bool flag;
	bool stay;
	vector<Tile*>adjacentTiles;
};