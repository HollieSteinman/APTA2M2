#include <string>

#include "Factory.h"

Factory::Factory(){
    center.push_back(new Tile(F));

    // prevent segfault
    for (int i = 0; i < 4; ++i){
        fa1.push_back(new Tile(E));
    }
    for (int i = 0; i < 4; ++i){
        fa2.push_back(new Tile(E));
    }
    for (int i = 0; i < 4; ++i){
        fa3.push_back(new Tile(E));
    }
    for (int i = 0; i < 4; ++i){
        fa4.push_back(new Tile(E));
    }
    for (int i = 0; i < 4; ++i){
        fa5.push_back(new Tile(E));
    }
}

Factory::~Factory(){
    center.clear();
    fa1.clear();
    fa2.clear();
    fa3.clear();
    fa4.clear();
    fa5.clear();
}

std::vector<TilePtr> Factory::getTiles(Colour colour, int line){
    
    if (line < 0 || line > 5){
        throw std::out_of_range("Wrong row selected");
    } else {
        std::vector<TilePtr> toReturn;
        std::vector<TilePtr> holder;
        if (line == 0){
            // check if the center has been picked
            // during this round
            if (center[0]->getColour() == F){
                toReturn.push_back(center[0]);
                center.erase(center.begin() + 0);
            }
            // copy tiles of same colour to return variable
            for (unsigned int i = 0; i < center.size(); ++i){
                if (center[i]->getColour() == colour){
                    toReturn.push_back(center[i]);
                }
            }
            // copy tiles of different colour to holder
            for (unsigned int i = 0; i < center.size(); ++i){
                if (center[i]->getColour() != colour){
                    holder.push_back(center[i]);
                }
            }
            // clean up workspace
            center.clear();
            center = holder;
            holder.clear();
            // Trap wrong colour entry
            if (toReturn.empty()){
                throw std::logic_error("No such colours");
            }
        } else if (line == 1){
            // copy tiles of same colour to return variable
            for (unsigned int i = 0; i < fa1.size(); ++i){
                if (fa1[i]->getColour() == colour){
                    toReturn.push_back(fa1[i]);
                }
            }
            // copy tiles of different colour to holder
            for (unsigned int i = 0; i < fa1.size(); ++i){
                if (fa1[i]->getColour() != colour){
                    holder.push_back(fa1[i]);
                }
            }
            // move unselected colours to center
            for (unsigned int i = 0; i < holder.size(); ++i){
                center.push_back(holder[i]);
            }
            // cleanup workspace
            fa1.clear();
            holder.clear();
            // Trap wrong colour entry
            if (toReturn.empty()){
                throw std::logic_error("No such colours");
            }
        } else if (line == 2){
            // copy tiles of same colour to return variable
            for (unsigned int i = 0; i < fa2.size(); ++i){
                if (fa2[i]->getColour() == colour){
                    toReturn.push_back(fa2[i]);
                }
            }
            // copy tiles of different colour to holder
            for (unsigned int i = 0; i < fa2.size(); ++i){
                if (fa2[i]->getColour() != colour){
                    holder.push_back(fa2[i]);
                }
            }
            // move unselected colours to center
            for (unsigned int i = 0; i < holder.size(); ++i){
                center.push_back(holder[i]);
            }
            // cleanup workspace
            fa2.clear();
            holder.clear();
            // Trap wrong colour entry
            if (toReturn.empty()){
                throw std::logic_error("No such colours");
            }
        } else if (line == 3){
            // copy tiles of same colour to return variable
            for (unsigned int i = 0; i < fa3.size(); ++i){
                if (fa3[i]->getColour() == colour){
                    toReturn.push_back(fa3[i]);
                }
            }
            // copy tiles of different colour to holder
            for (unsigned int i = 0; i < fa3.size(); ++i){
                if (fa3[i]->getColour() != colour){
                    holder.push_back(fa3[i]);
                }
            }
            // move unselected colours to center
            for (unsigned int i = 0; i < holder.size(); ++i){
                center.push_back(holder[i]);
            }
            // cleanup workspace
            fa3.clear();
            holder.clear();
            // Trap wrong colour entry
            if (toReturn.empty()){
                throw std::logic_error("No such colours");
            }
        } else if (line == 4){
            // copy tiles of same colour to return variable
            for (unsigned int i = 0; i < fa4.size(); ++i){
                if (fa4[i]->getColour() == colour){
                    toReturn.push_back(fa4[i]);
                }
            }
            // copy tiles of different colour to holder
            for (unsigned int i = 0; i < fa4.size(); ++i){
                if (fa4[i]->getColour() != colour){
                    holder.push_back(fa4[i]);
                }
            }
            // move unselected colours to center
            for (unsigned int i = 0; i < holder.size(); ++i){
                center.push_back(holder[i]);
            }
            // cleanup workspace
            fa4.clear();
            holder.clear();
            // Trap wrong colour entry
            if (toReturn.empty()){
                throw std::logic_error("No such colours");
            }
        } else if (line == 5){
            // copy tiles of same colour to return variable
            for (unsigned int i = 0; i < fa5.size(); ++i){
                if (fa5[i]->getColour() == colour){
                    toReturn.push_back(fa5[i]);
                }
            }
            // copy tiles of different colour to holder
            for (unsigned int i = 0; i < fa5.size(); ++i){
                if (fa5[i]->getColour() != colour){
                    holder.push_back(fa5[i]);
                }
            }
            // move unselected colours to center
            for (unsigned int i = 0; i < holder.size(); ++i){
                center.push_back(holder[i]);
            }
            // cleanup workspace
            fa5.clear();
            holder.clear();
            // Trap wrong colour entry
            if (toReturn.empty()){
                throw std::logic_error("No such colours");
            }
        }
        return toReturn;
    }
}

