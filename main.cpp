#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    //Necessary for QCustomPlot
    #if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
      QApplication::setGraphicsSystem("raster");
    #endif

    QApplication a(argc, argv);

    //THIS LITTLE BIT HERE IS NECESSARY FOR SAVING WINDOW GEOMETRY SETTINGS ETC.
    QCoreApplication::setOrganizationName("QtProject");
    QCoreApplication::setApplicationName("Application Example");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);

    MainWindow w;
    w.show();
    return a.exec();
}


