#include <string.h>

#include "Player.h"

Player::Player(int id):
    id(id)
{
    board = new Board();
}

Player::~Player(){

}

int Player::getId(){
    return id;
}

Board* Player::getBoard(){
    return board;
}

bool Player::toStart(){
    return board->getPile()->toStart();
}
