#include <string>

#include "Mosaic.h"

Mosaic::Mosaic(){
    // instantiate an empty Pile
    // to prevent segfault
    for (int i = 0; i < 1; ++i){
        p1.push_back(new Tile(E));
    }
    for (int i = 0; i < 2; ++i){
        p2.push_back(new Tile(E));
    }
    for (int i = 0; i < 3; ++i){
        p3.push_back(new Tile(E));
    }
    for (int i = 0; i < 4; ++i){
        p4.push_back(new Tile(E));
    }
    for (int i = 0; i < 5; ++i){
        p5.push_back(new Tile(E));
    }
    for (int i = 0; i < 7; ++i){
        broken.push_back(new Tile(E));
    }

    // instantiate the score
    points = 0;

    // instantiate the starter variable
    starter = false;

    // instantiate the gameover variable
    gameover = false;

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

Mosaic::Mosaic(bool s, Mos m, int p, std::vector<TilePtr> v[6]) {

    starter = s;
    points = p;
    std::copy(v[0].begin(), v[0].end(), back_inserter(p1));
    std::copy(v[1].begin(), v[1].end(), back_inserter(p2));
    std::copy(v[2].begin(), v[2].end(), back_inserter(p3));
    std::copy(v[3].begin(), v[3].end(), back_inserter(p4));
    std::copy(v[4].begin(), v[4].end(), back_inserter(p5));
    std::copy(v[5].begin(), v[5].end(), back_inserter(broken));

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

    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            mosaic[i][j] = m[i][j];
        };
    }

}

Mosaic::~Mosaic(){
    // clear the pile
    p1.clear();
    p2.clear();
    p3.clear();
    p4.clear();
    p5.clear();
    broken.clear();
}

int Mosaic::getPoints(){
    return points;
}

