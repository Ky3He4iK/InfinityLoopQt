//
// Created by ky3he4ik on 7/20/19.
//

#include "FieldWidget.h"
#include <algorithm>

FieldWidget::FieldWidget(QWidget *, Field *_field) : field(_field) {
//    setHorizontalSpacing(0);
//    setVerticalSpacing(0);

    // set black background
    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(0, 0, 0));
    setAutoFillBackground(true);
    setPalette(pal);

    if (field == nullptr)
        return;
    holder = new QVBoxLayout;
    setLayout(holder);
    start();

    connect(field, &Field::dataChangedSignal, this, &FieldWidget::dataChangedSlot);
}

void FieldWidget::clear() {
    for (size_t x = 0; x < cellsGrid.size(); x++)
        clearRow(x);

    cellsGrid.clear();
    rows.clear();
}

void FieldWidget::clearRow(size_t x) {
    for (size_t y = 0; y < cellsGrid[x].size(); y++) {
        clearCell(x, y);
    }
    cellsGrid[x].clear();
    holder->removeItem(holder->itemAt(x));
    delete rows[x];
}

void FieldWidget::clearCell(size_t x, size_t y) {
    cellsGrid[x][y]->hide();
    disconnect(this, &FieldWidget::redrawSignal, cellsGrid[x][y],
               &FieldCellWidget::redrawSlot);
    rows[x]->removeItem(rows[x]->itemAt(y));
    delete cellsGrid[x][y];
}

void FieldWidget::start() {
    holder->setSpacing(0);
    cellsGrid.resize(field->getHeigth());
    rows.resize(field->getHeigth());
    for (size_t x = 0; x < field->getHeigth(); x++)
        addRow(x);
}

void FieldWidget::addRow(size_t x) {
    rows[x] = new QHBoxLayout;
    rows[x]->setSpacing(0);
    cellsGrid[x].resize(field->getWidth());
    holder->addLayout(rows[x]);
    for (size_t y = 0; y < field->getWidth(); y++)
        addCell(x, y);
}

void FieldWidget::addCell(size_t x, size_t y) {
    cellsGrid[x][y] = new FieldCellWidget{Q_NULLPTR, field, x, y};
    connect(this, &FieldWidget::redrawSignal, cellsGrid[x][y],
            &FieldCellWidget::redrawSlot);
    rows[x]->addWidget(cellsGrid[x][y]);
}

void FieldWidget::dataChangedSlot() {
    if (cellsGrid[0].size() != field->getWidth() || cellsGrid.size() != field->getHeigth()) {
//        clear();
//        start();
        rearrange();
        resize(cellsGrid[0][0]->size().width() * field->getWidth(), cellsGrid[0][0]->size().height() * field->getHeigth());
        adjustSize();
    }

    emit redrawSignal();
}

void FieldWidget::rearrange() {
    size_t old_w = cellsGrid[0].size(), old_h = cellsGrid.size(), new_w = field->getWidth(), new_h = field->getHeigth();
    for (size_t x = 0; x < std::min(old_h, new_h); x++) {
        if (old_w >= new_w) {
            for (size_t y = new_w; y < old_w; y++)
                clearCell(x, y);
            cellsGrid[x].resize(new_w);
        } else {
            cellsGrid[x].resize(new_w);
            for (size_t y = old_w; y < new_w; y++)
                addCell(x, y);
        }
    }
    if (old_h >= new_h) {
        for (size_t x = new_h; x < old_h; x++)
            clearRow(x);

        cellsGrid.resize(new_h);
        rows.resize(new_h);
    } else {
        cellsGrid.resize(new_h);
        rows.resize(new_h);
        for (size_t x = old_h; x < new_h; x++)
            addRow(x);
    }
}
