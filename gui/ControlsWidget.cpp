//
// Created by ky3he4ik on 7/22/19.
//

#include "ControlsWidget.h"
#include "util/IconManager.h"

#include <QApplication>
#include <QDesktopWidget>

ControlsWidget::ControlsWidget(QWidget *, size_t width, size_t height, uint8_t solverLevel) {
    size_t iconSize = IconManager::getIconSize();

    QRect desktopSize = QApplication::desktop()->availableGeometry();
    size_t maxIconSize = std::min(desktopSize.width() / 2, desktopSize.height() / 2);

    QHBoxLayout *allContent;
    allContent = new QHBoxLayout;
    controlWidth = new QVBoxLayout;
    labelWidth = new QLabel;
    labelWidth->setText("Width:");
    spinBoxWidth = new QSpinBox;
    controlWidth->addWidget(labelWidth);
    controlWidth->addWidget(spinBoxWidth);
    allContent->addLayout(controlWidth);

    controlHeight = new QVBoxLayout;
    labelHeight = new QLabel;
    labelHeight->setText("Height:");
    spinBoxHeight = new QSpinBox;
    controlHeight->addWidget(labelHeight);
    controlHeight->addWidget(spinBoxHeight);
    allContent->addLayout(controlHeight);

    controlIconSize = new QVBoxLayout;
    labelIconSize = new QLabel;
    labelIconSize->setText("Icon size:");
    spinBoxIconSize = new QSpinBox;
    spinBoxIconSize->setRange(16, maxIconSize);
    spinBoxIconSize->setValue(iconSize);
    controlIconSize->addWidget(labelIconSize);
    controlIconSize->addWidget(spinBoxIconSize);
    allContent->addLayout(controlIconSize);


    controlSolverLvl = new QVBoxLayout;
    labelSolverLvl = new QLabel;
    labelSolverLvl->setText("SolverLvl:");
    comboSolverLvl = new QComboBox;
    controlSolverLvl->addWidget(labelSolverLvl);
    controlSolverLvl->addWidget(comboSolverLvl);
    allContent->addLayout(controlSolverLvl);

    comboSolverLvl->setInsertPolicy(QComboBox::NoInsert);
    comboSolverLvl->setEditable(false);
    comboSolverLvl->addItems(QStringList() << "1" << "2" << "3" << "4");
    comboSolverLvl->setCurrentIndex(solverLevel + 1);


    updateSpinBoxes(iconSize);
    spinBoxWidth->setValue(width);
    spinBoxHeight->setValue(height);

    applyButton = new QPushButton;
    applyButton->setText("Apply");
    allContent->addWidget(applyButton);

    setLayout(allContent);
    connect(applyButton, &QPushButton::clicked, this, &ControlsWidget::applySlot);
}

void ControlsWidget::applySlot() {
    if (spinBoxIconSize->value() != IconManager::getIconSize()) {
        IconManager::getInstance().setIconSize(spinBoxIconSize->value());
        updateSpinBoxes(spinBoxIconSize->value());
    }
    emit resizeSignal(spinBoxWidth->value(), spinBoxHeight->value(), comboSolverLvl->currentIndex() - 1);
}

void ControlsWidget::updateSpinBoxes(size_t iconSize) {
    QRect desktopSize = QApplication::desktop()->availableGeometry();
    size_t maxWidth = desktopSize.width() / (iconSize + 1), maxHeight =
            desktopSize.height() / (iconSize + 1);
    if (maxHeight < 4)
        maxHeight = 4;
    if (maxWidth < 4)
        maxWidth = 4;
    if (maxWidth < spinBoxWidth->value() || maxHeight < spinBoxHeight->value()) {
        spinBoxWidth->setValue(std::min(maxWidth, (size_t) spinBoxWidth->value()));
        spinBoxHeight->setValue(std::min(maxHeight, (size_t) spinBoxHeight->value()));
        emit resizeSignal(spinBoxWidth->value(), spinBoxHeight->value(), comboSolverLvl->currentIndex() - 1);
    }
    spinBoxWidth->setRange(2, maxWidth);
    spinBoxHeight->setRange(2, maxHeight);
}
