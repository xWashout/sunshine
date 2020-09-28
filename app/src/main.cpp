#include <inc/sunshinedesktop.h>
#include <mqtt_wrapper.h>
#include <QApplication>
#include <mqtt_wrapper.h>

int main(int argc, char *argv[])
{
    MqttWrapper mqttWrapper;
    mqttWrapper.Receiver();
    QApplication a(argc, argv);
    SunshineDesktop w;
    w.show();
    return a.exec();
}
