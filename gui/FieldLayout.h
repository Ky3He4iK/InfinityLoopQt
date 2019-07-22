//
// Created by ky3he4ik on 7/20/19.
//

#ifndef GAME_FIELDLAYOUT_H
#define GAME_FIELDLAYOUT_H

#include <QWidget>
#include <QGridLayout>
#include <vector>
#include "FieldCellWidget.h"

class FieldLayout : public QGridLayout {
Q_OBJECT

public:
    explicit FieldLayout(QWidget *parent = Q_NULLPTR, Field *_field = nullptr);

private:
    Field *field;
    std::vector<FieldCellWidget *> fieldCells;

    void clear();

    void start();

    void rearrange();

public slots:

//    void restartSlot(Field *_field);
    void dataChangedSlot();

signals:

    void redrawSignal();
};


#endif //GAME_FIELDLAYOUT_H
