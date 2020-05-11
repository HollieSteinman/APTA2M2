#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Player.h"
#include "Tile.h"
#include "Factory.h"

class GameManager {
public:

    //  Constructor / Destructor
    GameManager();
    ~GameManager();

    //  Returns the current round - used for saving
    void getRound();

    //  Plays a round through each player and adds to mosaic at end of round
    void playRound();

    //  Displays player's board and piles
    void displayRound();

    //  Returns tiles of one colour from a factory and discards the rest
    Tile* getFactory(int pile, char colour);

    //  Generates piles from the bag
    void generatePiles();

    //  Sets player to play first
    void setFirstPlayer(int playerID);

    //  Saves the current game
    void saveGame();

private:

    int round;

    // TODO variables for game

};

#endif //GAMEMANAGER_H
