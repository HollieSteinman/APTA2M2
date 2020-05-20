#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <exception>

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
void playGame();

/**
 *  Loads a game from a save file or
 *  makes a new game
 */
void loadGame();

/**
 *  Display programmers
 */
void showCredits();


#endif // UTILS_H