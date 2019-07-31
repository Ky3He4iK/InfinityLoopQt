//
// Created by ky3he4ik on 7/20/19.
//

#include "FieldCellWidget.h"

FieldCellWidget::FieldCellWidget(QWidget *parent, Field *_field, size_t _x, size_t _y)
        : iconManager(IconManager::getInstance()), field(_field), x(_x), y(_y) {

    draw();
    setFlat(true);
    show();
    connect(this, &FieldCellWidget::clicked, this, &FieldCellWidget::clickedSlot);
    connect(this, &FieldCellWidget::rotateSignal, field, &Field::rotateSlot);
}


void FieldCellWidget::draw() {
    setIcon(iconManager.getIcon(field->gettype(x, y), field->getrotate(x, y)));
    setIconSize(QSize(50, 50));
}

void FieldCellWidget::redrawSlot() {
    draw();
}

void FieldCellWidget::clickedSlot() {
    draw();
    emit rotateSignal(x, y);
}

void FieldCellWidget::relocate(size_t _x, size_t _y) {
    x = _x;
    y = _y;
    draw();
}
