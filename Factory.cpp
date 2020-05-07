#include <string>

#include "Factory.h"

Factory::Factory():
    factory()
{

}

Factory::~Factory(){

}

std::vector<TilePtr> Factory::getTiles(Colour colour, unsigned int count){
    if(isEmpty()){
        throw std::out_of_range("The factory is empty");
    } else {
        // declare return variables
        std::vector<TilePtr> toReturn;
        // loop through factory and add tiles
        // of the selected color to holder
        for(int i = 0; i < size(); ++i){
            if (factory[i]->getColour() == colour){
                toReturn.push_back(factory[i]);
                // cplusplus.com
                factory.erase(factory.begin() + i);
            }
            // if the selcted color is not in the factory
            // or does not match the amount selected
            if (toReturn.empty() || toReturn.size() != count){
                throw std::logic_error("Your selection cannot play");
            }
        }
        return toReturn;
    }
}

int Factory::size(){
    return factory.size();
}

void Factory::addTile(TilePtr tile){
    factory.push_back(tile);
}

void Factory::loadFactory(Bag* bag){
    // remeber to check if bag is empty
    // as a fallback to runtime error 
    // trapping
    for (int i = 0; i < 4; ++i){
        factory.push_back(bag->serveTile());
    }
}

bool Factory::isEmpty(){
    return factory.empty();
}

std::vector<TilePtr> Factory::getFactory(){
    return factory;
}

void Factory::listFactory(){
    int i = 0;
    while (i < size()){
        std::cout << factory[i]->getChar() << " ";
        ++i;
    }
    std::cout << std::endl;
}