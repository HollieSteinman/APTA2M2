#ifndef PILE_H
#define PILE_H

#include <string>
#include <vector>

#include "Factory.h"

class Pile {
    public:
        /**
         * Constructor / Deconstructor
         */
        Pile();
        ~Pile();

        /**
         * Load the pile from the factory
         * 
         */
        void loadPile(Factory* factory, unsigned int fRow, Colour colour, unsigned int pRow);

        /**
         * Load the broken pile
         */
        void loadBroken(TilePtr tile);

        /**
         * Return Pile 1
         */
        std::vector<TilePtr> getP1();

        /**
         * Return Pile 2
         */
        std::vector<TilePtr> getP2();

        /**
         * Return Pile 3
         */
        std::vector<TilePtr> getP3();

        /**
         * Return Pile 4
         */
        std::vector<TilePtr> getP4();

        /**
         * Return Pile 5
         */
        std::vector<TilePtr> getP5();

        /**
         * Return broken tiles
         */
        std::vector<TilePtr> getBroken();

    private:
        std::vector<TilePtr> p1;
        std::vector<TilePtr> p2;
        std::vector<TilePtr> p3;
        std::vector<TilePtr> p4;
        std::vector<TilePtr> p5;
        std::vector<TilePtr> broken;
};

#endif // PILE_H