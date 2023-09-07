#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "board.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <time.h>

// Board logic

// Constructors
Board::Board() {
	width = 0;
	height = 0;
	bombCount = 0;
}

Board::Board(int width, int height, int bombCount) {
	this->width = width;
	this->height = height;
	this->bombCount = bombCount;
}

// Destructor
Board::~Board() {
    for (unsigned int i = 0; i < height; i++) {
        delete[] binaryBoard[i];
        delete[] tileList[i];
    }
}

// Copy assignment operator
Board& Board::operator=(const Board& rhs) {
    if (this != &rhs) {
        // delete old existing array
        for (unsigned int i = 0; i < height; i++) {
            delete[] binaryBoard[i];
            delete[] tileList[i];
        }

        // copy new stuff
        width = rhs.width;
        height = rhs.height;
        bombCount = rhs.bombCount;

        // allocate new array
        binaryBoard = new int* [height];
        for (unsigned int i = 0; i < height; i++)
            binaryBoard[i] = new int[width];

        // deep copy
        for (unsigned int i = 0; i < height; i++) {
            for (unsigned int j = 0; j < width; j++) {
                binaryBoard[i][j] = rhs.binaryBoard[i][j];
            }
        }
    }
    return *this;
}

vector<int> Board::GenerateRandomBomb() {
    vector<int> randomBombLocation;
    int index = 0;
    int random = 0;
    bool duplicate = false;

    // initialize random seed: 
    srand(time(NULL));

    while (index != bombCount) {
        // generate a random number between 0 and (bombCount - 1)
        random = rand() % (width * height);
        duplicate = false;
        for (unsigned int i = 0; i < randomBombLocation.size(); i++) {
            if (random == randomBombLocation[i])
                duplicate = true;
        }

        if (duplicate == false) {
            randomBombLocation.push_back(random);
            index++;
        }
    }
    return randomBombLocation;
}

void Board::GenerateBinary2DArray(vector<int> randomBombLocation) {
    // Declare memory block
    binaryBoard = new int*[height];

    for (unsigned int i = 0; i < height; i++)
        binaryBoard[i] = new int[width];

    // Set everything to zero
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            binaryBoard[i][j] = 0;
        }
    }
    
    // Place mines
    int row = 0;
    int column = 0;
    for (unsigned int i = 0; i < bombCount; i++) {
        row = randomBombLocation[i] / width;
        column = randomBombLocation[i] % width;
        binaryBoard[row][column] = 1;
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cout << binaryBoard[i][j] << " ";
        }
        cout << endl;
    }
}

