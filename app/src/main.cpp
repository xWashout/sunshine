#include <inc/sunshinedesktop.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SunshineDesktop mainWindow;
//    QApplication::setStyle(QStyleFactory::create("Fusion"));
//    QPalette palette= QApplication::palette();
//    palette.setColor(QPalette::Window, QColor(102,178,255));
//    QApplication::setPalette(palette);
    mainWindow.setWindowTitle("Weather Station");
    mainWindow.show();

    return a.exec();
}
