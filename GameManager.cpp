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

    std::cout << "Let’s Play!";

    playRound();

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

