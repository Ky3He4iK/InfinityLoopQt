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

    std::random_device random;

    void clear();

    void create(size_t _width, size_t _height);

    void shuffle();

public:
    Field(size_t, size_t);

    void restart(size_t _width, size_t _height);

    void rotate(size_t x, size_t y);

    const bool check();

    const bool check(size_t x, size_t y);

    const uint8_t getMask(size_t x, size_t y);

    const uint8_t getType(size_t x, size_t y);

    const uint8_t getRotation(size_t x, size_t y);

    const size_t getWidth() { return width; }

    const size_t getHeight() { return height; }

signals:

    void dataChangedSignal();

public slots:

    void restartSlot(size_t _width, size_t _height);

    void rotateSlot(size_t x, size_t y);

};


#endif //GAME_FIELD_H
