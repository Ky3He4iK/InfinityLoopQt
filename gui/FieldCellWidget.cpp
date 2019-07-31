//
// Created by ky3he4ik on 7/20/19.
//

#include <QtCore/QTime>
#include <QtCore/QEventLoop>
#include <QApplication>
#include "FieldCellWidget.h"

FieldCellWidget::FieldCellWidget(QWidget *parent, Field *_field, size_t _x, size_t _y)
        : iconManager(IconManager::getInstance()), field(_field), x(_x), y(_y) {

    draw();
    setIconSize(QSize(50, 50));
    setFlat(true);
    show();
    connect(this, &FieldCellWidget::clicked, this, &FieldCellWidget::clickedSlot);
    connect(this, &FieldCellWidget::rotateSignal, field, &Field::rotateSlot);
}


void FieldCellWidget::draw() {
    setIcon(iconManager.getIcon(field->gettype(x, y), field->getrotate(x, y)));
}

void FieldCellWidget::redrawSlot() {
    draw();
}

void FieldCellWidget::clickedSlot() {
    emit rotateSignal(x, y);
    draw();
}

void FieldCellWidget::relocate(size_t _x, size_t _y) {
    x = _x;
    y = _y;
    draw();
}
