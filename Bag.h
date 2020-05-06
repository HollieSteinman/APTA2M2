#ifndef BAG_H
#define BAG_H

#include <string>
#include <random>
#include <iostream>

#include "Tile.h"

/**
 * Used to move along the pointers
 */
class Node {
public:
   TilePtr value;
   Node* next;
};

/**
 * Create a linked list and instantiate the head
 */
class LinkedList {
public:
   Node* head;
};

/**
 * Create a shuffled bag of tiles
 */
class Bag {
    public:
        /**
         * Constructor / Deconstructor
         */
        Bag(int randGen);
        ~Bag();

        /**
         * Return the current number of
         * tiles in the bag
         */
        int size();
        /**
         * Draw a tile from the bag
         */
        TilePtr serveTile();
        /**
         * Used to reload the bag
         */
        void addTile(TilePtr tile);
        /**
         * Used for destructive purposes
         */
        void removeTile(int index);
        /**
         * Empty the bag
         */
        void clear();

    private:
        LinkedList* bag;
};



#endif // BAG_H