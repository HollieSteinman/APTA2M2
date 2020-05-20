#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Player.h"
#include "Tile.h"
#include "Bag.h"
#include "Factory.h"

class GameManager {
public:

    //  Constructor / Destructor
    GameManager();
    GameManager(int seed);
    ~GameManager();

    //  Returns the current round - used for saving
    void getRound();

    //  Plays a round through each player and adds to mosaic at end of round
    void playRound();

    //  Displays player's board and piles
    void displayRound();

    //  Returns tiles of one colour from a factory and discards the rest
    // i think this should be done by the ADT to keep in line with the struct
    Tile* getFactory(int pile, char colour);

    //  Generates piles from the bag
    // this is also handled by the ADT
    void generatePiles();

    //  Sets player to play first
    void setFirstPlayer(int playerID);

    //  Saves the current game
    void saveGame();

private:

    int round;
    Bag* bag;
    Factory* factory;
    Player* plyr1;
    Player* plyr2;
    bool gameOver;

    // TODO variables for game

};

#endif //GAMEMANAGER_H
