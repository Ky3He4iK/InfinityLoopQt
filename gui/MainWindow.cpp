//
// Created by ky3he4ik on 28/07/19.
//

#include "MainWindow.h"

#include "util/IconManager.h"

#include <QVBoxLayout>

MainWindow::MainWindow(size_t width, size_t height, size_t iconSize, uint8_t solverLevel) {
    IconManager::getInstance().setIconSize(iconSize);

    field = new Field(width, height, solverLevel);


    controlsWidget = new ControlsWidget(Q_NULLPTR, width, height, solverLevel);
    controlsWidget->adjustSize();
    controlsWidget->setWindowTitle("Controls | InfinityLoopQt");
    controlsWidget->show();

    recreateFieldWidgetSlot();

    connect(controlsWidget, &ControlsWidget::resizeSignal, field, &Field::restartSlot);
}

void MainWindow::recreateFieldWidgetSlot() {
    delete fieldWidget;
    fieldWidget = new FieldWidget(Q_NULLPTR, field);
    fieldWidget->adjustSize();
    fieldWidget->setWindowTitle("Field | InfinityLoopQt");
    fieldWidget->show();
    connect(fieldWidget, &FieldWidget::deleteMeSignal, this, &MainWindow::recreateFieldWidgetSlot);
}
