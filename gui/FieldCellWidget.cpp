//
// Created by ky3he4ik on 7/20/19.
//

#include <QtCore/QTime>
#include <QtCore/QEventLoop>
#include <QApplication>
#include "FieldCellWidget.h"

FieldCellWidget::FieldCellWidget(QWidget *, Field *_field, size_t _x, size_t _y)
        : iconManager(IconManager::getInstance()), field(_field), x(_x), y(_y) {

    redrawSlot();
    setIconSize(QSize(ICON_SIZE, ICON_SIZE));
    setFixedSize(ICON_SIZE + 1, ICON_SIZE + 1);
    setFlat(true);
    connect(this, &FieldCellWidget::clicked, this, &FieldCellWidget::clickedSlot);
    connect(this, &FieldCellWidget::rotateSignal, field, &Field::rotateSlot);
}

void FieldCellWidget::redrawSlot() {
    setIcon(iconManager.getIcon(field->getType(x, y), field->getRotation(x, y)));
}

void FieldCellWidget::clickedSlot() {
    emit rotateSignal(x, y);
    redrawSlot();
}
