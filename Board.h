#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"

class Board {

public:

    //  Constructor / Destructor
    Board();
    ~Board();

    //  Returns board points
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

    //  Displays the board
    void displayBoard();

private:

    int points;
    Tile** queue;
    Tile** mosaic;
    Tile* broken;

};

#endif //BOARD_H
