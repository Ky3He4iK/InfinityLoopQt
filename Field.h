//
// Created by ky3he4ik on 7/20/19.
//

#ifndef GAME_FIELD_H
#define GAME_FIELD_H

#include <vector>
#include <random>

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
#define UINT_6 (uint8_t) 6
#define UINT_7 (uint8_t) 7
#define UINT_8 (uint8_t) 8

#define UINT (uint8_t)

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

    uint8_t solverLevel;

    std::random_device random;

    void clear();

    void create(size_t _width, size_t _height);

    void shuffle();

    void print() const;

public:
    Field(size_t, size_t, uint8_t _solverLevel);

    void restart(size_t _width, size_t _height, uint8_t _solverLevel);

    void rotate(size_t x, size_t y, bool restartOnFin = true);

    const bool check();

    const bool check(size_t x, size_t y);

    const uint8_t getMask(size_t x, size_t y);

    const uint8_t getType(size_t x, size_t y);

    const uint8_t getRotation(size_t x, size_t y);

    const size_t getWidth() { return width; }

    const size_t getHeight() { return height; }

    enum Type {
        empty = 0,
        single = 1,
        corner = 2,
        triple = 3,
        quadriple = 4,
        line = 5,
    };

signals:

    void dataChangedSignal();

public slots:

    /**
     * @param solverLevel:
     *      0 - use last setting
     *      1 - do not use
     *      2 - use only generic algorithm
     *      3 - use brute-force algorithm for some cases that not solved by generic algorithm
     *      4 - use brute-force algorithm for some cases + some optimizations
     * */
    void restartSlot(size_t _width, size_t _height, uint8_t _solverLevel = 0);

    void rotateSlot(size_t x, size_t y);

};


#endif //GAME_FIELD_H
