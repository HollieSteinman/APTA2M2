#include <sstream>
#include "Utils.h"
#include "Player.h"
#include "GameManager.h"
#include "AI.h"

void showMenu(int seed){
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
        std::cout<< "New Game " << std::endl;
        std::cout<< "1. One Player (AI Opponent) " << std::endl;
        std::cout<< "2. Two Players " << std::endl;
        std::cout << std::endl;
        std::cout << "> ";

        std::cin >> menu;

        if(menu == 1) {
            GameManager* gameManager = new GameManager(seed, 1);
            gameManager->playRound();
        } else if (menu == 2) {
            GameManager* gameManager = new GameManager(seed, 2);
            gameManager->playRound();
        } else {
            throw std::range_error("Please select an item from the list");
        }
    } else if (menu == 2) {
        loadGame(seed);
    } else if (menu == 3) {
        showCredits();
        showMenu(seed);
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
    std::cout << "Email: s3667339@student.rmit. // playGame();edu.au " << std::endl;
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

/* ALGORITHM loadGame(int seed)
 * BEGIN
 * file name entered
 * IF file exists
 *     WHILE not end of file (eof)
 *          search until '$'
 *          search until '#'
 *          save string between '$' and '#'
 *          read first line of string
 *          read first line after ':'
 *          IF remaining string equals "player"
 *              run code to load player from rest of string
 *          ELSE IF remaining string equals "factory"
 *              run code to load factories from rest of string
 *          ELSE IF remaining string equals "game"
 *              run code to load game data from rest of string
 *     close file
 *     resume game
 * ELSE
 *     throw file not found error
 *     return to menu
 * END
 */


void loadGame(int s) {

    std::cout << "Enter the filename from which load a game" << std::endl;
    std::cout << "> ";
    
    std::string filename;
    std::cin >> filename;

    // file directory
    std::string dir = "saves/";

    // opens file
    std::ifstream saveFile (dir.append(filename));

    // checks if file exists
    if(saveFile.good()) {
        // constructing new objects
        Player *player1 = new Player(0, ""),
                *player2 = new Player(0, "");
        Factory *factory = new Factory();
        int turns = 0,
            active = 0,
            seed = 0;
        Bag *bag = new Bag(0);
        bool singleplayer = false;

        std::string input;

        // continue searching for objects until end of file is reached
        while(!saveFile.eof()) {
            // searches for the start of an object
            getline(saveFile, input, '$');
            // until the end of the object, save string to input
            getline(saveFile, input, '#');

            // creates a stringstream of each object
            std::stringstream ss(input);
            std::string line, type;

            // first line is blank
            getline(ss, line);
            // gets first line (object type)
            getline(ss, line);

            // creates stringstream for the first line
            std::stringstream ls(line);

            // gets label by searching the first line for ':'
            getline(ls, type, ':');
            // gets type
            getline(ls, type, ':');

            if(type == "player" || type == "ai") {
                std::string pId, pName, pPoints, pStarter, pMosaic,
                    pPile, pBroken, label;
                int id, points;
                bool starter = false;
                Mos m;
                std::vector<TilePtr> vectors[6], p1, p2, p3, p4, p5, broken;

                // continues while it has a new line
                while(getline(ss, line)) {
                    std::stringstream ls(line);

                    // gets label
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
                        getline(ls, pMosaic, ':');
                        std::stringstream ms(pMosaic);

                        // for each mosaic line
                        for(int i = 0; i < 5; i++) {
                            // get the next block in the line until ','
                            getline(ms, pMosaic, ',');
                            // for each element in the mosaic line
                            for(int j = 0; j < 5; j++) {
                                // convert to a char
                                char c = pMosaic[j];
                                TilePtr tile;
                                // create a new tile based on the char
                                if (c == 'F') {
                                    tile = new Tile(F);
                                } else if (c == 'R') {
                                    tile = new Tile(R);
                                } else if (c == 'Y') {
                                    tile = new Tile(Y);
                                } else if (c == 'B') {
                                    tile = new Tile(B);
                                } else if (c == 'L') {
                                    tile = new Tile(L);
                                } else if (c == 'U') {
                                    tile = new Tile(U);
                                } else {
                                    tile = new Tile(E);
                                }
                                // assign the tile to the correct spot in the mosaic
                                m[i][j] = tile;
                            }
                        }
                    } else if (label == "pile") {
                        // converts all blocks (until next ',') to TilePtr vectors
                        getline(ls, pPile, ':');
                        std::stringstream ps(pPile);

                        getline(ps, pPile, ',');
                        p1 = loadTiles(pPile, p1);

                        getline(ps, pPile, ',');
                        p2 = loadTiles(pPile, p2);

                        getline(ps, pPile, ',');
                        p3 = loadTiles(pPile, p3);

                        getline(ps, pPile, ',');
                        p4 = loadTiles(pPile, p4);

                        getline(ps, pPile, ',');
                        p5 = loadTiles(pPile, p5);
                    } else if (label == "broken") {
                        // converts the block to a TilePtr vector
                        getline(ls, pBroken, ':');
                        broken = loadTiles(pBroken, broken);
                    } else if (label == "starter") {
                        getline(ls, pStarter, ':');
                        if(pStarter == "0") {
                            starter = false;
                        } else {
                            starter = true;
                        }

                    }
                }

                // adding vectors to array for creation of a player's mosaic
                vectors[0] = p1;
                vectors[1] = p2;
                vectors[2] = p3;
                vectors[3] = p4;
                vectors[4] = p5;
                vectors[5] = broken;

                // if the id is 1, assign to player1, else assign to player2
                if(id == 1) {
                    player1 = new Player(id, pName);
                    Mosaic* mosaic = new Mosaic(starter, m, points, vectors);
                    player1->setMosaic(mosaic);
                } else if(type == "ai") {
                    player2 = new AI(id);
                    Mosaic* mosaic = new Mosaic(starter, m, points, vectors);
                    player2->setMosaic(mosaic);
                    singleplayer = true;
                } else {
                    player2 = new Player(id, pName);
                    Mosaic* mosaic = new Mosaic(starter, m, points, vectors);
                    player2->setMosaic(mosaic);
                }


            } else if (type == "factory") {
                std::string facStr, facContent;
                // while there is a new line (i.e. new factory)
                while(getline(ss, line)) {
                    std::stringstream ls(line);

                    // gets the factory number
                    getline(ls, facStr, ':');

                    int facNo;
                    if (facStr == "mid") {
                        facNo = 0;
                    } else {
                        // convert factory number string to int and assign to facNo
                        std::istringstream(facStr.substr(
                                facStr.length() - 1)) >> facNo;
                    }
                    // gets the content of the factory
                    getline(ls, facContent, ':');

                    // loads tiles into a vector from the block
                    std::vector<TilePtr> fac;

                    for (char &c : facContent) {
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

                    // load the factory into the factory object
                    factory->loadFactory(facNo, fac);

                    // clean up
                    fac.clear();
                }
            } else if (type == "game") {
                std::string label, gTurns, gActive, gSeed, gBag, gLid;
                // continues while it has a new line
                while(getline(ss, line)) {
                    std::stringstream ls(line);

                    getline(ls, label, ':');

                    if(label == "turns") {
                        getline(ls, gTurns, ':');
                        std::istringstream(gTurns) >> turns;
                    } else if (label == "active") {
                        getline(ls, gActive, ':');
                        std::istringstream(gActive) >> active;
                    } else if (label == "seed") {
                        getline(ls, gSeed, ':');
                        std::istringstream(gSeed) >> seed;
                    } else if (label == "bag") {
                        getline(ls, gBag, ':');
                        // loads tiles into a vector from the string block
                        std::vector<TilePtr> tempBag;
                        tempBag = loadTiles(gBag, tempBag);
                        // creates a new bag with the seed and vector of tiles
                        bag = new Bag(tempBag, seed);
                    } else if (label == "lid") {
                        getline(ls, gLid, ':');
                        // loads tiles into a vector from the string block
                        std::vector<TilePtr> lid;
                        lid = loadTiles(gLid, lid);
                        // assigns the lid contents to the bag
                        bag->putBox(lid);
                    }
                }
            }
        }

        // clean up - close file
        saveFile.close();

        if(singleplayer) {
            dynamic_cast<AI*>(player2)->setFactory(factory);
        }

        // creates new gameManager with loaded data and continues to play
        GameManager* gameManager = new GameManager(player1, player2, turns,
                                                   factory, bag, active, singleplayer);
        gameManager->playRound();

    } else {
        saveFile.close();
        throw std::logic_error("File not found.");
    }

}

std::vector<TilePtr> loadTiles(std::string s, std::vector<TilePtr> v) {
    // for each char in the string create a new tile based on it's colour
    // REFERENCED FROM: https://stackoverflow.com/a/9438329
    for (char &c : s) {
        if (c == 'F') {
            TilePtr tile = new Tile(F);
            v.push_back(tile);
        } else if (c == 'R') {
            TilePtr tile = new Tile(R);
            v.push_back(tile);
        } else if (c == 'Y') {
            TilePtr tile = new Tile(Y);
            v.push_back(tile);
        } else if (c == 'B') {
            TilePtr tile = new Tile(B);
            v.push_back(tile);
        } else if (c == 'L') {
            TilePtr tile = new Tile(L);
            v.push_back(tile);
        } else if (c == 'U') {
            TilePtr tile = new Tile(U);
            v.push_back(tile);
        } else if (c == 'E') {
            TilePtr tile = new Tile(E);
            v.push_back(tile);
        }
    }

    // returns filled vector
    return v;
}

void
saveGame(std::string filename, Player *p1, Player *p2, Factory *f, int turn,
         int active, Bag *bag, bool AI) {

    // file directory
    std::string dir = "saves/";

    // opens file (no need to check if file exists, overwrites automatically)
    std::ofstream saveFile;
    saveFile.open(dir.append(filename));

    // Player 1
    saveFile << "$" << std::endl;
    saveFile << "type:player" << std::endl;
    saveFile << "id:" << p1->getId() << std::endl;
    saveFile << "name:" << p1->getName() << std::endl;
    saveFile << "points:" << p1->getMosaic()->getPoints() << std::endl;
    saveFile << "mosaic:" << p1->getMosaic()->getMosaicString() << std::endl;
    saveFile << "pile:" << p1->getMosaic()->getPileString() << std::endl;
    saveFile << "broken:" << p1->getMosaic()->getBrokenString() << std::endl;
    saveFile << "starter:" << p1->getMosaic()->toStart() << std::endl;
    saveFile << "#" << std::endl;

    // Player 2 / AI
    saveFile << "$" << std::endl;
    if(AI) {
        saveFile << "type:ai" << std::endl;
    } else {
        saveFile << "type:player" << std::endl;
    }
    saveFile << "id:" << p2->getId() << std::endl;
    saveFile << "name:" << p2->getName() << std::endl;
    saveFile << "points:" << p2->getMosaic()->getPoints() << std::endl;
    saveFile << "mosaic:" << p2->getMosaic()->getMosaicString() << std::endl;
    saveFile << "pile:" << p2->getMosaic()->getPileString() << std::endl;
    saveFile << "broken:" << p2->getMosaic()->getBrokenString() << std::endl;
    saveFile << "starter:" << p2->getMosaic()->toStart() << std::endl;
    saveFile << "#" << std::endl;

    // Factories
    saveFile << "$" << std::endl;
    saveFile << "type:factory" << std::endl;
    saveFile << "f1:" << f->getFactoryString(0) << std::endl;
    saveFile << "f2:" << f->getFactoryString(1) << std::endl;
    saveFile << "f3:" << f->getFactoryString(2) << std::endl;
    saveFile << "f4:" << f->getFactoryString(3) << std::endl;
    saveFile << "f5:" << f->getFactoryString(4) << std::endl;
    saveFile << "mid:" << f->getFactoryString(5) << std::endl;
    saveFile << "#" << std::endl;

    // Game Data
    saveFile << "$" << std::endl;
    saveFile << "type:game" << std::endl;
    saveFile << "turns:" << turn << std::endl;
    saveFile << "active:" << active << std::endl;
    saveFile << "seed:" << bag->getSeed() << std::endl;
    saveFile << "bag:" << bag->getBag() << std::endl;
    saveFile << "lid:" << bag->getLid() << std::endl;
    saveFile << "#" << std::endl;

    // clean up - close file
    saveFile.close();

}