void Mosaic::loadPile(Factory* factory, unsigned int fRow, Colour colour, unsigned int pRow){
    
    // check that valid factory row and pile row is entered
    if (fRow > 5 || pRow > 6){
        throw std::out_of_range("Invalid selection, please reselect");
    } else {
        // get the tiles from the factory row
        std::vector<TilePtr> holder = factory->getTiles(colour, fRow);
        // check if the mosiac row has been filled
        for (int i = 0; i < 5; ++i){
            if (holder[0]->getColour() == mosaic[pRow - 1][i]->getColour()){
                throw std::out_of_range("That colour has played for this row");
            }
        }
        // check if the player that owns this mosaic  
        // should play first next round
        if (holder[0]->getColour() == F){
            loadBroken(holder[0]);
            holder.erase(holder.begin() + 0);
            starter = true;
        }
        // variable to count empty spaces
        unsigned int counter = 0;
        // variable to count number of tiles 
        // selected from the factory
        unsigned int numTiles = holder.size();
        if ( pRow == 1){
            // get the number of empty spaces
            for (unsigned int i = 0; i < p1.size(); ++i){
                if (p1[i]->getColour() == E){
                    ++counter;
                }
            }
            // check that there are empty spaces
            if (counter == 0){
                throw std::out_of_range("There is no empty space in that row");
            }
            // if pile row is not empty 
            // check that colour matches
            if (counter < p1.size()){
                if (holder[0]->getColour() != p1[0]->getColour() && p1[0]->getColour() != E){
                    throw std::out_of_range("That colour does mot match with the others");
                }
            }
            // if space more than number of tiles 
            if (counter >= holder.size()){
                for (unsigned int i = 0; i < p1.size() && numTiles != 0; ++i){
                    if (p1[i]->getColour() == E){
                        p1[i] = holder[0];
                        --numTiles;
                    }
                }
            }
            // if number of tiles more than space
            if (counter < holder.size()){
                for (unsigned int i = 0; i < p1.size(); ++i){
                    if (p1[i]->getColour() == E){
                        p1[i] = holder[0];
                        --numTiles;
                    }
                }
                for (unsigned int i = 0; i < numTiles; ++i){
                    loadBroken(holder[0]);
                }
            }
        } else if (pRow == 2){
            // get the number of empty spaces
            for (unsigned int i = 0; i < p2.size(); ++i){
                if (p2[i]->getColour() == E){
                    ++counter;
                }
            }
            // check that there are empty spaces
            if (counter == 0){
                throw std::out_of_range("There is no empty space in that row");
            }
            // if pile row is not empty 
            // check that colour matches
            if (counter < p2.size()){
                if (holder[0]->getColour() != p2[0]->getColour() && p2[0]->getColour() != E){
                    throw std::out_of_range("That colour does mot match with the others");
                }
            }
            // if space more than number of tiles 
            if (counter >= holder.size()){
                for (unsigned int i = 0; i < p2.size() && numTiles != 0; ++i){
                    if (p2[i]->getColour() == E){
                        p2[i] = holder[0];
                        --numTiles;
                    }
                }
            }
            // if number of tiles more than space
            if (counter < holder.size()){
                for (unsigned int i = 0; i < p1.size(); ++i){
                    if (p2[i]->getColour() == E){
                        p2[i] = holder[0];
                        --numTiles;
                    }
                }
                for (unsigned int i = 0; i < numTiles; ++i){
                    loadBroken(holder[0]);
                }
            }
        } else if (pRow == 3){
            // get the number of empty spaces
            for (unsigned int i = 0; i < p3.size(); ++i){
                if (p3[i]->getColour() == E){
                    ++counter;
                }
            }
            // check that there are empty spaces
            if (counter == 0){
                throw std::out_of_range("There is no empty space in that row");
            }
            // if pile row is not empty 
            // check that colour matches
            if (counter < p3.size()){
                if (holder[0]->getColour() != p3[0]->getColour() && p3[0]->getColour() != E){
                    throw std::out_of_range("That colour does mot match with the others");
                }
            }
            // if space more than number of tiles 
            if (counter >= holder.size()){
                for (unsigned int i = 0; i < p3.size() && numTiles != 0; ++i){
                    if (p3[i]->getColour() == E){
                        p3[i] = holder[0];
                        --numTiles;
                    }
                }
            }
            // if number of tiles more than space
            if (counter < holder.size()){
                for (unsigned int i = 0; i < p3.size(); ++i){
                    if (p3[i]->getColour() == E){
                        p3[i] = holder[0];
                        --numTiles;
                    }
                }
                for (unsigned int i = 0; i < numTiles; ++i){
                    loadBroken(holder[0]);
                }
            }
        } else if (pRow == 4){
            // get the number of empty spaces
            for (unsigned int i = 0; i < p4.size(); ++i){
                if (p4[i]->getColour() == E){
                    ++counter;
                }
            }
            // check that there are empty spaces
            if (counter == 0){
                throw std::out_of_range("There is no empty space in that row");
            }
            // if pile row is not empty 
            // check that colour matches
            if (counter < p4.size()){
                if (holder[0]->getColour() != p4[0]->getColour() && p4[0]->getColour() != E){
                    throw std::out_of_range("That colour does mot match with the others");
                }
            }
            // if space more than number of tiles 
            if (counter >= holder.size()){
                for (unsigned int i = 0; i < p4.size() && numTiles != 0; ++i){
                    if (p4[i]->getColour() == E){
                        p4[i] = holder[0];
                        --numTiles;
                    }
                }
            }
            // if number of tiles more than space
            if (counter < holder.size()){
                for (unsigned int i = 0; i < p4.size(); ++i){
                    if (p4[i]->getColour() == E){
                        p4[i] = holder[0];
                        --numTiles;
                    }
                }
                for (unsigned int i = 0; i < numTiles; ++i){
                    loadBroken(holder[0]);
                }
            }
        } else if (pRow == 5){
            // get the number of empty spaces
            for (unsigned int i = 0; i < p5.size(); ++i){
                if (p5[i]->getColour() == E){
                    ++counter;
                }
            }
            // check that there are empty spaces
            if (counter == 0){
                throw std::out_of_range("There is no empty space in that row");
            }
            // if pile row is not empty 
            // check that colour matches
            if (counter < p5.size()){
                if (holder[0]->getColour() != p5[0]->getColour() && p5[0]->getColour() != E){
                    throw std::out_of_range("That colour does mot match with the others");
                }
            }
            // if space more than number of tiles 
            if (counter >= holder.size()){
                for (unsigned int i = 0; i < p5.size() && numTiles != 0; ++i){
                    if (p5[i]->getColour() == E){
                        p5[i] = holder[0];
                        --numTiles;
                    }
                }
            }
            // if number of tiles more than space
            if (counter < holder.size()){
                for (unsigned int i = 0; i < p5.size(); ++i){
                    if (p5[i]->getColour() == E){
                        p5[i] = holder[0];
                        --numTiles;
                    }
                }
                for (unsigned int i = 0; i < numTiles; ++i){
                    loadBroken(holder[0]);
                }
            }
        }
    }
}

