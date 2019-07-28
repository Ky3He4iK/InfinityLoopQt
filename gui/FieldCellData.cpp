//
// Created by ky3he4ik on 7/21/19.
//

#include "FieldCellData.h"

FieldCellData::FieldCellData(Field *_field, size_t _x, size_t _y) : field(_field), x(_x), y(_y) {
    setIcon();
}

void FieldCellData::setIcon() {

    QPixmap pixmap(field->getIconPath(field->gettype(x, y)));
    icon.addPixmap(pixmap, QIcon::Mode::Active, QIcon::State::On);
    icon.addPixmap(pixmap, QIcon::Mode::Active, QIcon::State::Off);
    icon.addPixmap(pixmap, QIcon::Mode::Normal, QIcon::State::Off);
    uint8_t r = field->getrotate(x, y);
    for (uint8_t i = 0; i < r; i++)
        rotate();
}

void FieldCellData::rotate() {
    QPixmap pixmap(icon.pixmap(icon.availableSizes().last()));
    QMatrix rm;
    rm.rotate(90);
    pixmap = pixmap.transformed(rm);

    icon.addPixmap(pixmap, QIcon::Mode::Active, QIcon::State::On);
    icon.addPixmap(pixmap, QIcon::Mode::Active, QIcon::State::Off);
    icon.addPixmap(pixmap, QIcon::Mode::Normal, QIcon::State::Off);
    //todo
}
