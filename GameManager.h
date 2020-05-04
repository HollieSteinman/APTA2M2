#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Player.h"
#include "Tile.h"

class GameManager {
public:

    //  Constructor / Destructor
    GameManager(Player* players[]);
    ~GameManager();

    //  Generates a new game - e.g. tiles, piles and blank player boards
    void generateGame();

    //  Returns the current round - used for saving
    void getRound();

    //  Plays a round through each player
    void playRound();

    //  Returns tiles of one pattern from a pile and discards the rest
    Tile* getPile(int pile, std::string pattern);

    //  Returns tiles of one pattern from discard pile and places rest in bag
    Tile* getDiscarded(std::string pattern);

    //  Generates piles from the bag
    void generatePiles();

    //  Sets player to play first
    void setFirstPlayer(int playerID);

    //  Saves the current game
    void saveGame();

    //  Menu for each player - option to save and quit
    void menu();

private:

    int round;
    Player* players;
    Tile** piles;
    Tile* discarded;
    Tile* bag;

};

#endif //GAMEMANAGER_H
