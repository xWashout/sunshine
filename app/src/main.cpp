#include <inc/sunshinedesktop.h>
#include <mqtt_wrapper.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SunshineDesktop w;
    w.show();
    return a.exec();
}
