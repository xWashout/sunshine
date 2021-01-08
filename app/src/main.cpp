﻿#include <inc/sunshinedesktop.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SunshineDesktop mainWindow;
    mainWindow.setWindowTitle("Weather Station");
    mainWindow.show();

    return a.exec();
}
