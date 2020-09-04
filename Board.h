#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <vector>
#include <map>
#include "Tile.h"
using namespace std;

class Board
{
public:
    Tile board[25][16];
    bool reset = false;
    bool debug = false;
    bool lose = false;
    int flagcount = 0;
    int numberofbombs = 0;
    vector<bool> br;

    map<string, sf::Texture> store;

    Board()
    {
        sf::Texture hide;
        hide.loadFromFile("images/tile_hidden.png");
        store.emplace("hiddentile",hide);

        sf::Texture rev;
        rev.loadFromFile("images/tile_revealed.png");
        store.emplace("revealed",rev);

        sf::Texture min;
        min.loadFromFile("images/mine.png");
        store.emplace("mine",min);

        sf::Texture f;
        f.loadFromFile("images/flag.png");
        store.emplace("flag",f);

        sf::Texture n1;
        n1.loadFromFile("images/number_1.png");
        store.emplace("1",n1);
        sf::Texture n2;
        n2.loadFromFile("images/number_2.png");
        store.emplace("2",n2);
        sf::Texture n3;
        n3.loadFromFile("images/number_3.png");
        store.emplace("3",n3);
        sf::Texture n4;
        n4.loadFromFile("images/number_4.png");
        store.emplace("4",n4);
        sf::Texture n5;
        n5.loadFromFile("images/number_5.png");
        store.emplace("5",n5);
        sf::Texture n6;
        n6.loadFromFile("images/number_6.png");
        store.emplace("6",n6);
        sf::Texture n7;
        n7.loadFromFile("images/number_7.png");
        store.emplace("7",n7);
        sf::Texture n8;
        n8.loadFromFile("images/number_8.png");
        store.emplace("8",n8);

        sf::Texture timer;
        timer.loadFromFile("images/digits.png");
        store.emplace("digits",timer);


        for(int i = 0; i < 25; i++)
        {
            for(int j = 0; j < 16; j++)
            {
                board[i][j].xc = i;
                board[i][j].yc = j;
                board[i][j].hidden.setTexture(store["hiddentile"]);
                (board[i][j].hidden).setPosition(i * 32, j * 32);
            }
        }

        Randomize();

        for(int i = 0; i < 25; i++)
        {
            for(int j = 0; j < 16; j++)
            {
                getNeighbors(i,j);
            }
        }

    }

    void Randomize()
    {
        int mines = 0;
        while(mines <= 49)
        {
            int randomx = rand() % 25;
            int randomy = rand() % 16;
            if(!board[randomx][randomy].hasmine)
            {
                board[randomx][randomy].hasmine = true;
                mines++;
            }
        }
    }

    void RevealTiles(sf::RenderWindow& windowRef, int i, int j)
    {
        if(!board[i][j].beenrevealed && !board[i][j].hasflag)
        {
            board[i][j].beenrevealed = true;
            br.push_back(true);
            board[i][j].revealed.setTexture(store["revealed"]);
            board[i][j].revealed.setPosition(32 * i, 32 * j);

            if(board[i][j].bombcount == 0)
            {
                for(int m = 0; m < board[i][j].neighbors.size(); m++)
                {
                    int xcoor = board[i][j].neighbors[m]->xc;
                    int ycoor = board[i][j].neighbors[m]->yc;
                    RevealTiles(windowRef, xcoor, ycoor);
                }
            }
            else
            {
                board[i][j].number.setTexture(store[to_string(board[i][j].bombcount)]);
                board[i][j].number.setPosition(32 * i, 32 * j);
                board[i][j].hasnum = true;
            }
        }
    }

    void getNeighbors(int i, int j)
    {
        // top left corner
        if(i - 1 >= 0 && j - 1 >= 0)
        {
            if(!board[i - 1][j - 1].hasmine)
                board[i][j].neighbors.push_back(&board[i-1][j-1]);
            else
                board[i][j].bombcount++;
        }
        //top of
        if(j - 1 >= 0)
        {
            if(!board[i][j - 1].hasmine)
                board[i][j].neighbors.push_back(&board[i][j-1]);
            else
                board[i][j].bombcount++;
        }
        //top right corner
        if(i + 1 < 25 && j - 1 >= 0)
        {
            if(!board[i + 1][j - 1].hasmine)
                board[i][j].neighbors.push_back(&board[i + 1][j - 1]);
            else
                board[i][j].bombcount++;
        }
        //left
        if(i - 1 >= 0)
        {
            if(!board[i - 1][j].hasmine)
                board[i][j].neighbors.push_back(&board[i - 1][j]);
            else
                board[i][j].bombcount++;
        }
        //right
        if(i + 1 < 25)
        {
            if(!board[i + 1][j].hasmine)
                board[i][j].neighbors.push_back(&board[i + 1][j]);
            else
                board[i][j].bombcount++;
        }
        //directly under
        if(j + 1 < 16)
        {
            if(!board[i][j + 1].hasmine)
                board[i][j].neighbors.push_back(&board[i][j+1]);
            else
                board[i][j].bombcount++;
        }
        //bottom left
        if(i - 1 >= 0 && j + 1 < 16)
        {
            if(!board[i - 1][j + 1].hasmine)
                board[i][j].neighbors.push_back(&board[i - 1][j + 1]);
            else
                board[i][j].bombcount++;
        }
        //bottom right
        if(i + 1 < 25 && j + 1 < 16)
        {
            if(!board[i + 1][j + 1].hasmine)
                board[i][j].neighbors.push_back(&board[i + 1][j + 1]);
            else
                board[i][j].bombcount++;
        }

    }

