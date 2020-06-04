#ifndef AI_H
#define AI_H

#include "Player.h"

class AI : public Player{
public:

    AI(int id, Factory *factory);
    virtual ~AI();

    void playTurn();

    bool isEmpty(std::vector<TilePtr> v);

    TilePtr** simulateRound(TilePtr** mos, std::vector<TilePtr>* v, int row);

    Colour* availableColours(TilePtr** mos, int row);

    int calculateScore(int row, Colour colour, int num, std::vector<TilePtr>* v);

private:

    typedef struct Turn {
        int fRow;
        Colour colour;
        int pRow;
    };

    Factory* factory;
    TilePtr** puzzle;
};

#endif //AI_H
