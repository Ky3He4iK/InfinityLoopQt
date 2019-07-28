#include <iostream>

#include "Field.h"
#include "gui/ControlsWidget.h"
#include "gui/FieldCellWidget.h"
#include "gui/FieldLayout.h"
#include <QApplication>
#include <QMainWindow>
#include <QScrollArea>

#include <QVBoxLayout>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QPlainTextEdit>


int main(int argc, char *argv[]) {
//    Field field(4, 4);
//    field.restart(10, 5);
    QApplication app(argc, argv);
//    FieldCellWidget fieldCellWidget(mainWindow.parentWidget(), new FieldCellData());

//    QWidget mainWindow;
//    FieldLayout fieldLayout(Q_NULLPTR, &field);
//    mainWindow.setLayout(&fieldLayout);
//    mainWindow.showFullScreen();
//    mainWindow.setBackgroundRole(QPalette::ColorRole::Base);
//    mainWindow.show();

    ControlsWidget controlsWidget;
    controlsWidget.show();

    return app.exec();
}
