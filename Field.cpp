//
// Created by ky3he4ik on 7/20/19.
//

#include "Field.h"

#include <unistd.h>
#include <iostream>

Field::Field(const size_t _width, const size_t _height) : width(_width), height(_height) {
    srand(time(nullptr) * getpid());
    create(_width, _height);
}

void Field::restart(const size_t _width, const size_t _height) {
    clear();
    std::cout << "\nRestarting...\n";
    create(_width, _height);
}

void Field::rotate(const size_t x, const size_t y) {
    uint8_t newrot = ((field[x][y] & ROTATE_MASK) + UINT_1) % UINT_4;
    uint8_t type = gettype(x, y);
    if (newrot != 0 && types[type][newrot].second == types[type][0].second)
        newrot = 0;
    field[x][y] = (uint8_t) (field[x][y] & TYPE_MASK) | newrot;
    if (check(x, y) && check())
        restart(width, height);

    emit dataChangedSignal();
}

const bool Field::check() {
    for (size_t x = 0; x < height; x++)
        for (size_t y = 0; y < width; y++)
            if (!check(x, y)) {
                std::cout << "Err at " << x << ' ' << y << '\n';
                std::cout << check(x, y) << '\n';
                return false;
            }

    return true;
}

const bool Field::check(const size_t x, const size_t y) {
    uint8_t mask = getmask(x, y);
    if (x == 0) {
        if (mask & UINT_1)
            return false;
    } else if (((uint8_t) (getmask(x - 1, y) & UINT_4) >> UINT_2) != (mask & UINT_1))
        return false;

    if (y == 0) {
        if (mask & UINT_8)
            return false;
    } else if (((uint8_t) (getmask(x, y - 1) & UINT_2) >> UINT_1) != ((uint8_t) (mask & UINT_8) >> UINT_3))
        return false;

    if (x + 1 == height) {
        if (mask & UINT_4)
            return false;
    } else if ((getmask(x + 1, y) & UINT_1) != ((uint8_t) (mask & UINT_4) >> UINT_2))
        return false;

    if (y + 1 == width) {
        if (mask & UINT_2)
            return false;
    } else if (((uint8_t) (getmask(x, y + 1) & UINT_8) >> UINT_3) != ((uint8_t) (mask & UINT_2) >> UINT_1))
        return false;

    return true;
}

inline const uint8_t Field::getmask(const size_t x, const size_t y) {
    return types[gettype(x, y)][(field[x][y] & (uint8_t) 3)].second;
}

inline const uint8_t Field::gettype(const size_t x, const size_t y) {
    return (uint8_t) (field[x][y] & TYPE_MASK) >> UINT_5;
}


const uint8_t Field::getrotate(const size_t x, const size_t y) {
    return field[x][y] & ROTATE_MASK;
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

    std::cout << "in progress\n";
    print(std::cout);

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

    print(std::cout);
    std::cout << check() << '\n';

    shuffle();
    print(std::cout);
}

const void Field::print(std::ostream &out) {
    out << '\n';
    for (auto &row: field) {
        for (auto &cell: row) {
            out << types[(uint8_t) (cell & TYPE_MASK) >> UINT_5][cell & ROTATE_MASK].first;
        }
        out << '\n';
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
    print(std::cout);
}