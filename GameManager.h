#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Player.h"
#include "Tile.h"
#include "Bag.h"
#include "Factory.h"
#include "Bag.h"
#include <fstream>
#include <sstream>
#include <vector>

class GameManager {
public:

    //  Constructor / Destructor
    GameManager();
    GameManager(int seed);
    ~GameManager();

    //  Returns the current round - used for saving
    void getRound();

    /**
     * Plays a round through each player 
     * and scores player mosaic at end of round
     */
    void playRound();

    /**
     * Gets the game going
     */
    void startGame();

    /**
     * Displays current player tables
     */
    void displayTurn();

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

    /**
     * Returns color given a char
     */
    Colour makeColour(char c);

private:

    int round;
    Player* plyr1;
    Player* plyr2;
    Bag* bag;
    int currPlayerID;
    Factory* factory;
    Tile* currTile;
    std::vector<std::string> turns;
    std::vector<std::string> stringcommand;
    bool gameOver;  
    // TODO variables for game

};

#endif //GAMEMANAGER_H
