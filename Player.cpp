#include <string.h>

#include "Player.h"

Player::Player(int id, std::string name):
    id(id),
    name(name)
{
    mosaic = new Mosaic();
}

Player::~Player(){

}

int Player::getId(){
    return id;
}

std::string Player::getName(){
    return name;
}

Mosaic* Player::getMosaic(){
    return mosaic;
}

bool Player::toStart(){
    return mosaic->toStart();
}

void Player::playTurn(Factory* factory,unsigned int fRow, Colour colour,unsigned int pRow){
    mosaic->loadPile(factory, fRow, colour, pRow);
}