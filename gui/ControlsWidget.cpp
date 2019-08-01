//
// Created by ky3he4ik on 7/22/19.
//

#include "ControlsWidget.h"
#include "util/IconManager.h"

#include <QApplication>
#include <QDesktopWidget>

ControlsWidget::ControlsWidget(QWidget *parent, size_t _width, size_t _height) : width(_width), height(_height) {
    QSize desktopSize = QApplication::desktop()->size();

    size_t maxWidth = desktopSize.width() / (ICON_SIZE + 1) - 1, maxHeight = desktopSize.height() / (ICON_SIZE + 1) - 1;  //todo: parse from command line
    if (maxHeight < 4)
        maxHeight = 4;
    if (maxWidth < 4)
        maxWidth = 4;

    QHBoxLayout *allContent;
    allContent = new QHBoxLayout;
    controlWidth = new QVBoxLayout;
    labelWidth = new QLabel;
    labelWidth->setText("Width:");
    spinBoxWidth = new QSpinBox;
    spinBoxWidth->setRange(2, maxWidth); //todo: calculate max field size
    spinBoxWidth->setValue(width);
    controlWidth->addWidget(labelWidth);
    controlWidth->addWidget(spinBoxWidth);
    allContent->addLayout(controlWidth);

    controlHeight = new QVBoxLayout;
    labelHeight = new QLabel;
    labelHeight->setText("Height:");
    spinBoxHeight = new QSpinBox;
    spinBoxHeight->setRange(2, maxHeight);
    spinBoxHeight->setValue(height);
    controlHeight->addWidget(labelHeight);
    controlHeight->addWidget(spinBoxHeight);
    allContent->addLayout(controlHeight);

    applyButton = new QPushButton;
    applyButton->setText("Apply");
    allContent->addWidget(applyButton);

    setLayout(allContent);

    connect(spinBoxWidth, QOverload<int>::of(&QSpinBox::valueChanged), this, &ControlsWidget::changeWidthSlot);
    connect(spinBoxHeight, QOverload<int>::of(&QSpinBox::valueChanged), this, &ControlsWidget::changeHeightSlot);
    connect(applyButton, &QPushButton::clicked, this, &ControlsWidget::applySlot);
}

void ControlsWidget::applySlot() {
    emit resizeSignal(width, height);
}

void ControlsWidget::changeWidthSlot(size_t _width) {
    width = _width;
}

void ControlsWidget::changeHeightSlot(int _height) {
    height = _height;
}
