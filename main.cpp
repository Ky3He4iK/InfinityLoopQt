#include "gui/MainWindow.h"
#include <QApplication>
#include <QCommandLineParser>
#include <iostream>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QApplication::setApplicationVersion("0.1");
    QApplication::setApplicationName("InfinityLoopQt");

    QCommandLineParser parser;
    parser.setApplicationDescription("A clone of the game named infinity loop. Written using Qt");
    auto helpOption = parser.addHelpOption();
    auto versionOption = parser.addVersionOption();
    parser.addOptions({
                              {QStringList() << "x" << "w" << "width",
                                                                 QApplication::translate("main",
                                                                                         "<width> cells in single row"),
                                      QApplication::translate(
                                              "main", "width"),  "5"},
                              {QStringList() << "y" << "height",
                                                                 QApplication::translate("main",
                                                                                         "<height> cells in single column"),
                                      QApplication::translate(
                                              "main", "height"), "6"},
                              {QStringList() << "s" << "size",   QApplication::translate("main",
                                                                                         "icon size in pixels"),
                                      QApplication::translate(
                                              "main", "size"),   "50"},
                              {
                               QStringList() << "S" << "solver", QApplication::translate("main",
                                                                                         "solve level with built-in solver before showing. Solver levels:\n\t1 - do not use\n"
                                                                                         "\t2 - use only generic algorithm\n"
                                                                                         "\t3 - use brute-force algorithm for some cases that not solved by generic algorithm\n"
                                                                                         "\t4 - use brute-force algorithm for some cases + some optimizations"),
                                      QApplication::translate(
                                              "main", "level"),  "1"}
                      });
    parser.process(app);
    if (parser.isSet(versionOption)) {
        std::cout << qPrintable(app.applicationName()) << ' ' << qPrintable(app.applicationVersion()) << '\n';
        return 0;
    }
    if (parser.isSet(helpOption))
        parser.showHelp();

    QString width = parser.value("width");
    bool ok;
    size_t w = width.toInt(&ok);
    if (!ok) {
        std::cout << "Error: <width> is invalid!\nGiven value: " << qPrintable(width) << '\n';
        return 1;
    }
    bool ok2;
    QString height = parser.value("height");
    size_t h = height.toInt(&ok2);
    if (!ok2) {
        std::cout << "Error: <height> is invalid!\nGiven value: " << qPrintable(height) << '\n';
        return 1;
    }
    QString size = parser.value("size");
    size_t s = size.toInt(&ok2);
    if (!ok2) {
        std::cout << "Error: <size> is invalid!\nGiven value: " << qPrintable(size) << '\n';
        return 1;
    }

    QString solverLvl = parser.value("solver");
    size_t sl = solverLvl.toInt(&ok2);
    if (!ok2) {
        std::cout << "Error: <size> is invalid!\nGiven value: " << qPrintable(solverLvl) << '\n';
        return 1;
    }

    MainWindow mainWindow(w, h, s, sl);
    return QApplication::exec();
}
