//
// Created by ky3he4ik on 7/20/19.
//

#ifndef GAME_FIELD_H
#define GAME_FIELD_H

#include <vector>
#include <stdint-gcc.h>
#include <ostream>
#include <random>
#include <cstring>

#include <QObject>

#define ROTATE_MASK (uint8_t) 3
#define TYPE_MASK (uint8_t) 0b11100000
#define ROTATE_COUNT 4
#define TYPE_COUNT 6

#define UINT_1 (uint8_t) 1
#define UINT_2 (uint8_t) 2
#define UINT_3 (uint8_t) 3
#define UINT_4 (uint8_t) 4
#define UINT_5 (uint8_t) 5
#define UINT_8 (uint8_t) 8

class Field : public QObject {
Q_OBJECT
private:
    size_t width, height;
    std::vector<std::vector<uint8_t> > field; // type and rotation (0bTTT000RR)
    const std::pair<const char *, const uint8_t> types[TYPE_COUNT][ROTATE_COUNT] = {
            {{" ", 0},  {" ", 0},  {" ", 0},  {" ", 0}},
            {{"╼", 8},  {"╽", 1},  {"╾", 2},  {"╿", 4}},
            {{"┐", 12}, {"┘", 9},  {"└", 3},  {"┌", 6}},
            {{"┤", 13}, {"┴", 11}, {"├", 7},  {"┬", 14}},
            {{"┼", 15}, {"┼", 15}, {"┼", 15}, {"┼", 15}},
            {{"─", 10}, {"│", 5},  {"─", 10}, {"│", 5}}
    };

    const char *icon_names[TYPE_COUNT] = {
            "gui/grafics/svg/empty.svg",
            "gui/grafics/svg/single-blue-l.svg",
            "gui/grafics/svg/corner-blue-ld.svg",
            "gui/grafics/svg/triple-blue-uld.svg",
            "gui/grafics/svg/quadriple-blue-uldr.svg",
            "gui/grafics/svg/line-blue-lr.svg"
    };

    std::random_device random;

    /*
        {{" ", 0},  {" ", 0},  {" ", 0},  {" ", 0}},
        {{"╽", 1},  {"╾", 2},  {"╿", 4},  {"╼", 8}},
        {{"└", 3},  {"┌", 6},  {"┐", 12}, {"┘", 9}},
        {{"┴", 11}, {"├", 7},  {"┬", 14}, {"┤", 13}},
        {{"┼", 15}, {"┼", 15}, {"┼", 15}, {"┼", 15}},
        {{"─", 10}, {"│", 5},  {"─", 10}, {"│", 5}}

        {{0x257d, 1}, {0x257e, 2}, {0x257f, 4}, {0x257c, 8}},
        {{0x2514, 3}, {0x250c, 6}, {0x2510, 12}, {0x2518, 9}},
        {{0x2534, 11}, {0x251c, 7}, {0x252c, 14}, {0x2524, 13}},
        {{0x253c, 15}, {0x253c, 15}, {0x253c, 15}, {0x253c, 15}},
        {{0x2500, 10}, {0x2502, 5}, {0x2500, 10}, {0x2502, 5}},
        {{0x20, 0}, {0x20, 0}, {0x20, 0}, {0x20, 0}}
    */

    void clear();

    void create(size_t _width, size_t _height);

    const void print(std::ostream &);

    void shuffle();

public:
    Field(size_t, size_t);

    void restart(size_t _width, size_t _height);

    void rotate(size_t x, size_t y);

    const bool check();

    const bool check(size_t x, size_t y);

    const inline uint8_t getmask(size_t x, size_t y);

    const inline uint8_t gettype(size_t x, size_t y);

    const uint8_t getrotate(size_t x, size_t y);

    const char *getIconPath(uint8_t type) { return icon_names[type]; }

    const size_t getWidth() { return width; }

    const size_t getHeigth() { return height; }

signals:

    void dataChangedSignal();

public slots:

    void restartSlot(size_t _width, size_t _height);

    void rotateSlot(size_t x, size_t y);

};


#endif //GAME_FIELD_H
