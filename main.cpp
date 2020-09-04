#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include <array>
#include "Board.h"
using namespace std;


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");

    //======== CREATING THE BOARD =============//
    Board game;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right)
            {
                if(event.mouseButton.x >= 0 && event.mouseButton.x <= 800 &&
                   event.mouseButton.y <= 512 && event.mouseButton.y >= 0)
                {
                    //game.board[event.mouseButton.x / 32][event.mouseButton.y / 32].isclicked = true;
                    game.board[event.mouseButton.x / 32][event.mouseButton.y / 32].hasflag = !game.board[event.mouseButton.x / 32][event.mouseButton.y / 32].hasflag;
                    if(game.board[event.mouseButton.x / 32][event.mouseButton.y / 32].hasflag)
                        game.flagcount++;
                    else
                        game.flagcount--;
                }
            }


            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {

                // if smiley face clicked
                if(event.mouseButton.x >= 375 && event.mouseButton.x <= 439 &&
                   event.mouseButton.y <= 576 && event.mouseButton.y >= 512)
                {
                    game.reset = true;
                }

                // if tile clicked
                if(event.mouseButton.x >= 0 && event.mouseButton.x <= 800 &&
                   event.mouseButton.y <= 512 && event.mouseButton.y >= 0)
                {
                    if(!game.board[event.mouseButton.x / 32][event.mouseButton.y / 32].hasflag)
                    {
                        game.board[event.mouseButton.x / 32][event.mouseButton.y / 32].isclicked = true;
                    }
                }

                // if debug clicked
                if(event.mouseButton.x >= 475 && event.mouseButton.x <= 539 &&
                   event.mouseButton.y <= 576 && event.mouseButton.y >= 512)
                {
                    game.debug = !game.debug;
                }

                // if test 1 clicked
                if(event.mouseButton.x >= 539 && event.mouseButton.x <= 603 &&
                   event.mouseButton.y <= 576 && event.mouseButton.y >= 512)
                {
                    ifstream file("boards/testboard1.brd");
                    game.br.clear();
                    game.flagcount = 0;
                    game.numberofbombs = 0;
                    for(int j = 0; j < 16; j++)
                    {
                        for (int i = 0; i < 25; i++)
                        {
                            //
                            game.board[i][j].isclicked = false;
                            game.board[i][j].hasmine = false;
                            game.board[i][j].beenrevealed = false;
                            game.board[i][j].hasnum = false;
                            game.board[i][j].hasflag = false;
                            game.board[i][j].bombcount = 0;
                            game.board[i][j].flagtouched = false;
                            game.board[i][j].neighbors.clear();
                            //

                            char y;
                            char o = '1';
                            file >> y;

                            if(y == o)
                            {
                                game.board[i][j].hasmine = true;
                                game.numberofbombs++;
                            }
                            else
                                game.board[i][j].hasmine = false;
                        }
                    }
                    for(int i = 0; i < 25; i++)
                    {
                        for(int j = 0; j < 16; j++)
                        {
                            game.getNeighbors(i,j);
                        }
                    }
                }
                // if test 2 clicked
                if(event.mouseButton.x >= 603 && event.mouseButton.x <= 669 &&
                   event.mouseButton.y <= 576 && event.mouseButton.y >= 512)
                {
                    ifstream file("boards/testboard2.brd");
                    game.br.clear();
                    game.flagcount = 0;
                    game.numberofbombs = 0;
                    for(int j = 0; j < 16; j++)
                    {
                        for (int i = 0; i < 25; i++)
                        {
                            //
                            game.board[i][j].isclicked = false;
                            game.board[i][j].hasmine = false;
                            game.board[i][j].beenrevealed = false;
                            game.board[i][j].hasnum = false;
                            game.board[i][j].hasflag = false;
                            game.board[i][j].bombcount = 0;
                            game.board[i][j].flagtouched = false;
                            game.board[i][j].neighbors.clear();
                            //
                            char y;
                            char o = '1';
                            file >> y;

                            if(y == o)
                            {
                                game.board[i][j].hasmine = true;
                                game.numberofbombs++;
                            }
                            else
                                game.board[i][j].hasmine = false;
                        }
                    }
                    for(int i = 0; i < 25; i++)
                    {
                        for(int j = 0; j < 16; j++)
                        {
                            game.getNeighbors(i,j);
                        }
                    }
                }
                // if test 3 clicked
                if(event.mouseButton.x >= 667 && event.mouseButton.x <= 731 &&
                   event.mouseButton.y <= 576 && event.mouseButton.y >= 512)
                {
                    ifstream file("boards/testboard3.brd");
                    game.br.clear();
                    game.flagcount = 0;
                    game.numberofbombs = 0;

                    for(int j = 0; j < 16; j++)
                    {
                        for (int i = 0; i < 25; i++)
                        {
                            //
                            game.board[i][j].isclicked = false;
                            game.board[i][j].hasmine = false;
                            game.board[i][j].beenrevealed = false;
                            game.board[i][j].hasnum = false;
                            game.board[i][j].hasflag = false;
                            game.board[i][j].bombcount = 0;
                            game.board[i][j].flagtouched = false;
                            game.board[i][j].neighbors.clear();
                            //

                            char y;
                            char o = '1';
                            file >> y;

                            if(y == o)
                            {
                                game.board[i][j].hasmine = true;
                                game.numberofbombs++;
                            }
                            else
                                game.board[i][j].hasmine = false;
                        }
                    }
                    for(int i = 0; i < 25; i++)
                    {
                        for(int j = 0; j < 16; j++)
                        {
                            game.getNeighbors(i,j);
                        }
                    }
                }
            }

        }

        window.clear();
        game.Draw(window);
        game.DrawEnding(window);
        window.display();

        if(game.reset)
        {
            game.reset = false;
            game.lose = false;
        }
    }

    return 0;
}
