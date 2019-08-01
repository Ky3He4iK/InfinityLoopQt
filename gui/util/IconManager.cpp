//
// Created by ky3he4ik on 31/07/19.
//

#include "IconManager.h"

IconManager::IconManager() {
    data.resize(TYPE_COUNT);
    for (size_t i = 0; i < TYPE_COUNT; i++) {
        data[i].resize(ROTATE_COUNT);
        QPixmap pixmap(iconNames[i]);
        for (size_t j = 0; j < ROTATE_COUNT; j++) {
            data[i][j] = QIcon(pixmap);
            QMatrix rm;
            rm.rotate(90);
            pixmap = pixmap.transformed(rm);
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
