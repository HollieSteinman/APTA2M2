#include <string>
#include <iostream>

#include "Tile.h"

Tile::Tile(Colour colour):
    colour(colour)
{
}

Tile::~Tile(){
    
}

Tile::Tile(){
    colour = E;
}

char Tile::getColour(){
    return colours[colour];
}

char Tile::getChar(){
    char toReturn = '.';

    if(colour != 6) {
        toReturn = colours[colour];
    }

    return toReturn;
}

void Tile::clear(){
    colour = E;
}