//
// Created by ky3he4ik on 31/07/19.
//

#include "IconManager.h"

IconManager::IconManager() {
    data.resize(TYPE_COUNT);
    for (size_t i = 0; i < TYPE_COUNT; i++) {
        data[i].resize(ROTATE_COUNT);
        QIcon base(iconNames[i]);
        QPixmap pixmap(base.pixmap(base.availableSizes().last()));
        QMatrix rm;
        for (size_t j = 0; j < ROTATE_COUNT; j++) {
            data[i][j].addPixmap(pixmap, QIcon::Mode::Active, QIcon::State::On);
            data[i][j].addPixmap(pixmap, QIcon::Mode::Active, QIcon::State::Off);
            data[i][j].addPixmap(pixmap, QIcon::Mode::Normal, QIcon::State::Off);
            pixmap = pixmap.transformed(rm);
            rm.rotate(90);
        }
    }
}

IconManager &IconManager::getInstance() {
    static IconManager instance;
    return instance;
}

QIcon IconManager::getIcon(size_t type, size_t rotation) {
    return data[type][rotation];
}