// number of mines will be negative since 1 is already taken
void Board::NumberOfBombs() {
    int numMines = 0;
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            if (binaryBoard[i][j] == 0) {
                // top left edge case
                if (i == 0 && j == 0) {
                    if (binaryBoard[0][1] == 1)
                        numMines++;
                    if (binaryBoard[1][1] == 1)
                        numMines++;
                    if (binaryBoard[1][0] == 1)
                        numMines++;
                }

                // top right edge case
                else if (i == 0 && j == width - 1) {
                    if (binaryBoard[0][width - 2] == 1)
                        numMines++;
                    if (binaryBoard[1][width - 2] == 1)
                        numMines++;
                    if (binaryBoard[1][width - 1] == 1)
                        numMines++;
                }

                // bottom left edge case
                else if (i == height - 1 && j == 0) {
                    if (binaryBoard[height - 2][0] == 1)
                        numMines++;
                    if (binaryBoard[height - 2][1] == 1)
                        numMines++;
                    if (binaryBoard[height - 1][1] == 1)
                        numMines++;
                }

                // bottom right edge case
                else if (i == height - 1 && j == width - 1) {
                    if (binaryBoard[height - 1][width - 2] == 1)
                        numMines++;
                    if (binaryBoard[height - 2][width - 2] == 1)
                        numMines++;
                    if (binaryBoard[height - 2][width - 1] == 1)
                        numMines++;
                }

                // top row edge case
                else if (i == 0) {
                    if (binaryBoard[0][j - 1] == 1)
                        numMines++;
                    if (binaryBoard[0][j + 1] == 1)
                        numMines++;
                    if (binaryBoard[1][j - 1] == 1)
                        numMines++;
                    if (binaryBoard[1][j] == 1)
                        numMines++;
                    if (binaryBoard[1][j + 1] == 1)
                        numMines++;
                }

                // left column edge case
                else if  (j == 0) {
                    if (binaryBoard[i - 1][0] == 1)
                        numMines++;
                    if (binaryBoard[i - 1][1] == 1)
                        numMines++;
                    if (binaryBoard[i][1] == 1)
                        numMines++;
                    if (binaryBoard[i + 1][1] == 1)
                        numMines++;
                    if (binaryBoard[i + 1][0] == 1)
                        numMines++;
                }

                // right column edge case
                else if (j == width - 1) {
                    if (binaryBoard[i - 1][width - 1] == 1)
                        numMines++;
                    if (binaryBoard[i - 1][width - 2] == 1)
                        numMines++;
                    if (binaryBoard[i][width - 2] == 1)
                        numMines++;
                    if (binaryBoard[i + 1][width - 2] == 1)
                        numMines++;
                    if (binaryBoard[i + 1][width - 1] == 1)
                        numMines++;
                }

                // bottom row edge case
                else if (i == height - 1) {
                    if (binaryBoard[height - 1][j - 1] == 1)
                        numMines++;
                    if (binaryBoard[height - 1][j + 1] == 1)
                        numMines++;
                    if (binaryBoard[height - 2][j - 1] == 1)
                        numMines++;
                    if (binaryBoard[height - 2][j] == 1)
                        numMines++;
                    if (binaryBoard[height - 2][j + 1] == 1)
                        numMines++;
                }
                
                // Check everywhere!
                else {
                    if (binaryBoard[i - 1][j - 1] == 1)
                        numMines++;
                    if (binaryBoard[i - 1][j] == 1)
                        numMines++;
                    if (binaryBoard[i - 1][j + 1] == 1)
                        numMines++;
                    if (binaryBoard[i][j - 1] == 1)
                        numMines++;
                    if (binaryBoard[i][j + 1] == 1)
                        numMines++;
                    if (binaryBoard[i + 1][j - 1] == 1)
                        numMines ++;
                    if (binaryBoard[i + 1][j] == 1)
                        numMines++;
                    if (binaryBoard[i + 1][j + 1] == 1)
                        numMines++;
                }
                binaryBoard[i][j] = numMines * -1;
                numMines = 0;
            }
        }
    }

    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            cout << binaryBoard[i][j] << " ";
        }
        cout << endl;
    }
}

