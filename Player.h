#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "Board.h"

class Player {
public:

    /**
     * Constructor / Deconstructor
     */
    Player(int id, std::string name);
    ~Player();

    /**
     * Returns player id
     */
    int getId();

    /**
     * Returns player name
     */
    std::string getName();

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
    std::string name;
    Board* board;
    bool isStarter();

};

#endif // PLAYER_H
