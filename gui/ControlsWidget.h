//
// Created by ky3he4ik on 7/22/19.
//

#ifndef GAME_CONTROLSWIDGET_H
#define GAME_CONTROLSWIDGET_H

#include <QWidget>
#include <QSpinBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

class ControlsWidget : public QWidget {
Q_OBJECT

private:
    QLabel *labelWidth;
    QSpinBox *spinBoxWidth;
    QLabel *labelHeight;
    QSpinBox *spinBoxHeight;
    QLabel *labelIconSize;
    QSpinBox *spinBoxIconSize;
    QPushButton *applyButton;

    QVBoxLayout *controlHeight;
    QVBoxLayout *controlWidth;
    QVBoxLayout *controlIconSize;

    void updateSpinBoxes(size_t iconSize);

public:
    explicit ControlsWidget(QWidget *, size_t width, size_t height);

signals:

    void resizeSignal(size_t width, size_t height);

private slots:

    void applySlot();
};

#endif //GAME_CONTROLSWIDGET_H
