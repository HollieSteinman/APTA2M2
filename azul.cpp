/**
 * A project to design a cli based game of Azul
 * Designed for Advanced Programming Techniques
 * course at RMIT University
 */

#include <string>
#include <random>
#include <fstream>
#include <sstream>
#include <iostream>
#include <exception>
#include <stdexcept>

#include "Utils.h"
#include "Bag.h"
#include "Factory.h"
#include "Board.h"
#include "Pile.h"


class Args {
public:
   bool haveSeed;
   int seed;
};

void processArgs(int argc, char** argv, Args* args);
void testBag(Bag* gameBag, TilePtr holder);
void testFactory(Bag* gameBag, Factory* factory01);
void testBoard(Board* board);

int main(int argc, char** argv){
    // Process the args
    Args args;
    processArgs(argc, argv, &args);

    try {

        // basic main methods should be included in this try block
        // showMenu();
        // TilePtr holder = new Tile(R);
        Bag* gameBag = new Bag(10);
        Factory* factory01 = new Factory();
        // Board* board = new Board();
        // Pile* playp = new Pile();
        // To run tests do not show the menu
        // testBag(gameBag, holder);
        testFactory(gameBag, factory01);
        // testBoard(board);
        // factory01->loadFactory(gameBag);
        // playp->loadPile(factory01, R, 1);
        // board->getPile()->loadPile(factory01, R, 1);
        
        

    } catch (std::exception& e){

        std::cerr << "Exception Caught: " << e.what() << std::endl;
        showMenu();

    }

    return EXIT_SUCCESS;
}

void processArgs(int argc, char** argv, Args* args) {
   // First argument (index 0) - name of the program

   // Second args - random seed
   if (argc >= 2) {

      std::string seedSwitch(argv[1]);
      if (seedSwitch == "-s"){

          std::string strSeed(argv[2]);
          std::stringstream sstream(strSeed);
          sstream >> args->seed;
          
          args->haveSeed = true;

        }

    } else {

        args->haveSeed = false;
        args->seed = 0;
        
    }
}

void testBag(Bag* gameBag, TilePtr holder){
    std::cout << gameBag->size() << std::endl;
        for (int i = 0; i < 100; ++i){
        // while (gameBag->serveTile() != nullptr){
            holder = gameBag->serveTile();
            if (holder != nullptr){
                std::cout << holder->getColour() << " " << gameBag->size() << std::endl;
                // delete holder;
            }
        }
}

void testFactory(Bag* gameBag, Factory* factory01){
    factory01->loadFactory(gameBag);
    factory01->listFactory();
    // simulate player pile
    std::vector<TilePtr> holder = factory01->getTiles(R, 1);
    factory01->listFactory();
    holder = factory01->getTiles(U, 5);
    factory01->listFactory();
    holder = factory01->getTiles(Y, 0);
    factory01->listFactory();
    std::cout << "-------------------" << std::endl;
    for (unsigned int i = 0; i < holder.size(); ++i){
        std::cout << holder[i]->getChar() << " ";
    }
    std::cout << std::endl;
}

void testBoard(Board* board){
    board->displayBoard();
}