//
// Created by ky3he4ik on 28/07/19.
//

#include "MainWindow.h"

#include <QVBoxLayout>

MainWindow::MainWindow(size_t width, size_t height) {
    field = new Field(width, height);

    fieldWidget = new FieldWidget(Q_NULLPTR, field);
    fieldWidget->adjustSize();
    fieldWidget->setWindowTitle("Field | InfinityLoopQt");
    fieldWidget->show();
    controlsWidget = new ControlsWidget(Q_NULLPTR, width, height);
    controlsWidget->adjustSize();
    controlsWidget->setWindowTitle("Controls | InfinityLoopQt");
    controlsWidget->show();

    connect(controlsWidget, &ControlsWidget::resizeSignal, field, &Field::restartSlot);
}
