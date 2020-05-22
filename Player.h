#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "Mosaic.h"

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
     * Sets player mosaic
     */
    void setMosaic(Mosaic* m);

    /**
     * Returns player board
     */
    Mosaic* getMosaic();

    /**
     * Returns true if player 
     * will start next round
     */
    bool toStart();

    /**
     * Play a turn
     */
    void playTurn(Factory* factory,unsigned int fRow, Colour colour,unsigned int pRow);

private:

    int id;
    std::string name;
    Mosaic* mosaic;

};

#endif // PLAYER_H
