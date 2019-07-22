#include <iostream>

#include "Field.h"
#include "gui/FieldCellWidget.h"
#include "gui/FieldLayout.h"
#include <QApplication>
#include <QMainWindow>
#include <QScrollArea>

int main(int argc, char *argv[]) {
    Field field(4, 4);
//    field.restart(10, 5);
    QApplication app(argc, argv);
    QWidget mainWindow;


//    FieldCellWidget fieldCellWidget(mainWindow.parentWidget(), new FieldCellData());
//    QScrollArea scrollArea;

//    mainWindow.setLayout(&scrollArea);

    FieldLayout fieldLayout(Q_NULLPTR, &field);
    mainWindow.setLayout(&fieldLayout);
//    mainWindow.showFullScreen();
    mainWindow.setBackgroundRole(QPalette::ColorRole::Base);
    mainWindow.show();
    return app.exec();
}
