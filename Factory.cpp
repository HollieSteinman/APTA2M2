#include <string>

#include "Factory.h"

Factory::Factory():
    factory()
{

}

Factory::~Factory(){

}

// TilePtr Factory::getTiles(Colour colour, int count){
//     if(!isEmpty()){
//         TilePtr toReturn[count]; 
//         for(int i = 0; 1 < size(); ++i){

//         }
//     }
// }

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