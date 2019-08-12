//
// Created by ky3he4ik on 7/20/19.
//

#ifndef GAME_FIELDCELLWIDGET_H
#define GAME_FIELDCELLWIDGET_H

#include <QPushButton>
#include "../Field.h"
#include "util/IconManager.h"

class FieldCellWidget : public QPushButton {
Q_OBJECT

public:
    explicit FieldCellWidget(QWidget *, Field *_field, size_t _x, size_t _y);

private:
    IconManager &iconManager;
    Field *field;
    size_t x, y;

public slots:

    void clickedSlot();

    void redrawSlot();

    void resizeSlot(size_t iconSize);

signals:

    void rotateSignal(size_t, size_t);

};

#endif //GAME_FIELDCELLWIDGET_H
