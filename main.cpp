#include "mainwindow.h"

#include <QApplication>

///
/// \brief В мейне создается объект на главное окно и запускается приложение
///

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
