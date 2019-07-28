//
// Created by ky3he4ik on 7/20/19.
//

#ifndef GAME_FIELDWIDGET_H
#define GAME_FIELDWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <vector>
#include "FieldCellWidget.h"

class FieldWidget : public QWidget {
Q_OBJECT

public:
    explicit FieldWidget(QWidget *parent = Q_NULLPTR, Field *_field = nullptr);

private:
    Field *field;
    std::vector<FieldCellWidget *> fieldCells;
    QGridLayout *layout;

    void clear();

    void start();

    void rearrange();

public slots:

//    void restartSlot(Field *_field);
    void dataChangedSlot();

signals:

    void redrawSignal();
};


#endif //GAME_FIELDWIDGET_H
