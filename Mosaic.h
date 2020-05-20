#ifndef MOSAIC_H
#define MOSAIC_H

#include <string>
#include <vector>

#include "Factory.h"

/**
 * Define a variable type Mos
 * which is a 5x5 2D array
 */
typedef TilePtr Mos[5][5];

class Mosaic {
    public:
        /**
         * Constructor / Deconstructor
         */
        Mosaic();
        Mosaic(bool s, Mos m, int p, std::vector<TilePtr> v[6]);
        ~Mosaic();

        /**
         * Returns mosaic points
         */
        int getPoints();

        /**
         * Load the pile from the factory
         */
        void loadPile(Factory* factory, unsigned int fRow, Colour colour, unsigned int pRow);

        /**
         * Load the broken pile
         */
        void loadBroken(TilePtr tile);

        /**
         * Returns true if F tile
         * is picked from center factory
         */
        bool toStart();

        /**
         * Displays the board
         */
        void displayMosaic();

        /**
         * Calculates score from board
         * also sets the points scored
         * also loads tiles to be put
         * back in the box lid
         */
        void score();

        /**
         * Returns tiles meant for 
         * the box lid
         */
        std::vector<TilePtr> getToBox();

        /**
         * Clears the boxholder after 
         * every round
         */
        void clearToBox();

        /**
         * Returns true if a mosaic
         * row is filled
         */
        bool isGameover();
        
        /**
         * Returns broken tiles
         */
        std::vector<TilePtr> getBrokenTile();

        /**
         * Returns mosaic as a string
         */
        std::string getMosaic();

        /**
         * Returns Pile as a string
         */
        std::string getPile();

        /**
         * Returns Broken tiles as string
         */
        std::string getBroken();

    private:
        std::vector<TilePtr> p1;
        std::vector<TilePtr> p2;
        std::vector<TilePtr> p3;
        std::vector<TilePtr> p4;
        std::vector<TilePtr> p5;
        std::vector<TilePtr> broken;
        std::vector<TilePtr> toBox;
        bool starter;
        Mos mosaic;
        Mos puzzle;
        int points;
        bool gameover;
};

#endif // MOSIAC_H