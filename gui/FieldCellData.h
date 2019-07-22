//
// Created by ky3he4ik on 7/21/19.
//

#ifndef GAME_FIELDCELLDATA_H
#define GAME_FIELDCELLDATA_H


#include <stdint-gcc.h>
#include <glob.h>

#include <QImage>
#include <QIcon>

#include "../Field.h"

class FieldCellData : public QObject {
Q_OBJECT
public:
    explicit FieldCellData(Field *_field, size_t _x, size_t _y);

    void rotate();

    void setIcon();

//private:
    size_t x, y;

    QIcon icon;
    Field *field;
//    QSize size;


};


#endif //GAME_FIELDCELLDATA_H
