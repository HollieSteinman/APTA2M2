/**
 * A project to design a cli based game of Azul
 * Designed for Advanced Programming Techniques
 * course at RMIT University
 */

#include <string>
#include <iostream>
#include <fstream>
#include <exception>
#include <stdexcept>

#include "Utils.h"

int main(int argc, char** argv){

    try {

        showMenu();

    } catch (std::exception& e){

         std::cerr << "Exception Caught: " << e.what() << std::endl;
         showMenu();
         
    }

    return EXIT_SUCCESS;
}