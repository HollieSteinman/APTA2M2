#include "Player.h"

Player::Player(int id, std::string name) {
    Player::name = name;
    Player::id = id;
}

Player::~Player() {
}

int Player::getId() {
    return id;
}

std::string Player::getName() {
    return name;
}

Board Player::getBoard() {
    return nullptr;
}

void Player::setBoard(Board board) {

}

