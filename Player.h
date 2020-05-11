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

    /**
     * Returns player board
     */
    Board* getBoard();

    //  Sets player's board
    void setBoard(Board board);

    /**
     * Returns true if player 
     * will start next round
     */
    bool toStart();


private:

    int id;
    Board* board;
    bool isStarter();

};

#endif // PLAYER_H
