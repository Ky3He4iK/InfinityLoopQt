//
// Created by ky3he4ik on 7/20/19.
//

#ifndef GAME_FIELDWIDGET_H
#define GAME_FIELDWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QVector>
#include "FieldCellWidget.h"

class FieldWidget : public QWidget {
Q_OBJECT

public:
    explicit FieldWidget(QWidget *parent = Q_NULLPTR, Field *_field = nullptr);

private:
    Field *field;

    QVector<QVector<FieldCellWidget*> > cellsGrid;
    QVector<QHBoxLayout*> rows;
    QVBoxLayout *holder;

    void clear();

    void clearRow(size_t x);

    void clearCell(size_t x, size_t y);

    void addRow(size_t x);

    void addCell(size_t x, size_t y);

    void start();

    void rearrange();

public slots:

//    void restartSlot(Field *_field);
    void dataChangedSlot();

signals:

    void redrawSignal();
};


#endif //GAME_FIELDWIDGET_H
