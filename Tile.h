#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct Tile
{
    int xc;
    int yc;
    //sprites
    bool isclicked;
    bool hasmine;
    bool beenrevealed;
    bool hasnum;
    bool hasflag;
    bool flagtouched;
    std::vector<Tile*> neighbors;
    int bombcount;


    sf::Sprite mine;
    sf::Sprite flag;
    sf::Sprite revealed;
    sf::Sprite hidden;
    sf::Sprite number;

    Tile()
    {
        beenrevealed = false;
        isclicked = false;
        hasmine = false;
        bombcount = 0;
        hasnum = false;
        hasflag = false;
        flagtouched = false;
    }

};