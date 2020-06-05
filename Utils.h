#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <exception>
#include "Tile.h"
#include "GameManager.h"

/**
 * Displays game menu with seed
 */
void showMenu(int seed);

/**
 *  Loads a game from a save file
 */
void loadGame(int seed);

/**
 * Converts a string of colours to a vector of tiles
 */
std::vector<TilePtr> loadTiles(std::string s, std::vector<TilePtr> v);

/**
 *  Saves a game to a save file
 */
void
saveGame(std::string filename, Player *p1, Player *p2, Factory *f, int turn,
         int active, Bag *bag, bool AI);

/**
 *  Display programmers
 */
void showCredits();


#endif // UTILS_H