#ifndef TILE_H
#define TILE_H

#include <string>

class Tile {
public:

    //  Constructor / Destructor
    Tile(std::string pattern);
    ~Tile();

    //  Returns pattern of tile
    std::string getPattern();


private:

    std::string pattern;

};

#endif //TILE_H
