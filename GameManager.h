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

    //  Generates a new game - e.g. tiles, piles and players
    void generateGame();

    //  Returns the current round - used for saving
    void getRound();

    //  Plays a round through each player and adds to mosaic at end of round
    void playRound();

    //  Returns tiles of one colour from a factory and discards the rest
    Tile* getFactory(int pile, char colour);

    //  Returns tiles of one colour from center factory and places rest in bag
    Tile* getCenter(char colour);

    //  Generates piles from the bag
    void generatePiles();

    //  Sets player to play first
    void setFirstPlayer(int playerID);

    //  Saves the current game
    void saveGame();

    //  Menu for each player - option to save and quit
    void menu();

    //  Displays all factories for players
    void displayFactories();

private:

    int round;
    Player* players[2];
    Factory* factories[5];
    Factory center;
    Tile* bag;
    Tile* lid;

};

#endif //GAMEMANAGER_H
