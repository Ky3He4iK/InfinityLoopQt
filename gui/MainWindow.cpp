//
// Created by ky3he4ik on 28/07/19.
//

#include "MainWindow.h"

#include <QVBoxLayout>
#include <iostream>

MainWindow::MainWindow(QWidget *) {
//    QVBoxLayout windowLayout;

    size_t w = 5, h = 6;  //todo: parse from command line
    field = new Field(w, h);

//    resize(640, 480);
    fieldWidget = new FieldWidget(Q_NULLPTR, field);
    fieldWidget->adjustSize();
    fieldWidget->setWindowTitle("Field | InfinityLoopQt");
    fieldWidget->show();
    controlsWidget = new ControlsWidget(Q_NULLPTR, w, h);
    controlsWidget->adjustSize();
    controlsWidget->setWindowTitle("Controls | InfinityLoopQt");
    controlsWidget->show();

    QSize fieldSize = fieldWidget->size();
    QSize controlsSize = controlsWidget->size();
    std::cout << fieldSize.width() << 'x' << fieldSize.height() << "; " << controlsSize.width() << 'x'
              << controlsSize.height() << '\n';
//    setLayout(&windowLayout);
//    windowLayout.addWidget(fieldWidget);
//    windowLayout.addWidget(controlsWidget);
//    resize(h * 100, w * 100);

    connect(controlsWidget, &ControlsWidget::resizeSignal, field, &Field::restartSlot);
}
