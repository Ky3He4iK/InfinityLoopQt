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
    size_t width, height;
    QLabel *labelWidth;
    QSpinBox *spinBoxWidth;
    QLabel *labelHeight;
    QSpinBox *spinBoxHeight;
    QPushButton *applyButton;

    QVBoxLayout *controlHeight;
    QVBoxLayout *controlWidth;

public:
    explicit ControlsWidget(QWidget *, size_t _width, size_t _height);

signals:

    void resizeSignal(size_t width, size_t height);

private slots:

    void changeWidthSlot(size_t _width);

    void changeHeightSlot(size_t _height);

    void applySlot();
};

#endif //GAME_CONTROLSWIDGET_H
