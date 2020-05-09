#include <string>

#include "Board.h"

Board::Board(){
    // instantiate the score
    points = 0;

    // instantiate the mosaic
    for(int i = 0; i != 5; ++i){
            for(int j = 0; j != 5; ++j){
                mosaic[i][j] = new Tile();
            }
        }

}

Board::~Board(){

}

int Board::getPoints(){
    return points;
}

void Board::setPoints(int points){
    // try to do this in score function
}

void Board::displayBoard(){
    // line 1
    std::cout << "    " << pile->getP1().at(0)->getChar() << "||"; 
    for (int i = 0; i < 5; ++i){
        std::cout << mosaic[0][i]->getChar();
    }
    std::cout << std::endl;
    // line 2
    std::cout << "   ";
    for (int i = 0; i < 2; ++i){
        std::cout << pile->getP2().at(i)->getChar();
    }
    std::cout << "||";
    for (int i = 0; i < 5; ++i){
        std::cout << mosaic[1][i]->getChar();
    }
    std::cout << std::endl;
    // line 3
    std::cout << "  ";
    for (int i = 0; i < 3; ++i){
        std::cout << pile->getP3().at(i)->getChar();
    }
    std::cout << "||";
    for (int i = 0; i < 5; ++i){
        std::cout << mosaic[2][i]->getChar();
    }
    std::cout << std::endl;
    // line 4
    std::cout << " ";
    for (int i = 0; i < 4; ++i){
        std::cout << pile->getP4().at(i)->getChar();
    }
    std::cout << "||";
    for (int i = 0; i < 5; ++i){
        std::cout << mosaic[3][i]->getChar();
    }
    std::cout << std::endl;
    // line 5
    for (int i = 0; i < 5; ++i){
        std::cout << pile->getP5().at(i)->getChar();
    }
    std::cout << "||";
    for (int i = 0; i < 5; ++i){
        std::cout << mosaic[4][i]->getChar();
    }
    std::cout << std::endl;
}