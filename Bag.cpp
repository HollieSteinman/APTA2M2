#include <string>

#include "Bag.h"

Bag::Bag(int randGen){
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

TilePtr Bag::serveTile(){
    Node* current = bag->head;
    TilePtr toReturn = nullptr;

    if (current->next == nullptr){
        std::cout << "Bag is empty" << std::endl;
    } else {
        toReturn = current->value;
        delete bag->head;
        bag->head = current->next;
    }
    return toReturn;
} 