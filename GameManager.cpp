#include "GameManager.h"

GameManager::GameManager() {

    std::string playerName1, playerName2;

    std::cout << "Enter a name for player 1" << std::endl;
    std::cout << "> ";
    std::cin >> playerName1;

    //  Create player 1

    std::cout << "Enter a name for player 2" << std::endl;
    std::cout << "> ";
    std::cin >> playerName2;

    //  Create player 2
    //  Create tiles and factories

    std::cout << "Let’s Play!" ;

    playRound();

}

GameManager::GameManager(int seed) {

    std::string playerName1, playerName2;

    std::cout << "Enter a name for player 1" << std::endl;
    std::cout << "> ";
    std::cin >> playerName1;

    plyr1 = new Player(1, playerName1);

    std::cout << "Enter a name for player 2" << std::endl;
    std::cout << "> ";
    std::cin >> playerName2;

    plyr2 = new Player(2, playerName2);
    bag = new Bag(seed);
    factory->loadFactory(bag);

    std::cout << "Let’s Play!" ;
    // variable to check if game is over
    gameOver = false;
    // make player 1 the first starter
    factory->listFactory();
    std::cout << " Mosaic for " << plyr1->getName() << std::endl;
    std::cout << "> ";



    while (!gameOver){
        playRound();
    }

}

GameManager::~GameManager() {

}

void GameManager::getRound() {

}

void GameManager::playRound() {

}

void GameManager::displayRound() {

}

Tile *GameManager::getFactory(int pile, char colour) {
    return nullptr;
}

void GameManager::generatePiles() {

}

void GameManager::setFirstPlayer(int playerID) {

}

void GameManager::saveGame() {



}

