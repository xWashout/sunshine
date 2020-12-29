#include <inc/sunshinedesktop.h>
#include <mqtt_wrapper.h>
#include <QApplication>
#include <mqtt_wrapper.h>
#include <thread>
#include <iostream>
int main(int argc, char *argv[])
{
    mqtt_wrapper::MqttWrapper mqttWrapper;

    std::thread mqttThread(&mqtt_wrapper::MqttWrapper::Receiver, &mqttWrapper);
    mqttThread.detach();

//    mqttWrapper.Publisher("DATA TESTOWA DO PYTHONA", "measFreq");
    QApplication a(argc, argv);
    SunshineDesktop w;
    w.show();

    return a.exec();
}
