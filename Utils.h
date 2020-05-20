#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <exception>
#include "Tile.h"

#define BAG_SIZE 100

/**
 *  Displays the game menu
 */
void showMenu();

/**
 * Displays game menu with seed
 */
void showMenu(int seed);

/**
 *  Plays the game
 */
void playGame(int seed);

/**
 *  Loads a game from a save file
 */
void loadGame();

// std::vector<TilePtr> loadTiles(std::string s, std::vector<TilePtr> v);

/**
 *  Saves a game to a save file
 */
void saveGame(std::string filename);

/**
 *  Display programmers
 */
void showCredits();


#endif // UTILS_H