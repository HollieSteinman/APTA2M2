#include <fstream>
#include <sstream>
#include "Utils.h"
#include "Player.h"
#include "GameManager.h"

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

    // int seed;
    // try{
    //     //std::cin.exceptions(std::istream::failbit);
    //     std::cin >> seed;
    // }catch(const std::ios::failure &){
    //     std::cout << "Number is invalid";
    // }
    int menu = 0;
    std::cin >> menu;

    if (menu == 1) {
         playGame(seed);
    } else if (menu == 2) {
        // loadGame();
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

void playGame(int seed){
    // Start Game
        GameManager* gameManager = new GameManager(seed);
        gameManager->startGame();
    // try {
    //     // Game Start: Play round
    //    gameManager->playRound(gameBag);
    // } catch (std::exception& e){
    //     // recover from last save
    //     std::cerr << "Exception Caught: " << e.what() << std::endl;
    // }

}

void playGame(GameManager* gameManager) {

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
        Player *player1, *player2;
        Factory *factory;
        int turns, active, seed;
        Bag *bag;

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
                std::string pId, pName, pPoints, pStarter, pMosaic,
                    pPile, pBroken, label;
                int id, points;
                bool starter;
                Mos m;
                std::vector<TilePtr> vectors[6], p1, p2, p3, p4, p5, broken;
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
                        getline(ls, pMosaic, ':');
                        std::stringstream ms(pMosaic);
                        for(int i = 0; i < 5; i++) {
                            getline(ms, pMosaic, ',');
                            for(int j = 0; j < 5; j++) {
                                char c = pMosaic[j];
                                TilePtr tile;
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
                                m[i][j] = tile;
                            }
                        }
                    } else if (label == "pile") {
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

                vectors[0] = p1;
                vectors[1] = p2;
                vectors[2] = p3;
                vectors[3] = p4;
                vectors[4] = p5;
                vectors[5] = broken;

                std::string p;

                if(id == 1) {
                    player1 = new Player(id, pName);
                    Mosaic* mosaic = new Mosaic(starter, m, points, vectors);
                    player1->setMosaic(mosaic);
                } else {
                    player2 = new Player(id, pName);
                    Mosaic* mosaic = new Mosaic(starter, m, points, vectors);
                    player2->setMosaic(mosaic);
                }


            } else if (type == "factory") {
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

                    fac = loadTiles(facContent, fac);

                    factory = new Factory();
                    factory->loadFactory(facNo, fac);
                    fac.clear();
                }
            } else if (type == "game") {
                std::string label, gTurns, gActive, gSeed, gBag, gLid;
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
                        // TODO store seed
                        getline(ls, gSeed, ':');
                        std::istringstream(gSeed) >> seed;
                    } else if (label == "bag") {
                        getline(ls, gBag, ':');
                        std::vector<TilePtr> tempBag;
                        tempBag = loadTiles(gBag, tempBag);
                        bag = new Bag(tempBag);
                    } else if (label == "lid") {
                        getline(ls, gLid, ':');
                        std::vector<TilePtr> lid;
                        lid = loadTiles(gLid, lid);
                        bag->putBox(lid);
                    }
                }
            }
        }

        saveFile.close();

        // GameManager* gameManager = new GameManager(player1, player2, turns, factory);
        // gameManager->playRound(bag);

    } else {
        // this will be a good place to throw an exception if the 
        // file entered does not exist also to check if we are using
        // multiple save files the erase an old file before rewriting
        std::cout << "File not found, returning to menu." << std::endl;
        saveFile.close();
        showMenu();
    }

}

std::vector<TilePtr> loadTiles(std::string s, std::vector<TilePtr> v) {
    for (char &c : s) {
        //TODO check referencing
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

    return v;
}

void saveGame(std::string filename, Player* p1, Player* p2, Factory* f, int turn, int active) {

    // filename for testing, change later
    std::string dir = "saves/";

    // opens file
    std::ofstream saveFile;
    saveFile.open(dir.append(filename));

    // Player 1
    saveFile << "$" << std::endl;
    saveFile << "type:player" << std::endl;
    saveFile << "id:" << p1->getId() << std::endl;
    saveFile << "name:" << p1->getName() << std::endl;
    saveFile << "points:" << p1->getMosaic()->getPoints() << std::endl;
    saveFile << "mosaic:" << p1->getMosaic()->getMosaic() << std::endl;
    saveFile << "pile:" << p1->getMosaic()->getPile() << std::endl;
    saveFile << "broken:" << p1->getMosaic()->getBroken() << std::endl;
    saveFile << "starter:" << p1->getMosaic()->toStart() << std::endl;
    saveFile << "#" << std::endl;

    // Player 2
    saveFile << "$" << std::endl;
    saveFile << "type:player" << std::endl;
    saveFile << "id:" << p2->getId() << std::endl;
    saveFile << "name:" << p2->getName() << std::endl;
    saveFile << "points:" << p2->getMosaic()->getPoints() << std::endl;
    saveFile << "mosaic:" << p2->getMosaic()->getMosaic() << std::endl;
    saveFile << "pile:" << p2->getMosaic()->getPile() << std::endl;
    saveFile << "broken:" << p2->getMosaic()->getBroken() << std::endl;
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
    saveFile << "seed:" << std::endl; // TODO save seed
    saveFile << "bag:" << std::endl; // TODO save bag & lid
    saveFile << "lid:" << std::endl;
    saveFile << "#" << std::endl;

    saveFile.close();

}