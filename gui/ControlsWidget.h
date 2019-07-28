//
// Created by ky3he4ik on 7/22/19.
//

#ifndef GAME_CONTROLSWIDGET_H
#define GAME_CONTROLSWIDGET_H

#include <QWidget>
#include <QSpinBox>
#include <QPlainTextEdit>
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
    explicit ControlsWidget(QWidget *parent = Q_NULLPTR, size_t _width = 4, size_t _height = 4);

signals:
    void resizeSignal(size_t width, size_t height);

private slots:

    void changeWidthSlot(size_t _width);

    void changeHeightSlot(int _height);

    void applySlot();

};


#endif //GAME_CONTROLSWIDGET_H