void Mosaic::loadBroken(TilePtr tile){
    // Variable to ckeck once the first 
    // empty space is reached
    int count = 0;
    for (int i = 0; i < 7 && count != 1; ++i){
        if (broken[i]->getColour() == E){
            broken[i] = tile;
            ++count;
        }
    }
}

void Mosaic::displayMosaic(){
    // line 1
    std::cout << "1:     " << p1.at(0)->getChar() << "|| ";
    for (int i = 0; i < 5; ++i){
        std::cout << mosaic[0][i]->getChar();
    }
    std::cout << " ||";
    for (int i = 0; i < 5; ++i){
        std::cout << puzzle[0][i]->getChar() << " ";
    }
    std::cout << std::endl;

    // line 2
    std::cout << "2:    ";
    for (int i = 0; i < 2; ++i){
        std::cout << p2.at(i)->getChar();
    }
    std::cout << "|| ";
    for (int i = 0; i < 5; ++i){
        std::cout << mosaic[1][i]->getChar();
    }
    std::cout << " ||";
    for (int i = 0; i < 5; ++i){
        std::cout << puzzle[1][i]->getChar() << " ";
    }
    std::cout << std::endl;

    // line 3
    std::cout << "3:   ";
    for (int i = 0; i < 3; ++i){
        std::cout << p3.at(i)->getChar();
    }
    std::cout << "|| ";
    for (int i = 0; i < 5; ++i){
        std::cout << mosaic[2][i]->getChar();
    }
    std::cout << " ||";
    for (int i = 0; i < 5; ++i){
        std::cout << puzzle[2][i]->getChar() << " ";
    }
    std::cout << std::endl;

    // line 4
    std::cout << "4:  ";
    for (int i = 0; i < 4; ++i){
        std::cout << p4.at(i)->getChar();
    }
    std::cout << "|| ";
    for (int i = 0; i < 5; ++i){
        std::cout << mosaic[3][i]->getChar();
    }
    std::cout << " ||";
    for (int i = 0; i < 5; ++i){
        std::cout << puzzle[3][i]->getChar() << " ";
    }
    std::cout << std::endl;

    // line 5
    std::cout << "5: ";
    for (int i = 0; i < 5; ++i){
        std::cout << p5.at(i)->getChar();
    }
    std::cout << "|| ";
    for (int i = 0; i < 5; ++i){
        std::cout << mosaic[4][i]->getChar();
    }
    std::cout << " ||";
    for (int i = 0; i < 5; ++i){
        std::cout << puzzle[4][i]->getChar() << " ";
    }
    std::cout << std::endl;

    // broken tiles
    std::cout << "broken: ";
    for (int i = 0; i < 7; ++i){
        std::cout << broken.at(i)->getChar();
    }
    std::cout << std::endl;
}

