//
// Created by ky3he4ik on 28/07/19.
//

#include "MainWindow.h"

#include <QVBoxLayout>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) {
    QVBoxLayout windowLayout;

    size_t w = 5, h = 6;
    field = new Field(w, h);
    fieldLayout = new FieldLayout(Q_NULLPTR, field);
    controlsWidget = new ControlsWidget(Q_NULLPTR, w, h);

    std::cout << "adding fieldLayout\n";
    windowLayout.addLayout(fieldLayout);
    std::cout << "adding controlsWidget\n";
    windowLayout.addWidget(controlsWidget);
    std::cout << "applying\n";
    setLayout(&windowLayout);
}
