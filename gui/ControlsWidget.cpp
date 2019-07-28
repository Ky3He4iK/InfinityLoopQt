//
// Created by ky3he4ik on 7/22/19.
//

#include "ControlsWidget.h"


#include <QGridLayout>


ControlsWidget::ControlsWidget(QWidget *parent, size_t _width, size_t _height) : width(_width), height(_height) {
    //todo

    QHBoxLayout *allContent;


    allContent = new QHBoxLayout;

    controlWidth = new QVBoxLayout;
    textWidth = new QPlainTextEdit;
    textWidth->setReadOnly(true);
    textWidth->setPlainText("Width:");
    spinBoxWidth = new QSpinBox;
    spinBoxWidth->setRange(3, 20);
    spinBoxWidth->setValue(width);
    controlWidth->addWidget(textWidth);
    controlWidth->addWidget(spinBoxWidth);
    allContent->addLayout(controlWidth);

    controlHeight = new QVBoxLayout;
    textHeight = new QPlainTextEdit;
    textHeight->setReadOnly(true);
    textHeight->setPlainText("Height:");
    spinBoxHeight = new QSpinBox;
    spinBoxHeight->setRange(3, 20);
    spinBoxHeight->setValue(height);
    controlHeight->addWidget(textHeight);
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
