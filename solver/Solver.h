//
// Created by ky3he4ik on 30/08/19.
//

#ifndef GAME_SOLVER_H
#define GAME_SOLVER_H

#include "../Field.h"
#include <vector>

class Solver {
public:
    static Solver &getInstance();

    std::pair<size_t, size_t> getNextMove(Field &field);

    void clearPersistence();

private:
    std::vector <std::vector<bool>> isDone;

    uint8_t getNeighbors(size_t x, size_t y, Field &field);

    bool checkNeighbors(uint8_t mask, uint8_t neighbors);
};


#endif //GAME_SOLVER_H
