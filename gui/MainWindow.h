//
// Created by ky3he4ik on 28/07/19.
//

#ifndef GAME_MAINWINDOW_H
#define GAME_MAINWINDOW_H

#include <QMainWindow>

#include "FieldLayout.h"
#include "ControlsWidget.h"
#include "../Field.h"

class MainWindow : public QWidget {
Q_OBJECT

private:
    FieldLayout *fieldLayout;
    ControlsWidget *controlsWidget;
    Field *field;

public:
    explicit MainWindow(QWidget *parent = Q_NULLPTR);

};


#endif //GAME_MAINWINDOW_H