void Factory::loadFactory(Bag* bag){
    // remember to check if bag is empty
    // as a fallback to runtime error 
    // trapping
    fa1.clear();
    for (int i = 0; i < 4; ++i){
        fa1.push_back(bag->serveTile());
    }
    fa2.clear();
    for (int i = 0; i < 4; ++i){
        fa2.push_back(bag->serveTile());
    }
    fa3.clear();
    for (int i = 0; i < 4; ++i){
        fa3.push_back(bag->serveTile());
    }
    fa4.clear();
    for (int i = 0; i < 4; ++i){
        fa4.push_back(bag->serveTile());
    }
    fa5.clear();
    for (int i = 0; i < 4; ++i){
        fa5.push_back(bag->serveTile());
    }
    center.clear();
    center.push_back(new Tile(F));
}

void Factory::loadFactory(int factoryNo, std::vector<TilePtr> factory) {
    //TODO copy vector
    if(factoryNo == 0) {
        center = factory;
    } else if (factoryNo == 1) {
        fa1 = factory;
    } else if (factoryNo == 2) {
        fa2 = factory;
    } else if (factoryNo == 3) {
        fa3 = factory;
    } else if (factoryNo == 4) {
        fa4 = factory;
    } else if (factoryNo == 5) {
        fa5 = factory;
    }
}

bool Factory::isEmpty(){
    bool toReturn = false;
    if (center.empty()){
        if (fa1.empty()){
            if (fa2.empty()){
                if (fa3.empty()){
                    if (fa4.empty()){
                        if (fa5.empty()){
                            toReturn = true;
                        }
                    }
                }
            }
        }
    }
    return toReturn;
}

std::vector<TilePtr> Factory::getFactory(int line){
    std::vector<TilePtr> toReturn;

    if (line < 0 || line > 6){
        throw std::out_of_range("The index selected is out of bounds");
    } else {
        if (line == 0){
            toReturn = center;
        } else if (line == 1){
            toReturn = fa1;
        } else if (line == 2){
            toReturn = fa2;
        } else if (line == 3){
            toReturn = fa3;
        } else if (line == 4){
            toReturn = fa4;
        } else if (line == 5){
            toReturn = fa5;
        }
    }
    return toReturn;
}

void Factory::listFactory(){

    std::cout << "0: ";
    for (unsigned int i = 0; i < center.size(); ++i){
        std::cout << center[i]->getChar() << " ";
    }
    std::cout << std::endl;
    std::cout << "1: ";
    for (unsigned int i = 0; i < fa1.size(); ++i){
        std::cout << fa1[i]->getChar() << " ";
    }
    std::cout << std::endl;
    std::cout << "2: ";
    for (unsigned int i = 0; i < fa2.size(); ++i){
        std::cout << fa2[i]->getChar() << " ";
    }
    std::cout << std::endl;
    std::cout << "3: ";
    for (unsigned int i = 0; i < fa3.size(); ++i){
        std::cout << fa3[i]->getChar() << " ";
    }
    std::cout << std::endl;
    std::cout << "4: ";
    for (unsigned int i = 0; i < fa4.size(); ++i){
        std::cout << fa4[i]->getChar() << " ";
    }
    std::cout << std::endl;
    std::cout << "5: ";
    for (unsigned int i = 0; i < fa5.size(); ++i){
        std::cout << fa5[i]->getChar() << " ";
    }
    std::cout << std::endl;

}

std::string Factory::getFactoryString(int fac) {
    std::string f;

    // creates array of vectors to easily find the correct factory
    std::vector<TilePtr> factory[6] = {fa1, fa2, fa3, fa4, fa5, center};

    // LOOP REFERENCED FROM: https://www.geeksforgeeks.org/array-of-vectors-in-c-stl/
    // loops through factory in the 'fac' position of the factory array
    for (auto it = factory[fac].begin();
         it != factory[fac].end(); it++) {

        // create a tile object from the iterator
        TilePtr tilePtr = *it;
        // creates a string of length 1 from the returned char
        std::string t(1, tilePtr->getColourChar());
        // appends string with colour char
        f = f.append(t);
    }

    return f;
}

bool Factory::colourExists(int fac, Colour colour) {
    bool found = false;
    std::vector<TilePtr> currentFac = getFactory(fac);

    for (auto it = currentFac.begin();
         it != currentFac.end(); it++) {

        // create a tile object from the iterator
        TilePtr tilePtr = *it;
        // creates a string of length 1 from the returned char
        if(tilePtr->getColour() == colour) {
            found = true;
        }
    }

    return found;
}