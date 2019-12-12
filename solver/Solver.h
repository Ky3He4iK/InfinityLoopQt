//
// Created by ky3he4ik on 30/08/19.
//

#ifndef GAME_SOLVER_H
#define GAME_SOLVER_H

#include "../Field.h"
#include <vector>
#include <queue>

typedef std::pair<size_t, size_t> Pos;

template<typename T>
using Vec2d = std::vector<std::vector<T> >;

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
    Pos getNextMove(Field &field, uint8_t solverLevel);

    void clearPersistence();

private:
    Vec2d<bool> isDone;
    std::queue<Pos> queue;

    uint8_t getNeighbors(size_t x, size_t y, Field &field) const;

    static bool checkNeighbors(uint8_t mask, uint8_t neighbors);

    Vec2d<size_t> findComponent() const;

    void checkComponent(size_t x, size_t y, size_t value, Vec2d<size_t> &component) const;

    Vec2d<Pos> getWrong() const;

    Pos findBottleNeck(std::vector<Pos> &graph) const;

    static int brute(Field &field,
              const std::vector<Pos> &graph,
              const Vec2d<size_t> &component,
              std::queue<Pos> &actions, size_t posInd, size_t componentId);
};


#endif //GAME_SOLVER_H
