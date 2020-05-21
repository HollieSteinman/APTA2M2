#ifndef BAG_H
#define BAG_H

#include <string>
#include <random>
#include <iostream>
#include <vector>

#include "Tile.h"

/**
 * Create a Tile node and pointer
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
        Bag(std::vector<TilePtr> tempBag, int randGen);
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

        /**
         * Reload the bag from the boxlid
         */
        void reload();

        /**
         * Put tiles in the boxLid
         */
        void putBox(std::vector<TilePtr> tiles);

        /**
         * Clear the boxlid at end of game
         */
        void clearBox();

        /**
         * Gets seed
         */
         int getSeed();

         /**
          * Return bag as string
          */
          std::string getBag();

          /**
           * Return lid as string
           */
           std::string getLid();

    private:
        int seed;
        LinkedList* bag;
        std::vector<TilePtr> boxLid;
};



#endif // BAG_H