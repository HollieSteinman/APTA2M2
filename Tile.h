#ifndef TILE_H
#define TILE_H

#include <string>

enum Colour {
    F,
    R,
    Y,
    B,
    L,
    U,
    E
};

class Tile {
public:

    /**
     * Constructor / Destructor
     */
    Tile(Colour colour);
    ~Tile();

    /**
     * Default constructor to prevent segfault
     */
    Tile();

    /**
     * Returns tile colour as a char
     */
    char getColourChar();

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

    /**
     * For destructive purposes
     */
    void clear();


private:

    Colour colour;
    char colours[7] = {'F','R','Y','B','L','U','E'};

};

typedef Tile* TilePtr;

#endif //TILE_H