    void Draw(sf::RenderWindow& windowRef)
    {
        sf::RectangleShape rect {{800.0f, 88.0f}};
        rect.setPosition({0.f, 512.f });
        windowRef.draw(rect);

        for(int i = 0; i < 25; i++)
        {
            for(int j = 0; j < 16; j++)
            {
                if(!reset && !lose)
                {
                    if(!board[i][j].isclicked && !board[i][j].beenrevealed)
                        windowRef.draw(board[i][j].hidden);
                    if (board[i][j].hasmine && board[i][j].isclicked)
                    {
                        board[i][j].mine.setTexture(store["mine"]);
                        board[i][j].mine.setPosition(32 * i, 32 * j);
                        board[i][j].revealed.setTexture(store["revealed"]);
                        board[i][j].revealed.setPosition(32 * i, 32 * j);
                        windowRef.draw(board[i][j].revealed);
                        windowRef.draw(board[i][j].mine);
                        lose = true;

                    }
                    if (!board[i][j].hasmine && board[i][j].isclicked && !board[i][j].hasflag)
                    {
                        RevealTiles(windowRef,i,j);
                        for(int k = 0; k < 25; k++)
                        {
                            for(int l = 0; l < 16; l++)
                            {
                                if(board[k][l].beenrevealed && !board[k][l].hasmine)
                                {
                                    windowRef.draw(board[k][l].revealed);
                                }
                                if(board[k][l].hasnum)
                                {
                                    windowRef.draw(board[k][l].number);
                                }
                            }
                        }
                    }
                    if(board[i][j].hasflag)
                    {
                        windowRef.draw(board[i][j].hidden);
                        board[i][j].flag.setTexture(store["flag"]);
                        board[i][j].flag.setPosition(32 * i, 32 * j);
                        windowRef.draw(board[i][j].flag);
                        board[i][j].flagtouched = true;
                    }
                    if(!board[i][j].hasflag && board[i][j].flagtouched)
                    {
                        windowRef.draw(board[i][j].hidden);
                        board[i][j].flagtouched = false;
                    }

                }
                else
                {
                    windowRef.draw(board[i][j].hidden);
                    if(lose)
                    {
                        if(board[i][j].hasmine)
                        {
                            board[i][j].mine.setTexture(store["mine"]);
                            board[i][j].mine.setPosition(32*i,32*j);
                            windowRef.draw(board[i][j].mine);
                            flagcount = 0;
                        }
                    }
                    if(reset)
                    {
                        board[i][j].isclicked = false;
                        board[i][j].hasmine = false;
                        board[i][j].beenrevealed = false;
                        board[i][j].hasnum = false;
                        board[i][j].hasflag = false;
                        board[i][j].bombcount = 0;
                        board[i][j].flagtouched = false;
                        board[i][j].neighbors.clear();
                        br.clear();
                        flagcount = 0;
                        numberofbombs = 0;
                        debug = false;
                    }
                }

            }
        }

        if(reset)
        {
            Randomize();
            for(int i = 0; i < 25; i++)
            {
                for(int j = 0; j < 16; j++)
                {
                    getNeighbors(i,j);
                }
            }
        }

        if(debug)
        {
            for(int i = 0; i < 25; i ++)
            {
                for(int j = 0; j < 16; j++)
                {
                    if(board[i][j].hasmine)
                    {
                        board[i][j].mine.setTexture(store["mine"]);
                        board[i][j].mine.setPosition(32 * i, 32 * j);
                        windowRef.draw(board[i][j].mine);
                    }
                }
            }
        }


    }

    void DrawEnding(sf::RenderWindow& windowRef)
    {
        sf::Sprite smile;
        sf::Texture h;
        if(!lose)
            h.loadFromFile("images/face_happy.png");
        if(lose)
        {
            h.loadFromFile("images/face_lose.png");
        }

        if(br.size() == 400 - numberofbombs)
            h.loadFromFile("images/face_win.png");


        smile.setTexture(h);
        smile.setPosition(375,512);
        windowRef.draw(smile);
        sf::Sprite debugg;
        sf::Texture d;
        d.loadFromFile("images/debug.png");
        debugg.setTexture(d);
        debugg.setPosition(475,512);
        windowRef.draw(debugg);
        sf::Sprite test1;
        sf::Texture t1;
        t1.loadFromFile("images/test_1.png");
        test1.setTexture(t1);
        test1.setPosition(539,512);
        windowRef.draw(test1);
        sf::Sprite test2;
        sf::Texture t2;
        t2.loadFromFile("images/test_2.png");
        test2.setTexture(t2);
        test2.setPosition(603,512);
        windowRef.draw(test2);
        sf::Sprite test3;
        sf::Texture t3;
        t3.loadFromFile("images/test_3.png");
        test3.setTexture(t3);
        test3.setPosition(667,512);
        windowRef.draw(test3);


        int remmine = 50 - flagcount;

        sf::Sprite p1;
        p1.setPosition(0,512);
        sf::Sprite p2;
        p2.setPosition(21,512);
        sf::Sprite p3;
        p3.setPosition(42,512);

        if(remmine >= 0)
        {
            p1.setTexture(store["digits"]);
            p1.setTextureRect(sf::IntRect(0,0,21,32));
        }
        else
        {
            p1.setTexture(store["digits"]);
            p1.setTextureRect(sf::IntRect(210,0,21,32));
            remmine = -1 * remmine;
        }
        int unitdig = remmine % 10;
        int tendig = remmine / 10;
        p2.setTexture(store["digits"]);
        p2.setTextureRect(sf::IntRect(21 * tendig,0,21,32));
        p3.setTexture(store["digits"]);
        p3.setTextureRect(sf::IntRect(21 * unitdig,0,21,32));
        windowRef.draw(p1);
        windowRef.draw(p2);
        windowRef.draw(p3);
    }
};