void Mosaic::score(){
    // score first pile
    // check that no empty spaces in pile row
    unsigned int counter = 0;
    for (unsigned int i = 0; i < p1.size(); ++i){
        if (p1[i]->getColour() != E){
            ++counter;
        }
    }
    // check that pile row is full
    if (counter == p1.size()){
        // set the tile in the mosaic
        for (int i = 0; i < 5; ++i){
            if (p1[0]->getColour() == puzzle[0][i]->getColour()){
                mosaic[0][i] = p1[0];
                points += 2;// score
                p1[0] = new Tile(E);// empty pile
            }
        }
        counter = 0;
    } else {
        // reset counter
        counter = 0;
    }

    // score pile 2
    // check that no empty spaces in pile row
    for (unsigned int i = 0; i < p2.size(); ++i){
        if (p2[i]->getColour() != E){
            ++counter;
        }
    }
    // check that pile row is full
    if (counter == p2.size()){
        // set the tile in the mosaic
        for (int i = 0; i < 5; ++i){
            if (p2[0]->getColour() == puzzle[1][i]->getColour()){
                mosaic[1][i] = p2[0];
                points += 2;// score
            }
        }
        // add remaining tiles to boxlid holder
        for (unsigned int i = 0; i < p2.size() - 1; ++i){
            toBox.push_back(p2[i]);
        }
        // clear the pile
        for (unsigned int i = 0; i < p2.size(); ++i){
            p2[i] = new Tile(E);
        }
        counter = 0;
    } else {
        // reset counter
        counter = 0;
    }

    // score pile 3
    // check that no empty spaces in pile row
    for (unsigned int i = 0; i < p3.size(); ++i){
        if (p3[i]->getColour() != E){
            ++counter;
        }
    }
    // check that pile row is full
    if (counter == p3.size()){
        // set the tile in the mosaic
        for (int i = 0; i < 5; ++i){
            if (p3[0]->getColour() == puzzle[2][i]->getColour()){
                mosaic[2][i] = p3[0];
                points += 2;// score
            }
        }
        // add remaining tiles to boxlid holder
        for (unsigned int i = 0; i < p3.size() - 1; ++i){
            toBox.push_back(p3[i]);
        }
        // clear the pile
        for (unsigned int i = 0; i < p3.size(); ++i){
            p3[i] = new Tile(E);
        }
        counter = 0;
    } else {
        // reset counter
        counter = 0;
    }

    // score pile 4
    // check that no empty spaces in pile row
    for (unsigned int i = 0; i < p4.size(); ++i){
        if (p4[i]->getColour() != E){
            ++counter;
        }
    }
    // check that pile row is full
    if (counter == p4.size()){
        // set the tile in the mosaic
        for (int i = 0; i < 5; ++i){
            if (p4[0]->getColour() == puzzle[3][i]->getColour()){
                mosaic[3][i] = p4[0];
                points += 2;// score
            }
        }
        // add remaining tiles to boxlid holder
        for (unsigned int i = 0; i < p4.size() - 1; ++i){
            toBox.push_back(p4[i]);
        }
        // clear the pile
        for (unsigned int i = 0; i < p4.size(); ++i){
            p4[i] = new Tile(E);
        }
        counter = 0;
    } else {
        // reset counter
        counter = 0;
    }

    // score pile 5
    // check that no empty spaces in pile row
    for (unsigned int i = 0; i < p5.size(); ++i){
        if (p5[i]->getColour() != E){
            ++counter;
        }
    }
    // check that pile row is full
    if (counter == p5.size()){
        // set the tile in the mosaic
        for (int i = 0; i < 5; ++i){
            if (p5[0]->getColour() == puzzle[4][i]->getColour()){
                mosaic[4][i] = p5[0];
                points += 2;// score
            }
        }
        // add remaining tiles to boxlid holder
        for (unsigned int i = 0; i < p5.size() - 1; ++i){
            toBox.push_back(p5[i]);
        }
        // clear the pile
        for (unsigned int i = 0; i < p5.size(); ++i){
            p5[i] = new Tile(E);
        }
        counter = 0;
    } else {
        // reset counter
        counter = 0;
    }

    // score broken tiles
    // check that broken tiles is not empty
    for (unsigned int i = 0; i < broken.size(); ++i){
        if (broken[i]->getColour() == E){
            ++counter;
        }
    }
    // check that broken has tiles in it
    if (counter < broken.size()){
        // check if first player 
        if (broken[0]->getColour() == F){
            points -= 1;
            broken[0] = new Tile(E);
            starter = false;
        }
        // score the rest of broken
        for (unsigned int i = 0; i < broken.size(); ++i){
            if (broken[i]->getColour() != E){
                if (i >= 0 && i <= 2){
                    toBox.push_back(broken[i]);
                    broken[i] = new Tile(E);
                    points -= 1;
                }
                if (i >= 3 && i <= 4){
                    toBox.push_back(broken[i]);
                    broken[i] = new Tile(E);
                    points -= 2;
                }
                if (i >= 5 && i <= 6){
                    toBox.push_back(broken[i]);
                    broken[i] = new Tile(E);
                    points -= 3;
                }
            }
        }
        counter = 0;
    } else {
        // reset counter
        counter = 0;
    }

    // check if the game is over and set gameover
    // check mosaic row 1
    for (int i = 0; i < 5; ++i){
        if (mosaic[0][i]->getColour() != E){
            ++counter;
        }
    }
    if (counter == 0){
        gameover = true;
    }
    counter = 0;
    // check mosaic row 2
    for (int i = 0; i < 5; ++i){
        if (mosaic[1][i]->getColour() != E){
            ++counter;
        }
    }
    if (counter == 0){
        gameover = true;
    }
    counter = 0;
    // check mosaic row 3
    for (int i = 0; i < 5; ++i){
        if (mosaic[2][i]->getColour() != E){
            ++counter;
        }
    }
    if (counter == 0){
        gameover = true;
    }
    counter = 0;
    // check mosaic row 4
    for (int i = 0; i < 5; ++i){
        if (mosaic[3][i]->getColour() != E){
            ++counter;
        }
    }
    if (counter == 0){
        gameover = true;
    }
    counter = 0;
    // check mosiac row 5
    for (int i = 0; i < 5; ++i){
        if (mosaic[4][i]->getColour() != E){
            ++counter;
        }
    }
    if (counter == 0){
        gameover = true;
    }
    counter = 0;
}

