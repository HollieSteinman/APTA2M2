#ifndef FACTORY_H
#define FACTORY_H

#include "Tile.h"

class Factory {

public:

    //  Constructor / Destructor
    Factory();
    ~Factory();

    //  Returns tiles in the factory
    Tile* getTiles();

    //  Sets the tiles in the factory
    void setTiles(Tile* tiles);

    //  Returns if the factory is empty or not
    bool isEmpty();

private:

    Tile* tiles;

};

#endif //FACTORY_H
