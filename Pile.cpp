#include <string>

#include "Pile.h"

Pile::Pile(){
    for (int i = 0; i < 1; ++i){
        p1[i] = new Tile();
    }
    for (int i = 0; i < 2; ++i){
        p2[i] = new Tile();
    }
    for (int i = 0; i < 3; ++i){
        p3[i] = new Tile();
    }
    for (int i = 0; i < 4; ++i){
        p4[i] = new Tile();
    }
    for (int i = 0; i < 5; ++i){
        p5[i] = new Tile();
    }
    for (int i = 0; i < 9; ++i){
        broken[i] = new Tile();
    }
    // p1.resize(1);
    // p2.resize(2);
    // p3.resize(3);
    // p4.resize(4);
    // p5.resize(5);
    // broken.resize(9);
    // p1.reserve(1);
    // p2.reserve(2);
    // p3.reserve(3);
    // p4.reserve(4);
    // p5.reserve(5);
    // broken.reserve(9);
}

Pile::~Pile(){
    p1.clear();
    p2.clear();
    p3.clear();
    p4.clear();
    p5.clear();
    broken.clear();
}

void Pile::loadPile(Factory* factory, Colour colour, unsigned int row){
    if (row < 0 || row > 5){
        // check that a valid row is entered
        throw std::out_of_range("Please choose a valid Pile row");

    } else {
        // Temporary variable to hold the pile
        std::vector<TilePtr> holder;
        // Temporary variable to load broken
        unsigned int counter = 0;

        if (row == 1){
            holder = factory->getTiles(colour);
            if (p1.size() < row){
                int sizer = row - p1.size();
                for (int i = 0; i < sizer; ++i){
                    p1.push_back(holder[i]);
                    ++counter;
                }
            }
            if (holder.size() > counter || p1.size() > row){
                int sizer = holder.size() - counter;
                for (int i = 0; i < sizer; ++i){
                    loadBroken(holder[i]);
                }
            }
        } else if (row == 2){
            holder = factory->getTiles(colour);
            if (p2.size() < row){
                int sizer = row - p2.size();
                for (int i = 0; i < sizer; ++i){
                    p2.push_back(holder[i]);
                    ++counter;
                }
            }
            if (holder.size() > counter || p2.size() > row){
                int sizer = holder.size() - counter;
                for (int i = 0; i < sizer; ++i){
                    loadBroken(holder[i]);
                }
            }
        } else if (row == 3){
            holder = factory->getTiles(colour);
            if (p3.size() < row){
                int sizer = row - p3.size();
                for (int i = 0; i < sizer; ++i){
                    p3.push_back(holder[i]);
                    ++counter;
                }
            }
            if (holder.size() > counter || p3.size() > row){
                int sizer = holder.size() - counter;
                for (int i = 0; i < sizer; ++i){
                    loadBroken(holder[i]);
                }
            }
        } else if (row == 4){
            holder = factory->getTiles(colour);
            if (p4.size() < row){
                int sizer = row - p4.size();
                for (int i = 0; i < sizer; ++i){
                    p4.push_back(holder[i]);
                    ++counter;
                }
            }
            if (holder.size() > counter || p4.size() > row){
                int sizer = holder.size() - counter;
                for (int i = 0; i < sizer; ++i){
                    loadBroken(holder[i]);
                }
            }
        } else if (row == 5){
            holder = factory->getTiles(colour);
            if (p5.size() < row){
                int sizer = row - p5.size();
                for (int i = 0; i < sizer; ++i){
                    p5.push_back(holder[i]);
                    ++counter;
                }
            }
            if (holder.size() > counter || p5.size() > row){
                int sizer = holder.size() - counter;
                for (int i = 0; i < sizer; ++i){
                    loadBroken(holder[i]);
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