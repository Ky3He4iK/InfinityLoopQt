//
// Created by ky3he4ik on 31/07/19.
//

#ifndef GAME_ICONMANAGER_H
#define GAME_ICONMANAGER_H

#include <QIcon>
#include "../../Field.h"
#include <QVector>

class IconManager {
private:
    const QVector<QString> iconNames = {
            "gui/grafics/svg/empty.svg",
            "gui/grafics/svg/single-white-l.svg",
            "gui/grafics/svg/corner-white-ld.svg",
            "gui/grafics/svg/triple-white-uld.svg",
            "gui/grafics/svg/quadriple-white-uldr.svg",
            "gui/grafics/svg/line-white-lr.svg"
    };

    QVector<QVector<QIcon> > data;

    IconManager();

public:
    static IconManager &getInstance();

    QIcon getIcon(size_t type, size_t rotation);

    IconManager(IconManager const &) = delete;

    void operator=(IconManager const &) = delete;
};


#endif //GAME_ICONMANAGER_H
