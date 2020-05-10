#ifndef FACTORY_H
#define FACTORY_H

#include <iostream>
#include <vector>
// chosen because factory has a small size
// and overall cost is negligible

#include "Bag.h"

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
     * Returns true if factory is empty
     */
    bool isEmpty();

    /**
     * Lists all members of the factory
     */
    void listFactory();

    /**
     * Factory Accessor
     * use 0 to access the center
     * factory
     */
    std::vector<TilePtr> getFactory(int line);

    /**
     * Was the center picked
     */
    bool pCenter();

private:

    // std::vector<TilePtr> factory;
    std::vector<TilePtr> fa1;
    std::vector<TilePtr> fa2;
    std::vector<TilePtr> fa3;
    std::vector<TilePtr> fa4;
    std::vector<TilePtr> fa5;
    std::vector<TilePtr> center;
    bool pickCenter;

};

#endif //FACTORY_H
