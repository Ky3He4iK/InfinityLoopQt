//
// Created by ky3he4ik on 28/07/19.
//

#include "MainWindow.h"

#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) {
    QVBoxLayout windowLayout;

    size_t w = 5, h = 6;
    field = new Field(w, h);
    fieldLayout = new FieldWidget(Q_NULLPTR, field);
    controlsWidget = new ControlsWidget(Q_NULLPTR, w, h);

    windowLayout.addWidget(fieldLayout);
    windowLayout.addWidget(controlsWidget);
    setLayout(&windowLayout);

    connect(controlsWidget, &ControlsWidget::resizeSignal, field, &Field::restartSlot);
}
