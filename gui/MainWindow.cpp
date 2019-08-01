//
// Created by ky3he4ik on 28/07/19.
//

#include "MainWindow.h"

#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *) {
//    QVBoxLayout windowLayout;

    size_t w = 5, h = 6;  //todo: parse from command line
    field = new Field(w, h);

    fieldWidget = new FieldWidget(Q_NULLPTR, field);
    fieldWidget->adjustSize();
    fieldWidget->setWindowTitle("Field | InfinityLoopQt");
    fieldWidget->show();
    controlsWidget = new ControlsWidget(Q_NULLPTR, w, h);
    controlsWidget->adjustSize();
    controlsWidget->setWindowTitle("Controls | InfinityLoopQt");
    controlsWidget->show();

    connect(controlsWidget, &ControlsWidget::resizeSignal, field, &Field::restartSlot);
}
