//
// Created by ky3he4ik on 30/08/19.
//

#include "Solver.h"

#include <set>

Solver &Solver::getInstance() {
    static Solver instance;
    return instance;
}

std::pair<size_t, size_t> Solver::getNextMove(Field &field) {
    std::pair<size_t, size_t> nextMove = {-1, -1};

    if (isDone.size() != field.getHeight() || isDone[0].size() != field.getWidth()) {
        clearPersistence();
        isDone.resize(field.getHeight(), std::vector<bool>(field.getWidth()));
        for (size_t x = 0; x < isDone.size(); x++)
            for (size_t y = 0; y < isDone[0].size(); y++)
                if (field.getType(x, y) == Field::empty || field.getType(x, y) == Field::quadriple)
                    isDone[x][y] = true;

    }

    for (size_t x = 0; x < isDone.size(); x++)
        for (size_t y = 0; y < isDone[0].size(); y++) {
            if (isDone[x][y])
                continue;
            uint8_t neighbors = getNeighbors(x, y, field), mask = field.getMask(x, y);
//            std::vector<uint8_t> suite;
            std::set<uint8_t> suite;
//            suite.reserve(4);
            for (uint8_t rot = 0; rot < 4; rot++) {
                if (checkNeighbors(mask, neighbors))
                    suite.emplace(mask);
                mask = UINT (UINT (mask & UINT_7) << UINT_1) | UINT (UINT (mask & UINT_8) >> UINT_3);
            }
            if (suite.size() == 1) {
                if (*suite.begin() == mask)
                    isDone[x][y] = true;
                else {
                    nextMove = {x, y};
                    return nextMove;
                }
            }
        }


    return nextMove;
}

void Solver::clearPersistence() {
    isDone.clear();
}

/// 0b__XY__________XY__________XY___________XY
///  (x - 1, y); (x, y - 1); (x + 1, y); (x, y + 1)
/// X - isDone
/// Y - has connection
uint8_t Solver::getNeighbors(size_t x, size_t y, Field &field) {
    uint8_t res = 0;
    if (x == 0)
        res |= UINT 0x80;
    else
        res |= UINT (UINT (UINT (field.getMask(x - 1, y) & UINT_4) << UINT_4) |
                     UINT (UINT isDone[x - 1][y] << UINT_7));

    if (y == 0)
        res |= UINT_2;
    else
        res |= UINT (UINT (UINT (field.getMask(x, y - 1) & UINT_2) >> UINT_1) |
                     UINT (UINT isDone[x][y - 1] << UINT_1));

    if (x + 1 == isDone.size())
        res |= UINT_8;
    else
        res |= UINT (UINT (UINT (field.getMask(x + 1, y) & UINT_1) << UINT_3) |
                     UINT (UINT isDone[x + 1][y] << UINT_3));

    if (y + 1 == isDone[0].size())
        res |= UINT 0x20;
    else
        res |= UINT (UINT (UINT (field.getMask(x, y + 1) & UINT_8) << UINT_1) |
                     UINT (UINT isDone[x][y + 1] << UINT_5));
    return res;
}

bool Solver::checkNeighbors(uint8_t mask, uint8_t neighbors) {
    for (uint8_t dir = 0; dir < 4; dir++) {
        if ((UINT (neighbors >> UINT (dir * UINT_2 + UINT_1)) & UINT_1) &&
            ((UINT (neighbors >> UINT (dir * UINT_2)) & UINT_1) != (UINT (mask >> UINT (UINT_1 << dir)) & UINT_1)))
            return false;
    }
    return true;
}
