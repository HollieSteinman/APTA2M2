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
     * remember to addtiles to center
     */
    std::vector<TilePtr> getTiles(Colour colour);

    /**
     * Return the number of tiles in the 
     * factory
     */
    int size();

    /**
     * Load the factory from the bag
     * This is used by the 5 factories
     */
    void loadFactory(Bag* bag);

    /**
     * Add tile to factory, this is used
     * by the center factory
     */
    void addTile(TilePtr tile);

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
     */
    std::vector<TilePtr> getFactory();

private:

    std::vector<TilePtr> factory;

};

#endif //FACTORY_H
