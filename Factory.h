#ifndef FACTORY_H
#define FACTORY_H

#include <iostream>
#include <vector>
// chosen because factory has a small size
// and overall cost is negligible

#include "Bag.h"
#include "Tile.h"

class Factory {

public:

    /**
     * Constructor / Deconstructor
     */
    Factory();
    ~Factory();

    /**
     * Get all the tiles of a colour
     * returns a vector of tiles
     * auto adds tiles to center
     */
    std::vector<TilePtr> getTiles(Colour colour, int line);

    /**
     * Load the factory from the bag
     * This is used by the all factories
     * center factory is auto loaded
     */
    void loadFactory(Bag* bag);

    /**
     * Loads a specific factory,
     * used for loading save file
     */
    void loadFactory(int factoryNo, std::vector<TilePtr> factory);

    /**
     * Returns true if factory is empty
     */
    bool isEmpty();

    /**
     * Lists all members of the factory
     */
    void listFactory();

    /**
     * Returns factory as string
     */
     std::string getFactoryString(int fac);

private:

    std::vector<TilePtr> fa1;
    std::vector<TilePtr> fa2;
    std::vector<TilePtr> fa3;
    std::vector<TilePtr> fa4;
    std::vector<TilePtr> fa5;
    std::vector<TilePtr> center;

};

#endif //FACTORY_H
