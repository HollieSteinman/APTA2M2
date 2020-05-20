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
#include "Mosaic.h"


class Args {
public:
   bool haveSeed;
   int seed;
};

void processArgs(int argc, char** argv, Args* args);
void testBag(Bag* gameBag, TilePtr holder);
void testFactory(Bag* gameBag, Factory* factory01);
void testMosaic(Mosaic* mosaic, Bag* gameBag, Factory* factory);

int main(int argc, char** argv){
    // Process the args
    Args args;
    processArgs(argc, argv, &args);

    try {

        // basic main methods should be included in this try block
        showMenu();
        // TilePtr holder = new Tile(R);
        // Bag* gameBag = new Bag(10);
        // Factory* factory01 = new Factory();
        // Mosaic* mosaic = new Mosaic();
        showMenu();
        // Pile* playp = new Pile();
        // To run tests do not show the menu
        // testBag(gameBag, holder);
        // testFactory(gameBag, factory01);
        // testMosaic(mosaic, gameBag, factory01);
        // factory01->loadFactory(gameBag);
        // playp->loadPile(factory01, R, 1);
        // board->getPile()->loadPile(factory01, R, 1);
        // args.seed;
        

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

void testMosaic(Mosaic* mosaic, Bag* gameBag, Factory* factory){
    // ge
    factory->loadFactory(gameBag);
    factory->listFactory();
    mosaic->displayMosaic();
    mosaic->loadPile(factory, 3, U, 2);
    mosaic->loadPile(factory, 4, Y, 3);
    mosaic->loadPile(factory, 5, U, 4);
    mosaic->loadPile(factory, 2, Y, 3);
    mosaic->loadPile(factory, 0, Y, 5);
    mosaic->loadPile(factory, 0, R, 1);
    // use this to test error trap
    // mosaic->loadPile(factory, 1, R, 4);
    factory->listFactory();
    mosaic->displayMosaic();
    mosaic->score();
    mosaic->displayMosaic();
    for (unsigned int i = 0; i < mosaic->getToBox().size(); ++i){
        std::cout << mosaic->getToBox().at(i)->getChar();
    }
    std::cout << std::endl;
}