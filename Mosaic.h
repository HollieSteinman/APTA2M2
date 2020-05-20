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
<<<<<<< HEAD
         * Returns mosaic as a string
=======
         * Returns mosaic as string
>>>>>>> 1beefa6825fb305f9ea55334c2b984c0147a4c6e
         */
        std::string getMosaic();

        /**
<<<<<<< HEAD
         * Returns Pile as a string
=======
         * Returns pile as string
>>>>>>> 1beefa6825fb305f9ea55334c2b984c0147a4c6e
         */
        std::string getPile();

        /**
<<<<<<< HEAD
         * Returns Broken tiles as string
=======
         * Returns broken as string
>>>>>>> 1beefa6825fb305f9ea55334c2b984c0147a4c6e
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