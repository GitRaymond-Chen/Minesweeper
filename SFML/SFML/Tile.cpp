#include "Tile.h"

// Constructor
Tile::Tile() {
	type = 0;
	hidden = true;
	flag = true;
	stay = false;
}

Tile::Tile(int type, bool hidden, bool flag, bool stay){
	this->type = type;
	this->hidden = hidden;
	this->flag = flag;
	this->stay = stay;
}
