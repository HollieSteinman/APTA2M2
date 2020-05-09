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

        //  Calculate score from board
        void calculateScore();

        //  Sets queue of tiles
        void setQueue(Tile* tiles, int row);

        //  Adds queue to mosaic
        void addQueue();

        //  Returns board to save
        std::string** getBoard();

        //  Sets board from a save
        void setBoard(std::string** board);

        /**
         * Displays the board
         */
        void displayBoard();

    private:

        Mos mosaic;
        Pile* pile;
        int points;

};

#endif //BOARD_H
