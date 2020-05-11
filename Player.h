#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"

class Player {
public:

    //  Constructor / Destructor
    Player(int id, std::string name);
    ~Player();

    //  Returns player ID
    int getId();

    //  Returns player name
    std::string getName();

    //  Gets player's board
    Board getBoard();

    //  Sets player's board
    void setBoard(Board board);

private:

    int id;
    std::string name;
    Board board;

};

#endif // PLAYER_H
