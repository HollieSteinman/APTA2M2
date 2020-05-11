#include <string>

#include "Board.h"

Board::Board(){
    // instantiate the score
    points = 0;

    // instantiate the pile
    pile = new Pile();

    // instantiate the mosaic
    for (int i = 0; i != 5; ++i){
        for (int j = 0; j != 5; ++j){
            mosaic[i][j] = new Tile();
        }
    }

    // instantiate the puzzle
    for (int i = 0; i != 5; ++i){
        for (int j = 0; j != 5; ++j){
            if (i == j){
                puzzle[i][j] = new Tile(Y);
            }
            if (j == (i + 1) || j == (i - 4)){
                puzzle[i][j] = new Tile(B);
            }
            if (j == (i + 2) || j == (i - 3)){
                puzzle[i][j] = new Tile(L);
            }
            if (j == (i + 3) || j == (i - 2)){
                puzzle[i][j] = new Tile(R);
            }
            if (j == (i + 4) || j == (i - 1)){
                puzzle[i][j] = new Tile(U);
            }
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
    std::cout << "1:     " << pile->getP1().at(0)->getChar() << "||"; 
    for (int i = 0; i < 5; ++i){
        std::cout << mosaic[0][i]->getChar();
    }
    std::cout << std::endl;
    // line 2
    std::cout << "2:    ";
    for (int i = 0; i < 2; ++i){
        std::cout << pile->getP2().at(i)->getChar();
    }
    std::cout << "||";
    for (int i = 0; i < 5; ++i){
        std::cout << mosaic[1][i]->getChar();
    }
    std::cout << std::endl;
    // line 3
    std::cout << "3:   ";
    for (int i = 0; i < 3; ++i){
        std::cout << pile->getP3().at(i)->getChar();
    }
    std::cout << "||";
    for (int i = 0; i < 5; ++i){
        std::cout << mosaic[2][i]->getChar();
    }
    std::cout << std::endl;
    // line 4
    std::cout << "4:  ";
    for (int i = 0; i < 4; ++i){
        std::cout << pile->getP4().at(i)->getChar();
    }
    std::cout << "||";
    for (int i = 0; i < 5; ++i){
        std::cout << mosaic[3][i]->getChar();
    }
    std::cout << std::endl;
    // line 5
    std::cout << "5: ";
    for (int i = 0; i < 5; ++i){
        std::cout << pile->getP5().at(i)->getChar();
    }
    std::cout << "||";
    for (int i = 0; i < 5; ++i){
        std::cout << mosaic[4][i]->getChar();
    }
    std::cout << std::endl;
    // broken tiles
    std::cout << "broken: ";
    for (int i = 0; i < 7; ++i){
        std::cout << pile->getBroken().at(i)->getChar();
    }
    std::cout << std::endl;
}

Pile* Board::getPile(){
    return pile;
}

void Board::displayPuzzle(){
    // line 1
    for (int i = 0; i < 5; ++i){
        std::cout << puzzle[0][i]->getChar() << " ";
    }
    std::cout << std::endl;
    // line 2
    for (int i = 0; i < 5; ++i){
        std::cout << puzzle[1][i]->getChar() << " ";
    }
    std::cout << std::endl;
    // line 3
    for (int i = 0; i < 5; ++i){
        std::cout << puzzle[2][i]->getChar() << " ";
    }
    std::cout << std::endl;
    // line 4
    for (int i = 0; i < 5; ++i){
        std::cout << puzzle[3][i]->getChar() << " ";
    }
    std::cout << std::endl;
    // line 5
    for (int i = 0; i < 5; ++i){
        std::cout << puzzle[4][i]->getChar() << " ";
    }
    std::cout << std::endl;
}

void Board::score(){
    for (unsigned int i = 0; i < pile->getP1().size(); ++i){
        if (pile->getP1().at(i)->getColour() != E){
            //
        }
    }
}