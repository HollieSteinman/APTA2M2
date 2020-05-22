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
    GameManager(int seed);
    GameManager(Player* p1, Player* p2, int r, Factory* f, Bag* b);
    ~GameManager();

    /**
     * Plays a round through each player 
     * and scores player mosaic at end of round
     */
    void playRound();

    /**
     * Displays current player tables
     */
    void displayTurn();

    /**
     * Plays a single turn
     */
     void playTurn(int fRow, char color, int pRow, Colour colour);

    /**
     * Sets the player to play first
     */
    void setFirstPlayer(int playerID);

    /**
     * Returns colour given a char
     * sanitises user colour input
     */
    Colour makeColour(char c);

    /**
     * Runs relevant methods based
     * on command
     */
     void runCommand();


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

};

#endif //GAMEMANAGER_H
