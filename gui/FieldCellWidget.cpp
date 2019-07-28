//
// Created by ky3he4ik on 7/20/19.
//

#include "FieldCellWidget.h"

FieldCellWidget::FieldCellWidget(QWidget *parent, FieldCellData *_fieldCellData) : fieldCellData(_fieldCellData) {
    fieldCellData = _fieldCellData;
    setIcon(fieldCellData->icon);
    setIconSize(QSize(50, 50));

    setFlat(true);
    show();
    connect(this, &FieldCellWidget::clicked, this, &FieldCellWidget::clickedSlot);
    connect(this, &FieldCellWidget::rotateSignal, fieldCellData->field, &Field::rotateSlot);
}

FieldCellWidget::FieldCellWidget(QWidget *parent, Field *_field, size_t _x, size_t _y) : fieldCellData(
        new FieldCellData{_field, _x, _y}) {
    setIcon(fieldCellData->icon);
    setIconSize(QSize(50, 50));

    setFlat(true);
    show();
    connect(this, &FieldCellWidget::clicked, this, &FieldCellWidget::clickedSlot);
    connect(this, &FieldCellWidget::rotateSignal, fieldCellData->field, &Field::rotateSlot);
}

void FieldCellWidget::redraw() {
    fieldCellData->setIcon();
    setIcon(fieldCellData->icon);
}

void FieldCellWidget::redrawSlot() {
    redraw();
}

//void FieldCellWidget::onClick() {
//todo
//    emit rotateSignal(x, y);
//}

void FieldCellWidget::clickedSlot() {
    fieldCellData->rotate();
    setIcon(fieldCellData->icon);
    emit rotateSignal(fieldCellData->x, fieldCellData->y);
//    show();
}

//void FieldCellWidget::dataChangedSlot(Field *field) {
//    rotate = field->getrotate(x, y);
//}

void FieldCellWidget::relocate(size_t x, size_t y) {
    fieldCellData->x = x;
    fieldCellData->y = y;
    redraw();
}