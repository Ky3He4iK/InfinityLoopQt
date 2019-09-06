//
// Created by ky3he4ik on 30/08/19.
//

#ifndef GAME_SOLVER_H
#define GAME_SOLVER_H

#include "../Field.h"
#include <vector>
#include <queue>

class Solver {
public:
    static Solver &getInstance();

    /**
     * @param solverLevel:
     *      0 - use last setting
     *      1 - do not use
     *      2 - use only generic algorithm
     *      3 - use brute-force algorithm for some cases that not solved by generic algorithm
     *      4 - use brute-force algorithm for some cases + some optimizations
     * */
    std::pair<size_t, size_t> getNextMove(Field &field, uint8_t solverLevel);

    void clearPersistence();

private:
    std::vector <std::vector<bool>> isDone;
    std::queue <std::pair <size_t, size_t> > queue;

    uint8_t getNeighbors(size_t x, size_t y, Field &field);

    static bool checkNeighbors(uint8_t mask, uint8_t neighbors);

    std::vector<std::vector<size_t> > findComponent();

    void checkComponent(size_t x, size_t y, size_t value, std::vector<std::vector<size_t> > &component);


};


#endif //GAME_SOLVER_H
