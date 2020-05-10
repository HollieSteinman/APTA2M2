#include <fstream>
#include <sstream>
#include "Utils.h"

void showMenu(){
    std::cout << "Welcome To Azul! " << std::endl;
    std::cout << "------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "Menu " << std::endl;
    std::cout << "1. New Game " << std::endl;
    std::cout << "2. Load Game " << std::endl;
    std::cout << "3. Credits " << std::endl;
    std::cout << "4. Quit" << std::endl;
    std::cout << std::endl;
    std::cout << "> ";

    int menu = 0;
    std::cin >> menu;

    if (menu == 1) {
        // playGame();
    } else if (menu == 2) {
        loadGame();
    } else if (menu == 3) {
        showCredits();
        showMenu();
    } else if (menu == 4) {
        std::cout << "Bye Bye" << std::endl;
        exit(0);
    } else {
        throw std::range_error("Please select an item from the list");
    }

}

void showCredits(){
    std::cout << std::endl;
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "Name: Emmanuel Chukwudi Nwordu " << std::endl;
    std::cout << "Student ID: s3667339 " << std::endl;
    std::cout << "Email: s3667339@student.rmit.edu.au " << std::endl;
    std::cout << std::endl;
    std::cout << "Name: Joel Liang Shien Tan " << std::endl;
    std::cout << "Student ID: s3758729 " << std::endl;
    std::cout << "Email: s758729@student.rmit.edu.au " << std::endl;
    std::cout << std::endl;
    std::cout << "Name: Hollie Steinman " << std::endl;
    std::cout << "Student ID: s3784783 " << std::endl;
    std::cout << "Email: s784783@student.rmit.edu.au " << std::endl;
    std::cout << "-------------------------------------------" << std::endl;
}

void loadGame() {
    // filename for testing, change later
    std::string filename = "saveGame.txt";
    std::string dir = "saves/";

    // opens file
    std::ifstream saveFile (dir.append(filename));

    // checks if file exists
    if(saveFile.good()) {
        std::string input;
        while(!saveFile.eof()) {
            // searches for the start of an object
            getline(saveFile, input, '$');
            // until the end of the object
            getline(saveFile, input, '#');

            // creates a stringstream of each object
            std::stringstream ss(input);
            std::string line, type;
            // first line is blank - fix
            getline(ss, line);
            // gets first line (object type)
            getline(ss, line);

            // creates stringstream for the first line
            std::stringstream ls(line);

            // gets label
            getline(ls, type, ':');
            // gets type
            getline(ls, type, ':');

            if(type == "player") {
                //TODO load player
            } else if (type == "factory") {
                std::string facNo, facContent;
                while(getline(ss, line)) {
                    // WARNING - check if empty, last line is blank
                    std::stringstream ls(line);

                    // gets the factory number
                    getline(ls, facNo, ':');
                    std::cout << "Factory Number:" << facNo << std::endl;

                    // gets the content of the factory
                    getline(ls, facContent, ':');
                    std::cout << "Factory Content:" << facContent << std::endl;
                }
            }
        }

    } else {
        // Error handling
    }

}