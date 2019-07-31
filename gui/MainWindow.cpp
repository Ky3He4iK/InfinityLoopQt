//
// Created by ky3he4ik on 28/07/19.
//

#include "MainWindow.h"

#include <QVBoxLayout>
#include <QGridLayout>

#include <iostream>

MainWindow::MainWindow(QWidget *) {
//    QVBoxLayout windowLayout;
//    QGridLayout gridLayout;

    size_t w = 5, h = 6;
    field = new Field(w, h);

    resize(640, 480);
//    setLayout(&gridLayout);
    fieldWidget = new FieldWidget(Q_NULLPTR, field);
    fieldWidget->adjustSize();
    fieldWidget->show();
//    gridLayout.addWidget(fieldWidget, 1, 1);
    controlsWidget = new ControlsWidget(Q_NULLPTR, w, h);
    controlsWidget->adjustSize();
    controlsWidget->show();

//    gridLayout.addWidget(controlsWidget, 0, 0);
    QSize fieldSize = fieldWidget->size();
    QSize controlsSize = controlsWidget->size();


    std::cout << fieldSize.width() << 'x' << fieldSize.height() << "; " << controlsSize.width() << 'x'
              << controlsSize.height() << '\n';
    std::cout << fieldWidget->maximumHeight() << 'x' << fieldWidget->maximumWidth() << '\n';


//    setLayout(&windowLayout);
//    windowLayout.addWidget(fieldWidget);
//    windowLayout.addWidget(controlsWidget);
//    resize(h * 100, w * 100);

    connect(controlsWidget, &ControlsWidget::resizeSignal, field, &Field::restartSlot);
}