void Board::SetUpTiles() {
    // Declare memory block
    tileList = new Tile*[height];

    for (unsigned int i = 0; i < height; i++)
        tileList[i] = new Tile[width];

    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            // Set type and make hidden
            
            tileList[i][j].type = binaryBoard[i][j];
            tileList[i][j].hidden = true;
            tileList[i][j].flag = false;
            tileList[i][j].stay = false;

            //// Set up Pointers
            //// top left edge case
            if (i == 0 && j == 0) {
                tileList[i][j].adjacentTiles.push_back(&tileList[0][1]);
                tileList[j][j].adjacentTiles.push_back(&tileList[1][1]);
                tileList[i][j].adjacentTiles.push_back(&tileList[1][0]);
            }

            // top right left edge case
            else if (i == 0 && j == width - 1) {
                tileList[i][j].adjacentTiles.push_back(&tileList[0][width - 2]);
                tileList[i][j].adjacentTiles.push_back(&tileList[1][width - 2]);
                tileList[i][j].adjacentTiles.push_back(&tileList[1][width - 1]);
            }


            // bottom left edge case
            else if (i == height - 1 && j == 0) {
                tileList[i][j].adjacentTiles.push_back(&tileList[height - 2][0]);
                tileList[i][j].adjacentTiles.push_back(&tileList[height - 2][1]);
                tileList[i][j].adjacentTiles.push_back(&tileList[height - 1][1]);
            }

            // bottom right edge case
            else if (i == height - 1 && j == width - 1) {
                tileList[i][j].adjacentTiles.push_back(&tileList[height - 1][width - 2]);
                tileList[i][j].adjacentTiles.push_back(&tileList[height - 2][width - 2]);
                tileList[i][j].adjacentTiles.push_back(&tileList[height - 2][width - 1]);
            }

            // top row edge case
            else if (i == 0) {
                tileList[i][j].adjacentTiles.push_back(&tileList[0][j - 1]);
                tileList[i][j].adjacentTiles.push_back(&tileList[0][j + 1]);
                tileList[i][j].adjacentTiles.push_back(&tileList[1][j - 1]);
                tileList[i][j].adjacentTiles.push_back(&tileList[1][j]);
                tileList[i][j].adjacentTiles.push_back(&tileList[1][j + 1]);
            }

            // left column edge case
            else if (j == 0) {
                tileList[i][j].adjacentTiles.push_back(&tileList[i - 1][0]);
                tileList[i][j].adjacentTiles.push_back(&tileList[i - 1][1]);
                tileList[i][j].adjacentTiles.push_back(&tileList[i][1]);
                tileList[i][j].adjacentTiles.push_back(&tileList[i + 1][1]);
                tileList[i][j].adjacentTiles.push_back(&tileList[i + 1][0]);
            }

            // right column edge case
            else if (j == width - 1) {
                tileList[i][j].adjacentTiles.push_back(&tileList[i - 1][width - 1]);
                tileList[i][j].adjacentTiles.push_back(&tileList[i - 1][width - 2]);
                tileList[i][j].adjacentTiles.push_back(&tileList[i][width - 2]);
                tileList[i][j].adjacentTiles.push_back(&tileList[i + 1][width - 2]);
                tileList[i][j].adjacentTiles.push_back(&tileList[i + 1][width - 1]);
            }

            // bottom row edge case
            else if (i == height - 1) {
                tileList[i][j].adjacentTiles.push_back(&tileList[height - 1][j - 1]);
                tileList[i][j].adjacentTiles.push_back(&tileList[height - 1][j + 1]);
                tileList[i][j].adjacentTiles.push_back(&tileList[height - 2][j - 1]);
                tileList[i][j].adjacentTiles.push_back(&tileList[height - 2][j]);
                tileList[i][j].adjacentTiles.push_back(&tileList[height - 2][j + 1]);
            }

            // Check everywhere!
            else {
                tileList[i][j].adjacentTiles.push_back(&tileList[i - 1][j - 1]);
                tileList[i][j].adjacentTiles.push_back(&tileList[i - 1][j]);
                tileList[i][j].adjacentTiles.push_back(&tileList[i - 1][j + 1]);
                tileList[i][j].adjacentTiles.push_back(&tileList[i][j - 1]);
                tileList[i][j].adjacentTiles.push_back(&tileList[i][j + 1]);
                tileList[i][j].adjacentTiles.push_back(&tileList[i + 1][j - 1]);
                tileList[i][j].adjacentTiles.push_back(&tileList[i + 1][j]);
                tileList[i][j].adjacentTiles.push_back(&tileList[i + 1][j + 1]);
            }
        }
    }
}

void Board::RevealAround(Tile tile) {
    for (unsigned int i = 0; i < tile.adjacentTiles.size(); i++) {
        if (tile.adjacentTiles[i]->type == 0 && tile.adjacentTiles[i]->hidden == true && tile.adjacentTiles[i]->flag == false && tile.adjacentTiles[i]->stay == false) {
            tile.adjacentTiles[i]->hidden = false;
            RevealAround(*tile.adjacentTiles[i]);

        }
        if (tile.adjacentTiles[i]->flag == false && tile.adjacentTiles[i]->stay == false) {
            tile.adjacentTiles[i]->hidden = false;
        }
    }
    return;
}

void Board::InputFile(string fileName) {
    ifstream file;
    file.open(fileName);
    char sto;
    int count = 0;

    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            sto = file.get();
            if (sto == 49)
                count++;
            binaryBoard[i][j] = int(sto) - '0';
        }
        file.get();
    }

    bombCount = count;
    cout << "bombCount: " << bombCount << endl;

    file.close();
    NumberOfBombs();
    SetUpTiles();
}



// board info
//int width;
//int height;
//int bombCount;
//
//// Binary Board (dynamic 2d array of ints)
//int** binaryBoard;
//
// Tile list (dyamic 2d array of Tile)
//Tile** tileList;
