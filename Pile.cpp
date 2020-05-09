#include <string>

#include "Pile.h"

Pile::Pile(){
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
}

Pile::~Pile(){
    p1.clear();
    p2.clear();
    p3.clear();
    p4.clear();
    p5.clear();
    broken.clear();
}

void Pile::loadPile(Factory* factory, unsigned int fRow, Colour colour, unsigned int pRow){
    
    // check that valid factory row and pile row is entered
    if (fRow > 5 || pRow > 5){
        throw std::out_of_range("Invalid selection, please reselect");
    } else {
        // get the tiles from the factory row
        std::vector<TilePtr> holder = factory->getTiles(colour, fRow);
        unsigned int counter = 0;
        unsigned int numTiles = holder.size();
        if ( pRow == 1){
            // get the number of empty spaces
            for (unsigned int i = 0; i < p1.size(); ++i){
                if (p1[i]->getColour() == E){
                    ++counter;
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

void Pile::loadBroken(TilePtr tile){
    broken.push_back(tile);
}

std::vector<TilePtr> Pile::getP1(){
    return p1;
}

std::vector<TilePtr> Pile::getP2(){
    return p2;
}

std::vector<TilePtr> Pile::getP3(){
    return p3;
}

std::vector<TilePtr> Pile::getP4(){
    return p4;
}

std::vector<TilePtr> Pile::getP5(){
    return p5;
}

std::vector<TilePtr> Pile::getBroken(){
    return broken;
}