#ifndef AI_H
#define AI_H

#include "Player.h"

class AI : public Player{
public:

    AI(int id);
    AI(int id, Factory *factory);
    virtual ~AI();

    void setFactory(Factory* f);

    void playTurn();

    int isEmpty(std::vector<TilePtr> v);

    TilePtr** simulateRound(TilePtr** mos, std::vector<std::vector<TilePtr>> v, int row);

    std::vector<Colour> availableColours(TilePtr** mos, int row);

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
