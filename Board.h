#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>
#include <iostream>

#include "Pile.h"

/**
 * Define a variable type Mos
 * which is a 5x5 2D array
 */
typedef TilePtr Mos[5][5];

class Board {

    public:

        /**
         * Constructor / Deconstructor
         */
        Board();
        ~Board();

        /**
         * Returns board points
         */
        int getPoints();

        //  Sets board points
        void setPoints(int points);

        /**
         * Calculates score from board
         * also sets the points scored
         * also loads tiles to be put
         * back in the box lid
         */
        void score();

        //  Sets queue of tiles
        void setQueue(Tile* tiles, int row);

        //  Adds queue to mosaicclass Player {};
        void addQueue();

        //  Returns board to save
        std::string** getBoard();

        //  Sets board from a save
        void setBoard(std::string** board);

        /**
         * Displays the board
         */
        void displayBoard();

        /**
         * Pile Accessor
         */
        Pile* getPile();

        /**
         * Shows the puzzle to solve
         */
        void displayPuzzle();

        /**
         * Returns tiles to be put
         * in the box lid
         */
        std::vector<TilePtr> getToBox();

    private:

        Mos mosaic;
        Mos puzzle;
        Pile* pile;
        int points;
        std::vector<TilePtr> toBox;

};

#endif //BOARD_H
