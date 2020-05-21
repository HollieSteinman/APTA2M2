#include <string>

#include "Bag.h"

Bag::Bag(int randGen):
    seed(randGen)
{

    // initiate bag as a linked list
    bag = new LinkedList();
    bag->head = nullptr;

    // initiate random engine
    int min = 0;
    int max = 99;
    std::default_random_engine engine(randGen);
    std::uniform_int_distribution<int> uniform_dist(min, max);

    // Make an array of tiles
    TilePtr tempBag[100];
    
    // Put 20 of each tile type into the array
    for (int i = 0; i < 20; ++i){
        tempBag[i] = new Tile(R);
    }
    for (int i = 20; i < 40; ++i){
        tempBag[i] = new Tile(Y);
    }
    for (int i = 40; i < 60; ++i){
        tempBag[i] = new Tile(B);
    }
    for (int i = 60; i < 80; ++i){
        tempBag[i] = new Tile(L);
    }
    for (int i = 80; i < 100; ++i){
        tempBag[i] = new Tile(U);
    }

    // shuffle the array bag into the linked list bag
    int value = 0;
    int i = 0;
    while (i < 100) {
        value = uniform_dist(engine);
        if(tempBag[value] != nullptr){
            addTile(tempBag[value]);
            tempBag[value] = nullptr;
            for (int i = value; i < 100; ++i){
                tempBag[i] = tempBag[i+1];
                tempBag[i+1] = nullptr;
            }
        } else {
            // this ensures that a tile is transferred each round
            --i;
        }
        ++i;
    }



}

Bag::Bag(std::vector<TilePtr> tempBag, int randGen):
    seed(randGen)
{
    bag = new LinkedList();
    for (unsigned int i = 0; i < tempBag.size(); ++i){
        addTile(tempBag[i]);
    }
}

Bag::~Bag(){

}

int Bag::size() {
    Node* current = bag->head;
    int counter = 0;
    while (current != nullptr) {
        ++counter;
        current = current->next;
    }
    return counter;
}

void Bag::addTile(TilePtr tile){
    // create node
    Node* toAdd = new Node();
    toAdd->value = tile;
    toAdd->next = nullptr;
    // if linkedlist is empty
    if (bag->head == nullptr) {
        // point it to valueparam
        bag->head = toAdd;
    } else {
        // loop until end of linked list
        Node* current = bag->head;
        while (current->next != nullptr) {
            current = current->next;
        }
        // add to end of linked list
        current->next = toAdd;
    }
}

void Bag::removeTile(int index) {
    // create node
    Node* previous = bag->head;
    int counter = 0;
    if (bag->head == nullptr){
        std::cout << "The bag is empty" << std::endl;
    } else {
        while (counter < index - 1){
            ++counter;
            previous = previous->next;
        }
        Node* holder = previous->next->next;
        delete previous->next;
        // previous->next = nullptr;
        previous->next = holder;
    }
}

void Bag::clear() {
    for (int i = 0; i < 100; ++i){
        removeTile(i);// remove function handles error checking
    }
}

TilePtr Bag::serveTile(){
    Node* current = bag->head;
    TilePtr toReturn = nullptr;

    if (current == nullptr){
        //throw std::out_of_range("Cannot serve from an empty list");
        std::cout << "Bag is empty" << std::endl;
    } else {
        toReturn = current->value;
        delete bag->head;
        bag->head = current->next;
    }
    return toReturn;
} 

void Bag::reload(){
    for (unsigned int i = 0; i < boxLid.size(); ++i){
        addTile(boxLid[i]);
    }
    clearBox();
}

void Bag::putBox(std::vector<TilePtr> tiles){
    for (unsigned int i = 0; i < tiles.size(); ++i){
        boxLid.push_back(tiles[i]);
    }
}

void Bag::clearBox(){
    boxLid.clear();
}

int Bag::getSeed() {
    return seed;
}

std::string Bag::getBag() {
    std::string b;

    // find the head node and the node to be referenced from inside the loop
    Node* current = bag->head;
    // whilst the node isn't null
    while(current != nullptr) {
        // creates a string of length 1 from the returned char
        std::string t(1, current->value->getColourChar());
        // appends string with colour char
        b = b.append(t);
        // sets the current node for the next loop
        current = current->next;
    }

    return b;
}

std::string Bag::getLid() {
    std::string l;

    // LOOP REFERENCED FROM: https://www.geeksforgeeks.org/array-of-vectors-in-c-stl/
    for (auto it = boxLid.begin();
         it != boxLid.end(); it++) {

        // create a tile object from the iterator
        TilePtr tilePtr = *it;
        // creates a string of length 1 from the returned char
        std::string t(1, tilePtr->getColourChar());
        // appends string with colour char
        l = l.append(t);
    }

    return l;
}