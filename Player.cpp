#include <string.h>

#include "Player.h"

Player::Player(int id, std::string name):
    id(id),
    name(name)
{
    board = new Board();
}

Player::~Player(){

}

int Player::getId(){
    return id;
}

std::string Player::getName(){
    return name;
}

Board* Player::getBoard(){
    return board;
}

bool Player::toStart(){
    return board->getPile()->toStart();
}
