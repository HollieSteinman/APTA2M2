#ifndef AI_H
#define AI_H

#include "Player.h"

class AI : public Player{
public:

    /**
     * Constructor used for loading from savefile
     * @param id - AI id
     */
    AI(int id);

    /**
     * Default constructor
     * @param id - AI id
     * @param factory - Game factory (used to calculate moves)
     */
    AI(int id, Factory *factory);

    /**
     * Default destructor
     */
    virtual ~AI();

    /**
     * Sets the AI's factory
     * @param f - Used for loading
     */
    void setFactory(Factory* f);

    /**
     * Main method for the AI to play a turn
     */
    void playTurn();

    /**
     * Checks how many empty spots are in a pile
     * @param - Pile being checked
     * @return - Int of empty spots
     */
    int isEmpty(std::vector<TilePtr> v);

    /**
     * Simulates a round sequentially until a row,
     * used for calculating points for rows below
     * @param mos - Mosaic
     * @param v - Vector of piles
     * @param row - Row to be simulated until
     * @return - Modified mosaic
     */
    TilePtr** simulateRound(TilePtr** mos, std::vector<std::vector<TilePtr>> v, int row);

    /**
     * Returns the available colours in a
     * row of the mosaic
     * @param mos - Mosaic
     * @param row  - Row being checked
     * @return - Vector of available colours
     */
    std::vector<Colour> availableColours(TilePtr** mos, int row);

    /**
     * Calculates the score for a proposed turn
     * @param row - Pile row chosen
     * @param colour - Colour chosen
     * @param num - Number of tiles chosen from factory
     * @param v - Vector of piles
     * @param facNo - Number of the factory being chosen from
     * @return - Int of the estimated score
     */
    int calculateScore(int row, Colour colour, int num, std::vector<std::vector<TilePtr>> v, int facNo);

private:

    typedef struct Turn {
        int fRow;
        TilePtr tile;
        int pRow;
    } Turn;

    Factory* factory;
    TilePtr puzzle[5][5];
};

#endif //AI_H
