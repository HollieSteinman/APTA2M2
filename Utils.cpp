#include <fstream>
#include <sstream>
#include <vector>
#include "Utils.h"
#include "Tile.h"
#include "Factory.h"
#include "Player.h"

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

    std::cout << "Enter the filename from which load a game" << std::endl;
    std::cout << "> ";

    std::string filename;
    std::cin >> filename;

    // filename for testing, change later
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
                std::string pId, pName, pPoints, pStarter, label;
                int id, points, starter;
                while(getline(ss, line)) {
                    std::stringstream ls(line);

                    getline(ls, label, ':');

                    if(label == "id") {
                        getline(ls, pId, ':');
                        std::istringstream(pId) >> id;
                    } else if (label == "name") {
                        getline(ls, pName, ':');
                    } else if (label == "points") {
                        getline(ls, pPoints, ':');
                        std::istringstream(pPoints) >> points;
                    } else if (label == "mosaic") {
                        //TODO implement mosaic load
                    } else if (label == "pile") {
                        //TODO implement pile load
                    } else if (label == "broken") {
                        //TODO implement broken load
                    } else if (label == "starter") {
                        getline(ls, pStarter, ':');
                        std::istringstream(pPoints) >> starter;
                    }
                }

                // Player player = new Player(id, pName);

            } else if (type == "factory") {
                Factory factory;
                std::string facStr, facContent;
                while(getline(ss, line)) {
                    // WARNING - check if empty, last line is blank
                    std::stringstream ls(line);

                    // gets the factory number
                    getline(ls, facStr, ':');

                    int facNo;
                    if (facStr == "mid") {
                        facNo = 0;
                    } else {
                        std::istringstream(facStr.substr(
                                facStr.length() - 1)) >> facNo;
                    }
                    // gets the content of the factory
                    getline(ls, facContent, ':');

                    std::vector<TilePtr> fac;

                    //TODO check if empty
                    for (char &c : facContent) {
                        //TODO check referencing
                        if (c == 'F') {
                            TilePtr tile = new Tile(F);
                            fac.push_back(tile);
                        } else if (c == 'R') {
                            TilePtr tile = new Tile(R);
                            fac.push_back(tile);
                        } else if (c == 'Y') {
                            TilePtr tile = new Tile(Y);
                            fac.push_back(tile);
                        } else if (c == 'B') {
                            TilePtr tile = new Tile(B);
                            fac.push_back(tile);
                        } else if (c == 'L') {
                            TilePtr tile = new Tile(L);
                            fac.push_back(tile);
                        } else if (c == 'U') {
                            TilePtr tile = new Tile(U);
                            fac.push_back(tile);
                        }
                    }

                    factory.loadFactory(facNo, fac);
                    fac.clear();
                }
            }
        }

    } else {
        std::cout << "File not found, returning to menu." << std::endl;
        showMenu();
    }

}