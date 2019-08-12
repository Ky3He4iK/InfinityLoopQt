//
// Created by ky3he4ik on 31/07/19.
//

#ifndef GAME_ICONMANAGER_H
#define GAME_ICONMANAGER_H

#include <QIcon>
#include "../../Field.h"
#include <QVector>
#include <QObject>

class IconManager : public QObject {
Q_OBJECT

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

    static size_t iconSize;

public:
    static IconManager &getInstance();

    QIcon getIcon(size_t type, size_t rotation);

    IconManager(IconManager const &) = delete;

    void operator=(IconManager const &) = delete;

    static size_t getIconSize();

    void setIconSize(size_t);

signals:
    void iconResizeSignal(size_t newIconSize);
};

//size_t IconManager::iconSize = 50;

#endif //GAME_ICONMANAGER_H
