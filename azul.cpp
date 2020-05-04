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

class Args {
public:
   bool haveSeed;
   int seed;
};

void processArgs(int argc, char** argv, Args* args);

int main(int argc, char** argv){
    // Process the args
    Args args;
    processArgs(argc, argv, &args);

    try {

        // basic main methods should be included in this try block
        showMenu();

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
