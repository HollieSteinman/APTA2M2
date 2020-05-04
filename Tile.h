#ifndef TILE_H
#define TILE_H

#include <string>

class Tile {
public:

    //  Constructor / Destructor
    Tile(char colour);
    ~Tile();

    //  Returns pattern of tile
    char getColour();


private:

    char colour;

};

#endif //TILE_H
