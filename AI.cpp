#include "AI.h"

AI::AI(int id):
    Player(id, "AI")
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

AI::AI(int id, Factory* factory):
    Player(id, "AI"),
    factory(factory)
{
    for (int i = 0; i < 5; ++i){
        for (int j = 0; j < 5; ++j){
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

AI::~AI() {
    delete factory;
}

void AI::setFactory(Factory* f) {
    factory = f;
}

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
    std::vector<std::vector<TilePtr>> v = mosaic->getVectors();
    //  Loads a simulated mosaic to help calculate the score
    TilePtr** mos = mosaic->getMosaic();

    //  Variables to store the best turn
    bool incomplete = false;
    int score = 0;
    Turn current = {0, new Tile(E), 0};

    // for each pile
    for(int i = 0; i < 5; i++) {
        int empty = isEmpty(v[i]);
        //  if it is empty
        if(empty == v[i].size()) {
            // get the available colours in the row
            std::vector<Colour> available = availableColours(mos, i);

            //  for each available colour
            for(unsigned int j = 0; j < available.size(); j++) {
                //  for each factory
                for(int k = 0; k < 6; k++) {
                    //  if the factory contains those colours
                    int noAvailable = factory->countColourTiles(k, available[j]);
                    if(noAvailable > 0) {
                        int turnScore = calculateScore(i, available[j], noAvailable, v, k);
                        std::cout << "e:" << empty << ", fac:" << k << ", c:" << available[j] << ", no:" << noAvailable << ", pile:" << i + 1 << ": " << turnScore << std::endl;
                        if(turnScore > score || current.tile->getColour() == E) {
                            score = turnScore;
                            current = {k, new Tile(available[j]), i + 1};
                            std::cout << "chosen";
                            if(noAvailable < empty) {
                                incomplete = true;
                                std::cout << " incomplete";
                            }
                            std::cout << std::endl;
                        } else if (incomplete && score == turnScore && noAvailable == empty) {
                            score = turnScore;
                            current = {k, new Tile(available[j]), i + 1};
                            incomplete = false;
                            std::cout << "chosen complete" << std::endl;
                        }
                    }
                }
            }
        } else if (empty > 0) {
            Colour available = v[i][v[i].size() - 1]->getColour();

            for(int k = 0; k < 6; k++) {
                //  if the factory contains those colours
                int noAvailable = factory->countColourTiles(k, available);
                if(noAvailable > 0) {
                    int turnScore = calculateScore(i, available, noAvailable, v, k);
                    std::cout << "e:" << empty << ", fac:" << k << ", c:" << available << ", no:" << noAvailable << ", pile:" << i + 1 << ": " << turnScore << std::endl;
                    if(turnScore > score || current.tile->getColour() == E) {
                        score = turnScore;
                        current = {k, new Tile(available), i + 1};
                        std::cout << "chosen";
                        if(noAvailable < empty) {
                            incomplete = true;
                            std::cout << " incomplete";
                        }
                        std::cout << std::endl;
                    } else if (incomplete && score == turnScore && noAvailable == empty) {
                        score = turnScore;
                        current = {k, new Tile(available), i + 1};
                        incomplete = false;
                        std::cout << "chosen complete" << std::endl;
                    }
                }
            }
        }
    }

    //  forced broken
    if(current.tile->getColour() == E) {
        for(int i = 0; i < 6; i++) {
            if(factory->countColourTiles(i, R)) {
                current = {i, new Tile(R), 6};
            } else if(factory->countColourTiles(i, Y)) {
                current = {i, new Tile(Y), 6};
            } else if(factory->countColourTiles(i, B)) {
                current = {i, new Tile(B), 6};
            } else if(factory->countColourTiles(i, L)) {
                current = {i, new Tile(L), 6};
            } else if(factory->countColourTiles(i, U)) {
                current = {i, new Tile(U), 6};
            }
        }
    }

    try {
        Player::playTurn(factory, current.fRow, current.tile->getColour(), current.pRow);
    } catch (std::exception& e) {
        std::cerr << "Exception Caught: " << e.what() << std::endl;
        playTurn();
    }

    std::cout << std::endl << "AI: turn " << current.fRow << " " << current.tile->getColourChar() << " " << current.pRow << std::endl;
    std::cout << "Turn successful." << std::endl << std::endl;



}

int AI::isEmpty(std::vector<TilePtr> v) {
    int empty = 0;

    for(unsigned int i = 0; i < v.size(); i++) {
        if(v[i]->getColour() == E) {
            empty++;
        }
    }
    return empty;
}

TilePtr** AI::simulateRound(TilePtr** mos, std::vector<std::vector<TilePtr>> v, int row) {
    //  for each pile
    for(int i = 0; i <= row; i++) {
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

std::vector<Colour> AI::availableColours(TilePtr **mos, int row) {
    //  determine the number of available spaces
    int count = 0;
    for(int i = 0; i < 5; i++) {
        if(mos[row][i]->getColour() == E) {
            count++;
        }
    }

    //  initialise
    std::vector<Colour> available;

    //  find the available colours
    for(int i = 0; i < count; i++) {
        if(mos[row][i]->getColour() == E) {
            available.push_back(puzzle[row][i]->getColour());
        }
    }

    return available;
}

int AI::calculateScore(int row, Colour colour, int num, std::vector<std::vector<TilePtr>> v, int facNo) {
    //  initialising return score
    int turnScore = 0;

    //  scores from piles above that will be placed at the end of the round
    TilePtr** mos = simulateRound(mosaic->getMosaic(), v, row - 1);

    //  gets the selected pile
    std::vector<TilePtr> pile = v[row];

    //  gets the number of tiles in a pile
    int numTiles = num;
    for(unsigned int i = 0; i < pile.size(); i++) {
        if(pile[i]->getColour() != E) {
            numTiles++;
        }
    }

    //  if the number of tiles in a pile is full or greater than the pile size
    if(numTiles >= row + 1) {
        //  score broken tiles
        //  calculate how many are broken
        int brokenTiles = numTiles - (row + 1);
        //  if the factory chosen contains the first tile, add to broken
        if(factory->countColourTiles(facNo, F) == 1) {
            brokenTiles++;
        }

        int preBroken = 0;
        for(unsigned int i = 0; i < v[5].size(); i++) {
            if(v[5][i]->getColour() != E) {
                preBroken++;
            }
        }

        //  for all new broken tiles, score how many points are lost
        for(int i = preBroken - 1; i < brokenTiles; i++) {
            if(i >= 0 && i <= 2) {
                turnScore--;
            } else if (i >= 3 && i <= 4) {
                turnScore -= 2;
            } else if (i >= 5 && i <= 6) {
                turnScore -= 3;
            }
        }

        //  find the column the tile will be placed
        int col = 0;
        for(int i = 0; i < 5; i++) {
            if(colour == puzzle[row][i]->getColour()) {
                col = i;
            }
        }

        //  scoring end of round
        //  score column
        //  if first row
        if(row == 0) {
            if(mos[row + 1][col]->getColour() != E) {
                //  initial point for places tile
                turnScore++;
                //  for each tile connected in the column add a point
                for(int i = row + 1; i < 5; i++) {
                    if(mos[i][col]->getColour() != E) {
                        turnScore++;
                    }
                }
            }
        } else if(row == 4) {
            if(mos[row - 1][col]->getColour() != E) {
                //  if the last row
                //  initial point for places tile
                turnScore++;
                //  for each tile connected in the column add a point
                for(int i = row - 1; i >= 0; i--) {
                    if(mos[i][col]->getColour() != E) {
                        turnScore++;
                    }
                }
            }
        } else if(mos[row + 1][col]->getColour() != E
              || mos[row - 1][col]->getColour() != E) {
            //  if isn't first or last row and has adjacent tiles
            //  initial point for places tile
            turnScore++;
            //  for each tile connected in the column add a point
            for(int i = row + 1; i < 5; i++) {
                if(mos[i][col]->getColour() != E) {
                    turnScore++;
                }
            }
            for(int i = row - 1; i >= 0; i--) {
                if(mos[i][col]->getColour() != E) {
                    turnScore++;
                }
            }
        }

        //  score row
        //  if first column
        if(col == 0) {
            if(mos[row][col + 1]->getColour() != E) {
                //  initial point for places tile
                turnScore++;
                //  for each tile connected in the row add a point
                for(int i = col + 1; i < 5; i++) {
                    if(mos[row][i]->getColour() != E) {
                        turnScore++;
                    }
                }
            }
        } else if(col == 4) {
            if(mos[row][col - 1]->getColour() != E) {
                //  if the last row
                //  initial point for places tile
                turnScore++;
                //  for each tile connected in the row add a point
                for(int i = col - 1; i >= 0; i--) {
                    if(mos[row - 1][i]->getColour() != E) {
                        turnScore++;
                    }
                }
            }
        } else if(mos[row][col + 1]->getColour() != E
                  || mos[row][col - 1]->getColour() != E) {
            //  if isn't first or last column and has adjacent tiles
            //  initial point for places tile
            turnScore++;
            //  for each tile connected in the row add a point
            for(int i = col + 1; i < 5; i++) {
                if(mos[row][i]->getColour() != E) {
                    turnScore++;
                }
            }
            for(int i = col - 1; i >= 0; i--) {
                if(mos[row][i]->getColour() != E) {
                    turnScore++;
                }
            }
        }

        //  if no adjacent (i.e. no points have been awarded), add a single point
        if(turnScore <= 0) {
            turnScore++;
        }

        //  end of game scoring
        //  simulate again, with all turn already completed
        mos = simulateRound(mos, v, 5);

        //  completed row
        int tiles = 0;
        for(int i = 0; i < 5; i++) {
            if(mos[row][i]->getColour() != E || i == col) {
                tiles++;
            }
        }
        if(tiles == 5) {
            turnScore += 2;
        }

        //  completed column
        tiles = 0;
        for(int i = 0; i < 5; i++) {
            if(mos[i][col]->getColour() != E || i == row - 1) {
                tiles++;
            }
        }
        if(tiles == 5) {
            turnScore += 7;
        }

        //  set of colours
        tiles = 0;
        for(int i = 0; i < 5; i++) {
            for(int j = 0; j < 5; j++) {
                if(mos[i][j]->getColour() == colour) {
                    tiles++;
                }
            }
        }
        if(tiles == 4) {
            turnScore += 10;
        }
    }

    return turnScore;
}
