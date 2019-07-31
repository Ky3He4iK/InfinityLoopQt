//
// Created by ky3he4ik on 7/20/19.
//

#ifndef GAME_FIELDCELLWIDGET_H
#define GAME_FIELDCELLWIDGET_H

#include <QPushButton>
#include "../Field.h"
#include "FieldCellData.h"
#include "util/IconManager.h"

class FieldCellWidget : public QPushButton {
Q_OBJECT

public:
    explicit FieldCellWidget(QWidget *parent, Field *_field, size_t _x, size_t _y);

    void relocate(size_t x, size_t y);

    size_t getX() { return x; }

    size_t getY() { return y; }

private:
    IconManager &iconManager;
    Field *field;
    size_t x, y;

    void draw();



public slots:

    void clickedSlot();

    void redrawSlot();
//    void dataChangedSlot(Field *);

signals:

    void rotateSignal(size_t, size_t);

};


#endif //GAME_FIELDCELLWIDGET_H
