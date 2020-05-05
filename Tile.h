#ifndef TILE_H
#define TILE_H

#include <string>

enum Colour {
    F,
    R,
    Y,
    B,
    L,
    U
};

class Tile {
public:

    /**
     * Constructor / Destructor
     */
    Tile(Colour colour);
    ~Tile();

    /**
     * Returns tile pattern as 
     * its enum number
     */
    Colour getColour();

    /**
     * Return tile pattern as
     * a single char
     */
    char getChar();


private:

    Colour colour;

};

typedef Tile* TilePtr;

#endif //TILE_H
