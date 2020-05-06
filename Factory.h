#ifndef FACTORY_H
#define FACTORY_H

#include <vector>
// chosen because factory has a small size
// and cost is negligible

#include "Bag.h"

class Factory {

public:

    //  Constructor / Destructor
    Factory();
    ~Factory();

    /**
     * Get all the tiles of a colour
     * returns an array of tiles
     */
    TilePtr getTiles(Colour colour, int count);

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

private:

    std::vector<TilePtr> factory;

};

#endif //FACTORY_H
