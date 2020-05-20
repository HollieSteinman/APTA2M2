#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <exception>
#include "Tile.h"
#include "GameManager.h"

#define BAG_SIZE 100

/**
 *  Displays the game menu
 */
void showMenu();

/**
 *  Plays the game
 */
void playGame(int seed);

/**
 *  Plays the game from a saved gameManager
 */
void playGame(GameManager* gameManager);

/**
 *  Loads a game from a save file
 */
void loadGame();

std::vector<TilePtr> loadTiles(std::string s, std::vector<TilePtr> v);

/**
 *  Saves a game to a save file
 */
void saveGame(std::string filename, Player *p1, Player *p2,
              Factory *f, int turns, int active);

/**
 *  Display programmers
 */
void showCredits();


#endif // UTILS_H