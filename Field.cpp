//
// Created by ky3he4ik on 7/20/19.
//

#include "Field.h"

#include "solver/Solver.h"

#include <iostream>

Field::Field(const size_t _width, const size_t _height, bool _runSolver) : width(_width), height(_height), runSolver(_runSolver) {
    create(_width, _height);
}

void Field::restart(const size_t _width, const size_t _height) {
    clear();
    Solver::getInstance().clearPersistence();
    create(_width, _height);
}

void Field::rotate(const size_t x, const size_t y) {
    uint8_t newRotation = ((field[x][y] & ROTATE_MASK) + UINT_1) % UINT_4;
    uint8_t type = getType(x, y);
    if (newRotation != 0 && types[type][newRotation].second == types[type][0].second)
        newRotation = 0;
    field[x][y] = (uint8_t) (field[x][y] & TYPE_MASK) | newRotation;
    if (check(x, y) && check())
        restart(width, height);

    emit dataChangedSignal();
}

const bool Field::check() {
    for (size_t x = 0; x < height; x++)
        for (size_t y = 0; y < width; y++)
            if (!check(x, y))
                return false;
    return true;
}

const bool Field::check(const size_t x, const size_t y) {
    uint8_t mask = getMask(x, y);
    if (x == 0) {
        if (mask & UINT_1)
            return false;
    } else if (((uint8_t) (getMask(x - 1, y) & UINT_4) >> UINT_2) != (mask & UINT_1))
        return false;

    if (y == 0) {
        if (mask & UINT_8)
            return false;
    } else if (((uint8_t) (getMask(x, y - 1) & UINT_2) >> UINT_1) != ((uint8_t) (mask & UINT_8) >> UINT_3))
        return false;

    if (x + 1 == height) {
        if (mask & UINT_4)
            return false;
    } else if ((getMask(x + 1, y) & UINT_1) != ((uint8_t) (mask & UINT_4) >> UINT_2))
        return false;

    if (y + 1 == width) {
        if (mask & UINT_2)
            return false;
    } else if (((uint8_t) (getMask(x, y + 1) & UINT_8) >> UINT_3) != ((uint8_t) (mask & UINT_2) >> UINT_1))
        return false;

    return true;
}

inline const uint8_t Field::getMask(size_t x, size_t y) {
    return types[getType(x, y)][(field[x][y] & (uint8_t) 3)].second;
}

inline const uint8_t Field::getType(size_t x, size_t y) {
    if (x < height && y < width)
        return (uint8_t) (field[x][y] & TYPE_MASK) >> UINT_5;
    return 0;
}


const uint8_t Field::getRotation(size_t x, size_t y) {
    if (x < height && y < width)
        return field[x][y] & ROTATE_MASK;
    return 0;
}

void Field::clear() {
    for (auto &row: field)
        row.clear();
    field.clear();
}

void Field::create(const size_t _width, const size_t _height) {
    width = _width;
    height = _height;

    field.resize(height, std::vector<uint8_t>(width, 0));
    bool odd_row = true;
    for (size_t x = 0; x < height; x++) {
        for (size_t y = (odd_row ? 1 : 0); y < width; y += 2) {
            uint8_t type, rot;
            bool ok;
            do {
                type = random() % TYPE_COUNT;
                rot = random() % ROTATE_COUNT;
                ok = true;
                uint8_t mask = types[type][rot].second;
                if (x == 0 && mask & UINT_1)
                    ok = false;
                if (y == 0 && mask & UINT_8)
                    ok = false;
                if (x + 1 == height && mask & UINT_4)
                    ok = false;
                if (y + 1 == width && mask & UINT_2)
                    ok = false;
            } while (!ok);
            field[x][y] = (uint8_t) (type << UINT_5) | rot;
        }
        odd_row = !odd_row;
    }
    odd_row = true;
    for (size_t x = 0; x < height; x++) {
        for (size_t y = (odd_row ? 0 : 1); y < width; y += 2) {
            //todo: optimize
            bool ok = false;
            for (uint8_t t = 0; t < TYPE_COUNT; t++) {
                for (uint8_t r = 0; r < ROTATE_COUNT; r++) {
                    field[x][y] = (uint8_t) (t << UINT_5) | r;
                    if (check(x, y)) {
                        ok = true;
                        break;
                    }
                }
                if (ok)
                    break;
            }

        }
        odd_row = !odd_row;
    }

    shuffle();
    if (runSolver) {
        print();
        Solver solver = Solver::getInstance();
        auto move = solver.getNextMove(*this);
        while (move.first != (size_t) -1) {
            rotate(move.first, move.second);
            std::cout << move.first << ';' << move.second << '\n';
            print();
            move = solver.getNextMove(*this);
        }
    }
}

void Field::shuffle() {
    for (size_t x = 0; x < height; x++)
        for (size_t y = 0; y < width; y++)
            field[x][y] = (uint8_t) (field[x][y] & TYPE_MASK) | (random() & (uint8_t) 3);
    emit dataChangedSignal();
}

void Field::restartSlot(size_t _width, size_t _height) {
    restart(_width, _height);
}

void Field::rotateSlot(const size_t x, const size_t y) {
    rotate(x, y);
}

void Field::print() const {
    std::cout << '\n';
    for (auto &row: field) {
        for (auto &cell: row) {
            std::cout << types[(uint8_t) (cell & TYPE_MASK) >> UINT_5][cell & ROTATE_MASK].first;
        }
        std::cout << '\n';
    }
}
