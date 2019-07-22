//
// Created by ky3he4ik on 7/20/19.
//

#include "FieldLayout.h"
#include "util/GridLayoutUtil.h"

FieldLayout::FieldLayout(QWidget *parent, Field *_field) : field(_field) {
//    setHorizontalSpacing(0);
//    setVerticalSpacing(0);
    if (field == nullptr)
        return;
    start();

    connect(field, &Field::dataChangedSignal, this, &FieldLayout::dataChangedSlot);
}

void FieldLayout::clear() {
    for (size_t x = 0; x < rowCount(); x++) {

        for (size_t y = 0; y < columnCount(); y++) {
            delete fieldCells[x * columnCount() + y];
        }
    }
    fieldCells.clear();
    GridLayoutUtil::removeAll(this);
}

void FieldLayout::start() {
    setHorizontalSpacing(0);
    setVerticalSpacing(0);
    fieldCells.reserve(field->getHeigth() * field->getWidth());
    for (size_t x = 0; x < field->getHeigth(); x++) {
        for (size_t y = 0; y < field->getWidth(); y++) {
            fieldCells.push_back(new FieldCellWidget(Q_NULLPTR, new FieldCellData(field, x, y)));
            connect(this, &FieldLayout::redrawSignal, fieldCells[x * columnCount() + y], &FieldCellWidget::redrawSlot);
            addWidget(fieldCells[x * columnCount() + y], x, y);
        }
    }
}

void FieldLayout::dataChangedSlot() {
    if (columnCount() != field->getWidth() || rowCount() != field->getHeigth()) {
        clear();
        start();
//        rearrange();
    }
    emit redrawSignal();
}

void FieldLayout::rearrange() {
    size_t old_size = fieldCells.size(), new_size = field->getWidth() * field->getHeigth(),
            old_w = columnCount(), old_h = rowCount(), new_w = field->getWidth(), new_h = field->getHeigth();
    if (old_size >= new_size) {
        for (size_t x = 0; x < new_h; x++) {
            for (size_t y = 0; y < new_w; y++) {
                GridLayoutUtil::removeCell(this, fieldCells[x * columnCount() + y]->getX(),
                                           fieldCells[x * columnCount() + y]->getY());
                fieldCells[x * columnCount() + y]->relocate(x, y);
                addWidget(fieldCells[x * columnCount() + y], x, y);
            }
        }
        for (size_t i = new_size; i < old_size; i++)
            delete fieldCells[i];

    } else {
        for (size_t x = 0; x < old_size / new_w; x++) {
            for (size_t y = 0; y < new_w; y++) {
                addWidget(fieldCells[x * new_w + y], x, y);
                GridLayoutUtil::removeCell(this, fieldCells[x * new_w + y]->getX(),
                                           fieldCells[x * new_w + y]->getY());
                if (fieldCells[x * new_w + y]) {
                    fieldCells[x * new_w + y]->relocate(x, y);
                }
            }
        }
        for (size_t y = 0; y < old_size % new_w; y++) {
            GridLayoutUtil::removeCell(this, fieldCells[(old_size / new_w) * new_w + y]->getX(),
                                       fieldCells[(old_size / new_w) * new_w + y]->getY());
            addWidget(fieldCells[old_size / new_w * new_w + y], old_size / new_w, y);
            fieldCells[(old_size / new_w) * new_w + y]->relocate(old_size / new_w, y);
        }
        for (size_t y = old_size % new_w; y < new_w; y++) {
            fieldCells.push_back(new FieldCellWidget(Q_NULLPTR, new FieldCellData(field, old_size / new_w, y)));
            connect(this, &FieldLayout::redrawSignal, fieldCells[old_size / new_w * new_w + y],
                    &FieldCellWidget::redrawSlot);
            addWidget(fieldCells[old_size / new_w * new_w + y], old_size / new_w, y);
        }
        for (size_t x = old_size / new_w + ((old_size % new_w) ? 1 : 0); x < new_h; x++) {
            for (size_t y = 0; y < new_w; y++) {
                fieldCells.push_back(new FieldCellWidget(Q_NULLPTR, new FieldCellData(field, x, y)));
                connect(this, &FieldLayout::redrawSignal, fieldCells[x * new_w + y], &FieldCellWidget::redrawSlot);
                addWidget(fieldCells[x * new_w + y], x, y);
            }

        }
        //todo
    }
//    todo
}
