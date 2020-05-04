#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"

class Player {
public:

    //  Constructor / Destructor
    Player(int id);
    ~Player();

    //  Returns player ID
    int getId();

    //  Gets player's board
    Board getBoard();

    //  Sets player's board
    void setBoard(Board board);

private:

    int id;
    Board board;

};

#endif // PLAYER_H
