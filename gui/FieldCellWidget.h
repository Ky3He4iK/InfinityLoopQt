//
// Created by ky3he4ik on 7/20/19.
//

#ifndef GAME_FIELDCELLWIDGET_H
#define GAME_FIELDCELLWIDGET_H

#include <QPushButton>
#include "../Field.h"
#include "FieldCellData.h"

class FieldCellWidget : public QPushButton {
Q_OBJECT

public:
    explicit FieldCellWidget(QWidget *parent = Q_NULLPTR, FieldCellData *_fieldCellData = nullptr);

    explicit FieldCellWidget(QWidget *parent, Field *_field, size_t _x, size_t _y);

    void relocate(size_t x, size_t y);

    size_t getX() { return fieldCellData->x; }

    size_t getY() { return fieldCellData->y; }

private:
    FieldCellData *fieldCellData;

    void redraw();


public slots:

    void clickedSlot();

    void redrawSlot();
//    void dataChangedSlot(Field *);

signals:

    void rotateSignal(size_t, size_t);

};


#endif //GAME_FIELDCELLWIDGET_H
