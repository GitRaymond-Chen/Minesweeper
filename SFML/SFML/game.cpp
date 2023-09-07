#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "Tile.h"
#include "board.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// SFML stuff
int main()
{   
    unordered_map<string, sf::Texture> textures;
    textures["debug"].loadFromFile("images/debug.png");
    textures["face_happy"].loadFromFile("images/face_happy.png");
    textures["face_lose"].loadFromFile("images/face_lose.png");
    textures["face_win"].loadFromFile("images/face_win.png");
    textures["flag"].loadFromFile("images/flag.png");
    textures["mine"].loadFromFile("images/mine.png");
    textures["number_1"].loadFromFile("images/number_1.png");
    textures["number_2"].loadFromFile("images/number_2.png");
    textures["number_3"].loadFromFile("images/number_3.png");
    textures["number_4"].loadFromFile("images/number_4.png");
    textures["number_5"].loadFromFile("images/number_5.png");
    textures["number_6"].loadFromFile("images/number_6.png");
    textures["number_7"].loadFromFile("images/number_7.png");
    textures["number_8"].loadFromFile("images/number_8.png");
    textures["test_1"].loadFromFile("images/test_1.png");
    textures["test_2"].loadFromFile("images/test_2.png");
    textures["test_3"].loadFromFile("images/test_3.png");
    textures["hidden"].loadFromFile("images/tile_hidden.png");
    textures["revealed"].loadFromFile("images/tile_revealed.png");
    textures["digit_0"].loadFromFile("images/digits.png", sf::IntRect(0, 0, 21, 32));
    textures["digit_1"].loadFromFile("images/digits.png", sf::IntRect(21, 0, 21, 32));
    textures["digit_2"].loadFromFile("images/digits.png", sf::IntRect(42, 0, 21, 32));
    textures["digit_3"].loadFromFile("images/digits.png", sf::IntRect(63, 0, 21, 32));
    textures["digit_4"].loadFromFile("images/digits.png", sf::IntRect(84, 0, 21, 32));
    textures["digit_5"].loadFromFile("images/digits.png", sf::IntRect(105, 0, 21, 32));
    textures["digit_6"].loadFromFile("images/digits.png", sf::IntRect(126, 0, 21, 32));
    textures["digit_7"].loadFromFile("images/digits.png", sf::IntRect(147, 0, 21, 32));
    textures["digit_8"].loadFromFile("images/digits.png", sf::IntRect(168, 0, 21, 32));
    textures["digit_9"].loadFromFile("images/digits.png", sf::IntRect(189, 0, 21, 32));
    textures["digit_negative"].loadFromFile("images/digits.png", sf::IntRect(210, 0, 21, 32));
    
    sf::Sprite Hidden;
    Hidden.setTexture(textures.at("hidden"));
    sf::Sprite Reveal;
    Reveal.setTexture(textures.at("revealed"));
    sf::Sprite Happy;
    Happy.setTexture(textures.at("face_happy"));
    sf::Sprite Lose;
    Lose.setTexture(textures.at("face_lose"));
    sf::Sprite Win;
    Win.setTexture(textures.at("face_win"));
    sf::Sprite Debug;
    Debug.setTexture(textures.at("debug"));
    sf::Sprite Test1;
    Test1.setTexture(textures.at("test_1"));
    sf::Sprite Test2;
    Test2.setTexture(textures.at("test_2"));
    sf::Sprite Test3;
    Test3.setTexture(textures.at("test_3"));
    sf::Sprite Flag;
    Flag.setTexture(textures.at("flag"));
    sf::Sprite Mine;
    Mine.setTexture(textures.at("mine"));
    sf::Sprite Number1;
    Number1.setTexture(textures.at("number_1"));
    sf::Sprite Number2;
    Number2.setTexture(textures.at("number_2"));
    sf::Sprite Number3;
    Number3.setTexture(textures.at("number_3"));
    sf::Sprite Number4;
    Number4.setTexture(textures.at("number_4"));
    sf::Sprite Number5;
    Number5.setTexture(textures.at("number_5"));
    sf::Sprite Number6;
    Number6.setTexture(textures.at("number_6"));
    sf::Sprite Number7;
    Number7.setTexture(textures.at("number_7"));
    sf::Sprite Number8;
    Number8.setTexture(textures.at("number_8"));

    sf::Sprite Digit0;
    Digit0.setTexture(textures.at("digit_0"));
    sf::Sprite Digit1;
    Digit1.setTexture(textures.at("digit_1"));
    sf::Sprite Digit2;
    Digit2.setTexture(textures.at("digit_2"));
    sf::Sprite Digit3;
    Digit3.setTexture(textures.at("digit_3"));
    sf::Sprite Digit4;
    Digit4.setTexture(textures.at("digit_4"));
    sf::Sprite Digit5;
    Digit5.setTexture(textures.at("digit_5"));
    sf::Sprite Digit6;
    Digit6.setTexture(textures.at("digit_6"));
    sf::Sprite Digit7;
    Digit7.setTexture(textures.at("digit_7"));
    sf::Sprite Digit8;
    Digit8.setTexture(textures.at("digit_8"));
    sf::Sprite Digit9;
    Digit9.setTexture(textures.at("digit_9"));
    sf::Sprite Negative;
    Negative.setTexture(textures.at("digit_negative"));
    

    // Assign Texture to sprite
    ifstream file;
    string line;
    int width;
    int height;
    int bombCount;
    int flagCount = 0;
    bool reset = true;
    bool lose = false;
    bool win = false;
    bool debug = false;
    bool test1 = false;
    bool test2 = false;
    bool test3 = false;

    file.open("boards/config.cfg");
    getline(file, line);
    width = stoi(line);
    getline(file, line);
    height = stoi(line);
    getline(file, line);
    bombCount = stoi(line);
    file.close();

    Board board(width, height, bombCount);

    sf::RenderWindow window(sf::VideoMode(width * 32, (height * 32) + 100), "Minesweeper", sf::Style::Titlebar | sf::Style::Close);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                double x = event.mouseButton.x / 32.0;
                double y = event.mouseButton.y / 32.0;

                if (event.mouseButton.button == sf::Mouse::Right) {
                    if (x <= width && y <= height) {
                        // Place flag on board
                        if (board.tileList[int(y)][int(x)].flag == false && lose == false && win == false && board.tileList[int(y)][int(x)].hidden == true) {
                            board.tileList[int(y)][int(x)].flag = true;
                            board.tileList[int(y)][int(x)].stay = true;
                            flagCount++;
                        
                        }
                        // Place remove flag on board
                        else if (lose == false && win == false && board.tileList[int(y)][int(x)].hidden == true) {
                            board.tileList[int(y)][int(x)].flag = false;
                            flagCount--;
                        }
                    }
                }
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (x <= width && y <= height) {
                        // if click on a mine
                        if (board.tileList[int(y)][int(x)].type == 1 && board.tileList[int(y)][int(x)].flag == false && win == false) {
                            lose = true;
                        }
                        // if click on a tile that is not a mine
                        if (board.tileList[int(y)][int(x)].type != 1 && board.tileList[int(y)][int(x)].flag == false && lose == false) {
                            board.tileList[int(y)][int(x)].hidden = false;
                        }
                    }

                    // Reset
                    if ((x > (width * 1.0 / 2.0) - 1 && x < width * 1.0 / 2.0 + 1) && (y > height && y < height + 2)) {
                        reset = true;
                        lose = false;
                        win = false;
                    }

                    // Debug
                    if ((x > (width * 1.0 / 2.0) + 3 && x < (width * 1.0 / 2.0) + 5) && (y > height && y < height + 2) && lose == false && win == false) {
                        if (debug) {
                            debug = false;
                        }
                        else {
                            debug = true;
                        }
                        win = false;
                    }
                    // Test1
                    if ((x > (width * 1.0 / 2.0) + 5 && x < (width * 1.0 / 2.0) + 7) && (y > height && height + 2)) {
                        
                        test1 = true;
                        win = false;
                        lose = false;
                    }
                    // Test2
                    if ((x > (width * 1.0 / 2.0) + 7 && x < (width * 1.0 / 2.0) + 9) && (y > height && y < height + 2)) {
                        test2 = true;
                        win = false;
                        lose = false;
                    }
                    // Test3
                    if ((x > (width * 1.0 / 2.0) + 9 && x < (width * 1.0 / 2.0) + 11) && (y > height && y < height + 2)) {
                        test3 = true;
                        win = false;
                        lose = false;
                    }
                }
            }
        }
        
        window.clear(sf::Color::White);
        int x = 0;
        int y = 0;

        // reset Board
        if (reset) {
            flagCount = 0;
            board.bombCount = bombCount;
            win = false;
            vector<int> sto = board.GenerateRandomBomb();
            board.GenerateBinary2DArray(sto);
            cout << endl << endl;
            board.NumberOfBombs();
            cout << endl << endl;
            board.SetUpTiles();
            for (unsigned int i = 0; i < width; i++) {
                for (unsigned int j = 0; j < height; j++) {
                    Hidden.setPosition(sf::Vector2f(i * 32, j * 32));
                    window.draw(Hidden);
                    reset = false;
                }
            }
        }

        // draw board and flag
        for (unsigned int i = 0; i < width; i++) {
            for (unsigned int j = 0; j < height; j++) {
                if (board.tileList[j][i].flag == true) {
                    Flag.setPosition(sf::Vector2f(i * 32, j * 32));
                    Hidden.setPosition(sf::Vector2f(i * 32, j * 32));
                    window.draw(Hidden);
                    window.draw(Flag);
                }
                else {
                    Hidden.setPosition(sf::Vector2f(i * 32, j * 32));
                    window.draw(Hidden);
                }
            }
        }

        

        // reveal Tile
        for (unsigned int i = 0; i < width; i++) {
            for (unsigned int j = 0; j < height; j++) {
                if (board.tileList[j][i].hidden == false) {
                    Reveal.setPosition(sf::Vector2f(i * 32, j * 32));
                    window.draw(Reveal);
                    if (board.tileList[j][i].type == -1) {
                        Number1.setPosition(sf::Vector2f(i * 32, j * 32));
                        window.draw(Number1);
                    }
                    else if (board.tileList[j][i].type == -2) {
                        Number2.setPosition(sf::Vector2f(i * 32, j * 32));
                        window.draw(Number2);
                    }
                    else if (board.tileList[j][i].type == -3) {
                        Number3.setPosition(sf::Vector2f(i * 32, j * 32));
                        window.draw(Number3);
                    }
                    else if (board.tileList[j][i].type == -4) {
                        Number4.setPosition(sf::Vector2f(i * 32, j * 32));
                        window.draw(Number4);
                    }
                    else if (board.tileList[j][i].type == -5) {
                        Number5.setPosition(sf::Vector2f(i * 32, j * 32));
                        window.draw(Number5);
                    }
                    else if (board.tileList[j][i].type == -6) {
                        Number6.setPosition(sf::Vector2f(i * 32, j * 32));
                        window.draw(Number6);
                    }
                    else if (board.tileList[j][i].type == -7) {
                        Number7.setPosition(sf::Vector2f(i * 32, j * 32));
                        window.draw(Number7);
                    }
                    else if (board.tileList[j][i].type == -8) {
                        Number8.setPosition(sf::Vector2f(i * 32, j * 32));
                        window.draw(Number8);
                    }
                    else if (board.tileList[j][i].type == 0) {
                        board.RevealAround(board.tileList[j][i]);
                    }
                }
            }
        }


        // draw Face
        if (lose) {
            Lose.setPosition(sf::Vector2f(width * 16 - 32, height * 32));
            window.draw(Lose);
        }
        else if (win) {
            Win.setPosition(sf::Vector2f(width * 16 - 32, height * 32));
            window.draw(Win);
        }
        else {
            Happy.setPosition(sf::Vector2f(width * 16 - 32, height * 32));
            window.draw(Happy);
        }

        // draw Debug
        Debug.setPosition(sf::Vector2f(width * 16 + 96, height * 32));
        window.draw(Debug);

        // draw Test1
        Test1.setPosition(sf::Vector2f(width * 16 + 160, height * 32));
        window.draw(Test1);

        // draw Test2
        Test2.setPosition(sf::Vector2f(width * 16 + 224, height * 32));
        window.draw(Test2);

        // draw Test3
        Test3.setPosition(sf::Vector2f(width * 16 + 288, height * 32));
        window.draw(Test3);


        if (test1 == true) {
            flagCount = 0;
            board.InputFile("boards/testboard1.brd");
            test1 = false;
        }

        if (test2 == true) {
            flagCount = 0;
            board.InputFile("boards/testboard2.brd");
            test2 = false;
        }

        if (test3 == true) {
            flagCount = 0;
            board.InputFile("boards/testboard3.brd");
            test3 = false;
        }
       
        if (debug) {
            // draw mines
            for (unsigned int i = 0; i < width; i++) {
                for (unsigned int j = 0; j < height; j++) {
                    if (board.tileList[j][i].type == 1) {
                        Mine.setPosition(sf::Vector2f(i * 32, j * 32));
                        Hidden.setPosition(sf::Vector2f(i * 32, j * 32));
                        window.draw(Hidden);
                        window.draw(Mine);
                    }
                }
            }
        }
        if (win) {
            flagCount = board.bombCount;
            for (unsigned int i = 0; i < width; i++) {
                for (unsigned int j = 0; j < height; j++) {
                    if (board.tileList[j][i].type == 1) {
                        Flag.setPosition(sf::Vector2f(i * 32, j * 32));
                        Hidden.setPosition(sf::Vector2f(i * 32, j * 32));
                        window.draw(Hidden);
                        window.draw(Flag);
                    }
                }
            }
        }
        if (lose) {
            for (unsigned int i = 0; i < width; i++) {
                for (unsigned int j = 0; j < height; j++) {
                    if (board.tileList[j][i].type == 1) {
                        Mine.setPosition(sf::Vector2f(i * 32, j * 32));
                        Hidden.setPosition(sf::Vector2f(i * 32, j * 32));
                        window.draw(Hidden);
                        window.draw(Mine);
                    }
                }
            }
        }
        
        // draw mines remaing counter
        int flagRemaining = board.bombCount - flagCount;
        if (flagRemaining < 0) {
            Negative.setPosition(sf::Vector2f(0, height * 32));
            window.draw(Negative);
            flagRemaining *= -1;
        }
        // hundreds place
        if (flagRemaining / 100 == 0) {
            Digit0.setPosition(sf::Vector2f(21, height * 32));
            window.draw(Digit0);
        }
        if (flagRemaining / 100 == 1) {
            Digit1.setPosition(sf::Vector2f(21, height * 32));
            window.draw(Digit1);
        }
        if (flagRemaining / 100 == 2) {
            Digit2.setPosition(sf::Vector2f(21, height * 32));
            window.draw(Digit2);
        }
        if (flagRemaining / 100 == 3) {
            Digit3.setPosition(sf::Vector2f(21, height * 32));
            window.draw(Digit3);
        }
        if (flagRemaining / 100 == 4) {
            Digit4.setPosition(sf::Vector2f(21, height * 32));
            window.draw(Digit4);
        }
        if (flagRemaining / 100 == 5) {
            Digit5.setPosition(sf::Vector2f(21, height * 32));
            window.draw(Digit5);
        }
        if (flagRemaining / 100 == 6) {
            Digit6.setPosition(sf::Vector2f(21, height * 32));
            window.draw(Digit6);
        }
        if (flagRemaining / 100 == 7) {
            Digit7.setPosition(sf::Vector2f(21, height * 32));
            window.draw(Digit7);
        }
        if (flagRemaining / 100 == 8) {
            Digit8.setPosition(sf::Vector2f(21, height * 32));
            window.draw(Digit8);
        }
        if (flagRemaining / 100 == 9) {
            Digit9.setPosition(sf::Vector2f(21, height * 32));
            window.draw(Digit9);
        }

        // tens place
        if ((flagRemaining / 10) % 10 == 0) {
            Digit0.setPosition(sf::Vector2f(42, height * 32));
            window.draw(Digit0);
        }
        if ((flagRemaining / 10) % 100 == 1) {
            Digit1.setPosition(sf::Vector2f(42, height * 32));
            window.draw(Digit1);
        }
        if ((flagRemaining / 10) % 10 == 2) {
            Digit2.setPosition(sf::Vector2f(42, height * 32));
            window.draw(Digit2);
        }
        if ((flagRemaining / 10) % 10 == 3) {
            Digit3.setPosition(sf::Vector2f(42, height * 32));
            window.draw(Digit3);
        }
        if ((flagRemaining / 10) % 10 == 4) {
            Digit4.setPosition(sf::Vector2f(42, height * 32));
            window.draw(Digit4);
        }
        if ((flagRemaining / 10) % 10 == 5) {
            Digit5.setPosition(sf::Vector2f(42, height * 32));
            window.draw(Digit5);
        }
        if ((flagRemaining / 10) % 10 == 6) {
            Digit6.setPosition(sf::Vector2f(42, height * 32));
            window.draw(Digit6);
        }
        if ((flagRemaining / 10) % 10 == 7) {
            Digit7.setPosition(sf::Vector2f(42, height * 32));
            window.draw(Digit7);
        }
        if ((flagRemaining / 10) % 10 == 8) {
            Digit8.setPosition(sf::Vector2f(42, height * 32));
            window.draw(Digit8);
        }
        if ((flagRemaining / 10) % 10 == 9) {
            Digit9.setPosition(sf::Vector2f(42, height * 32));
            window.draw(Digit9);
        }

        // ones place
        if (flagRemaining % 10 == 0) {
            Digit0.setPosition(sf::Vector2f(63, height * 32));
            window.draw(Digit0);
        }
        if (flagRemaining % 10 == 1) {
            Digit1.setPosition(sf::Vector2f(63, height * 32));
            window.draw(Digit1);
        }
        if (flagRemaining % 10 == 2) {
            Digit2.setPosition(sf::Vector2f(63, height * 32));
            window.draw(Digit2);
        }
        if (flagRemaining % 10 == 3) {
            Digit3.setPosition(sf::Vector2f(63, height * 32));
            window.draw(Digit3);
        }
        if (flagRemaining % 10 == 4) {
            Digit4.setPosition(sf::Vector2f(63, height * 32));
            window.draw(Digit4);
        }
        if (flagRemaining % 10 == 5) {
            Digit5.setPosition(sf::Vector2f(63, height * 32));
            window.draw(Digit5);
        }
        if (flagRemaining % 10 == 6) {
            Digit6.setPosition(sf::Vector2f(63, height * 32));
            window.draw(Digit6);
        }
        if (flagRemaining % 10 == 7) {
            Digit7.setPosition(sf::Vector2f(63, height * 32));
            window.draw(Digit7);
        }
        if (flagRemaining % 10 == 8) {
            Digit8.setPosition(sf::Vector2f(63, height * 32));
            window.draw(Digit8);
        }
        if (flagRemaining % 10 == 9) {
            Digit9.setPosition(sf::Vector2f(63, height * 32));
            window.draw(Digit9);
        }

        // Check Win
        int revealed = 0;
        for (unsigned int i = 0; i < width; i++) {
            for (unsigned int j = 0; j < height; j++) {
                if (board.tileList[j][i].hidden == false)
                    revealed++;
            }
        }
        if (((width * height) - revealed) == board.bombCount) {
            win = true;
        }

        flagRemaining *= -1;

        window.display();
    }

    return 0;
}
