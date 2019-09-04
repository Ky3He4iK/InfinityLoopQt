//
// Created by ky3he4ik on 28/07/19.
//

#ifndef GAME_MAINWINDOW_H
#define GAME_MAINWINDOW_H

#include <QMainWindow>

#include "FieldWidget.h"
#include "ControlsWidget.h"
#include "../Field.h"

class MainWindow : public QWidget {
Q_OBJECT

private:
    FieldWidget *fieldWidget;
    ControlsWidget *controlsWidget;
    Field *field;

public:
    explicit MainWindow(size_t width, size_t height, size_t iconSize, bool solve);
};


#endif //GAME_MAINWINDOW_H
