#include "AI.h"

AI::AI(int id, Factory *factory):
    Player(id, "AI"),
    factory(factory)
{
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

AI::~AI() {}

/*
 *  -Look for move that results in most points
 *      -Doesn't account for filling up of piles?
 *  -Look for move that follows strategies/most points
 *
 *  -Start with pile 1 & 2
 *  -Start from centre
 *  -Keep broken minimal
 *  -Top is placed before bottom
 *  -Row of 5 = end of game
 *
 *  -Opponent sabotage?
 *
 *  -End of round points:
 *      -Minus broken
 *      -count linked tiles vertically
 *      -count linked tiles horizontally
 *  -End of game bonuses:
 *      -2 points for horizontal line
 *      -7 points for vertical line
 *      -10 points for all 5 of single colour
 *      -Tie = more horizontal lines
 */

/* ALGORITHM playTurn()
 * BEGIN
 * FIND current mosaic and piles
 * DETERMINE moves for each pile
 * FOR each move
 *    FIND gained points
 * PLAY best move
 */

void AI::playTurn() {
    //  Reloads mosaic and vectors at each turn
    std::vector<TilePtr>* v = mosaic->getVectors();
    //  Loads a simulated mosaic to help calculate the score
    TilePtr** mos = mosaic->getMosaic();

    //  Variables to store the best turn
    int score = mosaic->getPoints();
    Turn current = {0, E, 0};

    // for each pile
    for(int i = 0; i < 5; i++) {
        if(isEmpty(v[i])) {
            // get the available colours in the row
            Colour* available = availableColours(mos, i);

            //  for each availible colour
            for(int j = 0; j < sizeof(available); j++) {
                //  for each factory
                for(int k = 0; k < 6; k++) {
                    //  if the factory contains those colours
                    int noAvailible = factory->countColourTiles(k, available[j]);
                    if(noAvailible > 0) {
                        int turnScore = calculateScore(i, available[j], noAvailible, v);

                    }
                }
            }
        }
    }

}

bool AI::isEmpty(std::vector<TilePtr> v) {
    bool empty = true;

    // LOOP REFERENCED FROM: https://www.geeksforgeeks.org/array-of-vectors-in-c-stl/
    for (auto it = v.begin();
         it != v.end() && empty; it++) {

        // create a tile object from the iterator
        TilePtr tilePtr = *it;

        if(tilePtr->getColour() != E) {
            empty = false;
        }
    }

    return empty;
}

TilePtr** AI::simulateRound(TilePtr **mos, std::vector<TilePtr>* v, int row) {
    //  for each pile
    for(int i = 0; i < row; i++) {
        //  if the pile is full
        if(v[i].size() == i + 1) {
            //  for each column in the corresponding puzzle row
            for(int j = 0; j < 5; j++) {
                //  if the tile equals the tiles in the pile
                if(puzzle[i][j]->getColour() == v[i][0]->getColour()) {
                    //  set as placed in the AI mosaic
                    mos[i][j] = v[i][0];
                }
            }
        }
    }
    return mos;
}

Colour* AI::availableColours(TilePtr **mos, int row) {
    //  determine the number of available spaces
    int count = 0;
    for(int i = 0; i < 5; i++) {
        if(mos[row][i]->getColour() == E) {
            count++;
        }
    }

    //  initialise
    Colour* available = new Colour[count];

    //  find the availible colours
    for(int i = 0; i < count; i++) {
        if(mos[row][i]->getColour() == E) {
            available[i] = puzzle[row][i]->getColour();
        }
    }

    return available;
}

int AI::calculateScore(int row, Colour colour, int num, std::vector<TilePtr>* v) {
    //  initialising return score
    int turnScore = 0;

    //  scores from piles above that will be placed at the end of the round
    TilePtr** mos = simulateRound(mosaic->getMosaic(), v, row - 1);

    //  gets the selected pile
    std::vector<TilePtr> pile = v[row - 1];

    //  for each tile in the pile
    for(int i = 0; i < pile.size(); i++) {

    }

}
