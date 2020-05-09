#include <string>

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

Colour Tile::getColour(){
    return colour;
}

char Tile::getChar(){
    char toReturn = '.';

    if (getColour() == F){
        toReturn = 'F';
    } else if (getColour() == R){
        toReturn = 'R';
    } else if (getColour() == Y){
        toReturn = 'Y';
    } else if (getColour() == B){
        toReturn = 'B';
    } else if (getColour() == L){
        toReturn = 'L';
    } else if (getColour() == U){
        toReturn = 'U';
    }

    return toReturn;
}

void Tile::clear(){
    colour = E;
}