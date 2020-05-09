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
    // if (row < 0 || row > 5){
    //     // check that a valid row is entered
    //     throw std::out_of_range("Please choose a valid Pile row");

    // } else {
    //     // Temporary variable to hold the pile
    //     std::vector<TilePtr> holder;
    //     // Temporary variable to load broken
    //     unsigned int counter = 0;

    //     if (row == 1){
    //         holder = factory->getTiles(colour);
    //         if (p1.size() < row){
    //             int sizer = row - p1.size();
    //             for (int i = 0; i < sizer; ++i){
    //                 p1.push_back(holder[i]);
    //                 ++counter;
    //             }
    //         }
    //         if (holder.size() > counter || p1.size() > row){
    //             int sizer = holder.size() - counter;
    //             for (int i = 0; i < sizer; ++i){
    //                 loadBroken(holder[i]);
    //             }
    //         }
    //     } else if (row == 2){
    //         holder = factory->getTiles(colour);
    //         if (p2.size() < row){
    //             int sizer = row - p2.size();
    //             for (int i = 0; i < sizer; ++i){
    //                 p2.push_back(holder[i]);
    //                 ++counter;
    //             }
    //         }
    //         if (holder.size() > counter || p2.size() > row){
    //             int sizer = holder.size() - counter;
    //             for (int i = 0; i < sizer; ++i){
    //                 loadBroken(holder[i]);
    //             }
    //         }
    //     } else if (row == 3){
    //         holder = factory->getTiles(colour);
    //         if (p3.size() < row){
    //             int sizer = row - p3.size();
    //             for (int i = 0; i < sizer; ++i){
    //                 p3.push_back(holder[i]);
    //                 ++counter;
    //             }
    //         }
    //         if (holder.size() > counter || p3.size() > row){
    //             int sizer = holder.size() - counter;
    //             for (int i = 0; i < sizer; ++i){
    //                 loadBroken(holder[i]);
    //             }
    //         }
    //     } else if (row == 4){
    //         holder = factory->getTiles(colour);
    //         if (p4.size() < row){
    //             int sizer = row - p4.size();
    //             for (int i = 0; i < sizer; ++i){
    //                 p4.push_back(holder[i]);
    //                 ++counter;
    //             }
    //         }
    //         if (holder.size() > counter || p4.size() > row){
    //             int sizer = holder.size() - counter;
    //             for (int i = 0; i < sizer; ++i){
    //                 loadBroken(holder[i]);
    //             }
    //         }
    //     } else if (row == 5){
    //         holder = factory->getTiles(colour);
    //         if (p5.size() < row){
    //             int sizer = row - p5.size();
    //             for (int i = 0; i < sizer; ++i){
    //                 p5.push_back(holder[i]);
    //                 ++counter;
    //             }
    //         }
    //         if (holder.size() > counter || p5.size() > row){
    //             int sizer = holder.size() - counter;
    //             for (int i = 0; i < sizer; ++i){
    //                 loadBroken(holder[i]);
    //             }
    //         }
    //     }

    // }
    // check that valid factory row and pile row is entered
    if (fRow > 5 || pRow > 5){
        throw std::out_of_range("Invalid selection, please reselect");
    } else {
        // get the tiles from the factory row
        std::vector<TilePtr> holder = factory->getTiles(colour, fRow);
        int counter = 0;
        if ( pRow == 1){
            for (unsigned int i = 0; i < p1.size(); ++i){
                if (p1[i]->getColour() == E){
                    
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