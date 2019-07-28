//
// Created by ky3he4ik on 7/20/19.
//

#include "FieldWidget.h"
#include "util/GridLayoutUtil.h"

FieldWidget::FieldWidget(QWidget *parent, Field *_field) : field(_field) {
//    setHorizontalSpacing(0);
//    setVerticalSpacing(0);
    if (field == nullptr)
        return;
    layout = new QGridLayout;
    start();
    setLayout(layout);

    connect(field, &Field::dataChangedSignal, this, &FieldWidget::dataChangedSlot);
}

void FieldWidget::clear() {
    for (size_t x = 0; x < layout->rowCount(); x++) {

        for (size_t y = 0; y < layout->columnCount(); y++) {
            delete fieldCells[x * layout->columnCount() + y];
        }
    }
    fieldCells.clear();
    GridLayoutUtil::removeAll(layout);
}

void FieldWidget::start() {
    layout->setHorizontalSpacing(0);
    layout->setVerticalSpacing(0);
    fieldCells.reserve(field->getHeigth() * field->getWidth());
    for (size_t x = 0; x < field->getHeigth(); x++) {
        for (size_t y = 0; y < field->getWidth(); y++) {
            fieldCells.push_back(new FieldCellWidget{Q_NULLPTR, field, x, y});
            connect(this, &FieldWidget::redrawSignal, fieldCells[x * layout->columnCount() + y],
                    &FieldCellWidget::redrawSlot);
            layout->addWidget(fieldCells[x * layout->columnCount() + y], x, y);
        }
    }
}

void FieldWidget::dataChangedSlot() {
    if (layout->columnCount() != field->getWidth() || layout->rowCount() != field->getHeigth()) {
        clear();
        start();
//        rearrange();
    }
    emit redrawSignal();
}

void FieldWidget::rearrange() {
    size_t old_size = fieldCells.size(), new_size = field->getWidth() * field->getHeigth(),
            old_w = layout->columnCount(), old_h = layout->rowCount(), new_w = field->getWidth(), new_h = field->getHeigth();
    if (old_size >= new_size) {
        for (size_t x = 0; x < new_h; x++) {
            for (size_t y = 0; y < new_w; y++) {
                GridLayoutUtil::removeCell(layout, fieldCells[x * layout->columnCount() + y]->getX(),
                                           fieldCells[x * layout->columnCount() + y]->getY());
                fieldCells[x * layout->columnCount() + y]->relocate(x, y);
                layout->addWidget(fieldCells[x * layout->columnCount() + y], x, y);
            }
        }
        for (size_t i = new_size; i < old_size; i++)
            delete fieldCells[i];

    } else {
        for (size_t x = 0; x < old_size / new_w; x++) {
            for (size_t y = 0; y < new_w; y++) {
                layout->addWidget(fieldCells[x * new_w + y], x, y);
                GridLayoutUtil::removeCell(layout, fieldCells[x * new_w + y]->getX(),
                                           fieldCells[x * new_w + y]->getY());
                if (fieldCells[x * new_w + y]) {
                    fieldCells[x * new_w + y]->relocate(x, y);
                }
            }
        }
        for (size_t y = 0; y < old_size % new_w; y++) {
            GridLayoutUtil::removeCell(layout, fieldCells[(old_size / new_w) * new_w + y]->getX(),
                                       fieldCells[(old_size / new_w) * new_w + y]->getY());
            layout->addWidget(fieldCells[old_size / new_w * new_w + y], old_size / new_w, y);
            fieldCells[(old_size / new_w) * new_w + y]->relocate(old_size / new_w, y);
        }
        for (size_t y = old_size % new_w; y < new_w; y++) {
            fieldCells.push_back(new FieldCellWidget{Q_NULLPTR, field, old_size / new_w, y});
            connect(this, &FieldWidget::redrawSignal, fieldCells[old_size / new_w * new_w + y],
                    &FieldCellWidget::redrawSlot);
            layout->addWidget(fieldCells[old_size / new_w * new_w + y], old_size / new_w, y);
        }
        for (size_t x = old_size / new_w + ((old_size % new_w) ? 1 : 0); x < new_h; x++) {
            for (size_t y = 0; y < new_w; y++) {
                fieldCells.push_back(new FieldCellWidget{Q_NULLPTR, field, x, y});
                connect(this, &FieldWidget::redrawSignal, fieldCells[x * new_w + y], &FieldCellWidget::redrawSlot);
                layout->addWidget(fieldCells[x * new_w + y], x, y);
            }

        }
        //todo
    }
//    todo
}
