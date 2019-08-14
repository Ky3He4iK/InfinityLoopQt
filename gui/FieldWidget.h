//
// Created by ky3he4ik on 7/20/19.
//

#ifndef GAME_FIELDWIDGET_H
#define GAME_FIELDWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QVector>
#include "FieldCellWidget.h"

class FieldWidget : public QWidget {
Q_OBJECT

public:
    explicit FieldWidget(QWidget *, Field *_field);

private:
    Field *field;

    QVector<QVector<FieldCellWidget *> > cellsGrid;
    QVector<QHBoxLayout *> rows;
    QVBoxLayout *holder;

    void clearRow(size_t x);

    void clearCell(size_t x, size_t y);

    void addRow(size_t x);

    void addCell(size_t x, size_t y);

    void start();

    void rearrange();

public slots:

    void dataChangedSlot();

    void resizeSlot(size_t newSize = 0);

signals:

    void redrawSignal();
};

#endif //GAME_FIELDWIDGET_H