std::vector<TilePtr> Mosaic::getToBox(){
    return toBox;
}

void Mosaic::clearToBox(){
    toBox.clear();
}

bool Mosaic::isGameover(){
    return gameover;
}

bool Mosaic::toStart(){
    return starter;
}

std::vector<TilePtr> Mosaic::getBrokenTile() {
    return broken;
}

std::string Mosaic::getMosaic() {
    std::string m;

    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            std::string t(1, mosaic[i][j]->getColourChar());
            m = m.append(t);
        }
        if(i != 4) {
            m = m.append(",");
        }
    }

    return m;
}

std::string Mosaic::getPile() {
    std::string p;

    std::vector<TilePtr> pile[5] = {p1, p2, p3, p4, p5};

    for(int i = 0; i < 5; i++) {
        for (auto it = pile[i].begin();
             it != pile[i].end(); it++) {

            TilePtr tilePtr = *it;
            std::string t(1, tilePtr->getColourChar());
            p = p.append(t);
        }

        if(i != 4) {
            p = p.append(",");
        }
    }

    return p;
}

std::string Mosaic::getBroken() {
    std::string b;

    for (auto it = broken.begin();
         it != broken.end(); it++) {

        TilePtr tilePtr = *it;
        std::string t(1, tilePtr->getColourChar());
        b = b.append(t);
    }

    std::cout << b << std::endl;
    return b;
}