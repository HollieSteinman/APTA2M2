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
    toBox.clear();
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
        if (pRow < 6){
            for (int i = 0; i < 5; ++i){
                if (holder[0]->getColour() == mosaic[pRow - 1][i]->getColour()){
                    throw std::out_of_range("That colour has played for this row");
                }
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
                    throw std::out_of_range("That colour does not match with the others");
                }
            }
            // if space more than number of tiles 
            if (counter >= holder.size()){
                for (unsigned int i = p1.size() - 1; i >= 0 && numTiles != 0; --i){
                    if (p1[i]->getColour() == E){
                        p1[i] = holder[0];
                        --numTiles;
                    }
                }
            }
            // if number of tiles more than space
            if (counter < holder.size()){
                // LOOP REFERENCES FROM: https://stackoverflow.com/a/24851790
                for (auto it = p1.rbegin(); it != p1.rend(); ++it)
                {
                    TilePtr tile = *it;
                    if(tile->getColour() == E) {
                        *it = holder[0];
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
                for (unsigned int i = p2.size() - 1; i >= 0 && numTiles != 0; --i){
                    if (p2[i]->getColour() == E){
                        p2[i] = holder[0];
                        --numTiles;
                    }
                }
            }
            // if number of tiles more than space
            if (counter < holder.size()){
                // LOOP REFERENCES FROM: https://stackoverflow.com/a/24851790
                for (auto it = p2.rbegin(); it != p2.rend(); ++it)
                {
                    TilePtr tile = *it;
                    if(tile->getColour() == E) {
                        *it = holder[0];
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
                for (unsigned int i = p3.size() - 1; i >= 0 && numTiles != 0; --i){
                    if (p3[i]->getColour() == E){
                        p3[i] = holder[0];
                        --numTiles;
                    }
                }
            }
            // if number of tiles more than space
            if (counter < holder.size()){
                // LOOP REFERENCES FROM: https://stackoverflow.com/a/24851790
                for (auto it = p3.rbegin(); it != p3.rend(); ++it)
                {
                    TilePtr tile = *it;
                    if(tile->getColour() == E) {
                        *it = holder[0];
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
                for (unsigned int i = p4.size() - 1; i >= 0 && numTiles != 0; --i){
                    if (p4[i]->getColour() == E){
                        p4[i] = holder[0];
                        --numTiles;
                    }
                }
            }
            // if number of tiles more than space
            if (counter < holder.size()){
                // LOOP REFERENCES FROM: https://stackoverflow.com/a/24851790
                for (auto it = p4.rbegin(); it != p4.rend(); ++it)
                {
                    TilePtr tile = *it;
                    if(tile->getColour() == E) {
                        *it = holder[0];
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
                for (unsigned int i = p5.size() - 1; i >= 0 && numTiles != 0; --i){
                    if (p5[i]->getColour() == E){
                        p5[i] = holder[0];
                        --numTiles;
                    }
                }
            }
            // if number of tiles more than space
            if (counter < holder.size()){
                // LOOP REFERENCES FROM: https://stackoverflow.com/a/24851790
                for (auto it = p5.rbegin(); it != p5.rend(); ++it)
                {
                    TilePtr tile = *it;
                    if(tile->getColour() == E) {
                        *it = holder[0];
                        --numTiles;
                    }
                }
                for (unsigned int i = 0; i < numTiles; ++i){
                    loadBroken(holder[0]);
                }
            }
        } else if(pRow == 6) {
            for(unsigned int i = 0; i < holder.size(); i++) {
                loadBroken(holder[i]);
            }
        }
    }
}

void Mosaic::loadBroken(TilePtr tile){
    broken.push_back(tile);
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
    for (unsigned int i = 0; i < broken.size(); ++i){
        std::cout << broken.at(i)->getChar();
    }
    std::cout << std::endl;
}

void Mosaic::score(){
    std::vector<TilePtr> v[5] = {p1, p2, p3, p4, p5};

    //  for each pile
    for(int i = 0; i < sizeof(v); i++) {
        //  if the pile is full
        if(v[i].size() == i + 1) {
            //  for each column in the corresponding puzzle row
            for(int j = 0; j < 5; j++) {
                //  if the tile equals the tiles in the pile
                if(puzzle[i][j]->getColour() == v[i][0]->getColour()) {
                    mosaic[i][j] = v[i][0];

                    // if not the first pile, add remainder to boxlid
                    if(i != 0) {
                        // add remaining tiles to boxlid holder
                        for (unsigned int k = 0; k < v[i].size() - 1; k++){
                            toBox.push_back(v[i][k]);
                        }
                    }

                    // clear the pile
                    for (unsigned int k = 0; k < v[i].size(); k++){
                        v[i][k] = new Tile(E);
                    }


                    int initialPoints = points;

                    // score column
                    // if the first row
                    if(i == 0 && mosaic[i + 1][j]->getColour() != E) {
                        // initial point for places tile
                        points++;
                        // for each tile connected in the column add a point
                        for(int k = i + 1; k < 5; k++) {
                            if(mosaic[k][j]->getColour() != E) {
                                points++;
                            }
                        }
                    } else if(i == 4 && mosaic[i - 1][j]->getColour() != E) {
                        // if the last row
                        // initial point for places tile
                        points++;
                        // for each tile connected in the column add a point
                        for(int k = i - 1; k >= 0; k--) {
                            if(mosaic[k][j]->getColour() != E) {
                                points++;
                            }
                        }
                    } else if(mosaic[i + 1][j]->getColour() != E
                        || mosaic[i - 1][j]->getColour() != E) {
                        // if isn't first or last row and has adjacent tiles
                        // initial point for places tile
                        points++;
                        // for each tile connected in the column add a point
                        for(int k = i + 1; k < 5; k++) {
                            if(mosaic[k][j]->getColour() != E) {
                                points++;
                            }
                        }
                        for(int k = i - 1; k >= 0; k--) {
                            if(mosaic[k][j]->getColour() != E) {
                                points++;
                            }
                        }
                    }

                    // score row
                    // if first column
                    if(j == 0 && mosaic[i][j + 1]->getColour() != E) {
                        // initial point for places tile
                        points++;
                        // for each tile connected in the row add a point
                        for(int k = j + 1; k < 5; k++) {
                            if(mosaic[i][k]->getColour() != E) {
                                points++;
                            }
                        }
                    } else if(j == 4 && mosaic[i][j - 1]->getColour() != E) {
                        // if the last row
                        // initial point for places tile
                        points++;
                        // for each tile connected in the row add a point
                        for(int k = j - 1; k >= 0; k--) {
                            if(mosaic[i][k]->getColour() != E) {
                                points++;
                            }
                        }
                    } else if(mosaic[i][j + 1]->getColour() != E
                              || mosaic[i][j - 1]->getColour() != E) {
                        // if isn't first or last column and has adjacent tiles
                        // initial point for places tile
                        points++;
                        // for each tile connected in the row add a point
                        for(int k = j + 1; k < 5; k++) {
                            if(mosaic[i][k]->getColour() != E) {
                                points++;
                            }
                        }
                        for(int k = j - 1; k >= 0; k--) {
                            if(mosaic[i][k]->getColour() != E) {
                                points++;
                            }
                        }
                    }

                    // if no adjacent, add a single point
                    if(points == initialPoints) {
                        points++;
                    }

                }
            }
        }
    }

    int counter = 0;
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
        for (unsigned int i = 0; i < broken.size(); ++i){
            if (broken[i]->getColour() == F){
                points -= 1;
                broken[i] = new Tile(E);
                // starter = false;
            }
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

    broken.clear();

    // check if the game is over and set gameover
    // check mosaic row 1
    for (int i = 0; i < 5; ++i){
        if (mosaic[0][i]->getColour() == E){
            ++counter;
        }
    }
    if (counter == 0){
        gameover = true;
    }
    counter = 0;
    // check mosaic row 2
    for (int i = 0; i < 5; ++i){
        if (mosaic[1][i]->getColour() == E){
            ++counter;
        }
    }
    if (counter == 0){
        gameover = true;
    }
    counter = 0;
    // check mosaic row 3
    for (int i = 0; i < 5; ++i){
        if (mosaic[2][i]->getColour() == E){
            ++counter;
        }
    }
    if (counter == 0){
        gameover = true;
    }
    counter = 0;
    // check mosaic row 4
    for (int i = 0; i < 5; ++i){
        if (mosaic[3][i]->getColour() == E){
            ++counter;
        }
    }
    if (counter == 0){
        gameover = true;
    }
    counter = 0;
    // check mosiac row 5
    for (int i = 0; i < 5; ++i){
        if (mosaic[4][i]->getColour() == E){
            ++counter;
        }
    }
    if (counter == 0){
        gameover = true;
    }
    counter = 0;
}

void Mosaic::endScore() {
    int tiles;

    // completed rows
    for(int i = 0; i < 5; i++) {
        tiles = 0;
        for(int j = 0; j < 5; j++) {
            if(mosaic[i][j]->getColour() != E) {
                tiles++;
            }
        }
        if(tiles == 5) {
            points += 2;
        }
    }

    // completed columns
    for(int i = 0; i < 5; i++) {
        tiles = 0;
        for(int j = 0; j < 5; j++) {
            if(mosaic[j][i]->getColour() != E) {
                tiles++;
            }
        }
        if(tiles == 5) {
            points += 7;
        }
    }

    // set of colours
    int r = 0;
    int y = 0;
    int b = 0;
    int l = 0;
    int u = 0;

    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            if(mosaic[i][j]->getColour() == R) {
                r++;
            } else if(mosaic[i][j]->getColour() == Y) {
                y++;
            } else if(mosaic[i][j]->getColour() == B) {
                b++;
            } else if(mosaic[i][j]->getColour() == L) {
                l++;
            } else if(mosaic[i][j]->getColour() == U) {
                u++;
            }
        }
    }

    if(r == 5) {
        points += 10;
    }
    if(y == 5) {
        points += 10;
    }
    if(b == 5) {
        points += 10;
    }
    if(l == 5) {
        points += 10;
    }
    if(u == 5) {
        points += 10;
    }

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

std::string Mosaic::getMosaicString() {
    std::string m;

    // iterates through the 2D array
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            // creates a string of length 1 from the returned char
            std::string t(1, mosaic[i][j]->getColourChar());
            // appends string with colour char
            m = m.append(t);
        }
        if(i != 4) {
            // if not the last array, include delimiter ','
            m = m.append(",");
        }
    }

    return m;
}

std::string Mosaic::getPileString() {
    // REFERENCED FROM: https://www.geeksforgeeks.org/array-of-vectors-in-c-stl/
    std::string p;

    // create an array of vectors to iterate through of just the piles
    std::vector<TilePtr> pile[5] = {p1, p2, p3, p4, p5};

    // iterates through each pile
    for(int i = 0; i < 5; i++) {

        for (auto it = pile[i].begin();
             it != pile[i].end(); it++) {

            // create a tile object from the iterator
            TilePtr tilePtr = *it;
            // creates a string of length 1 from the returned char
            std::string t(1, tilePtr->getColourChar());
            // appends string with colour char
            p = p.append(t);
        }

        if(i != 4) {
            // if not the last array, include delimiter ','
            p = p.append(",");
        }
    }

    return p;
}

std::string Mosaic::getBrokenString() {
    std::string b;

    // LOOP REFERENCED FROM: https://www.geeksforgeeks.org/array-of-vectors-in-c-stl/
    for (auto it = broken.begin();
         it != broken.end(); it++) {

        // create a tile object from the iterator
        TilePtr tilePtr = *it;
        // creates a string of length 1 from the returned char
        std::string t(1, tilePtr->getColourChar());
        // appends string with colour char
        b = b.append(t);
    }

    return b;
}

void Mosaic::startReset(){
    starter = false;
}

TilePtr** Mosaic::getMosaic() {
    TilePtr** toReturn = new TilePtr*[5];

    for(int i = 0; i < 5; i++) {
        toReturn[i] = new TilePtr[5];
        for(int j = 0; j < 5; j++) {
            toReturn[i][j] = mosaic[i][j];
        }
    }

    return toReturn;
}

std::vector<TilePtr>* Mosaic::getVectors() {
    std::vector<TilePtr> v[6];
    std::copy(p1.begin(), p1.end(), back_inserter(v[0]));
    std::copy(p2.begin(), p2.end(), back_inserter(v[1]));
    std::copy(p3.begin(), p3.end(), back_inserter(v[2]));
    std::copy(p4.begin(), p4.end(), back_inserter(v[3]));
    std::copy(p5.begin(), p5.end(), back_inserter(v[4]));
    std::copy(broken.begin(), broken.end(), back_inserter(v[5]));
    return v;
}
