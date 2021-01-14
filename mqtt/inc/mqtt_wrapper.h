#ifndef MQTTWRAPPER_H
#define MQTTWRAPPER_H

#include <mqtt_conf_data.h>
#include <../app/inc/rasp0_sensor_data.h>
#include <../app/inc/rasp3b_sensor_data.h>
#include <QObject>

class SunshineDesktop;

namespace mqtt_wrapper
{

class MqttWrapper: public QObject
{
    Q_OBJECT
public:
    MqttWrapper() = default;
    ~MqttWrapper() = default;
    int Receiver(SunshineDesktop& sunshineDesktop);
    int Publisher(const char* data, const std::string topic);

signals:
    void setTempRasp3BSignal(const double value);
    void setHumRasp3BSignal(const double value);
    void setTvocRasp3BSignal(const double value);
    void setCo2Rasp3BSignal(const double value);

    void setTempRasp0Signal(const double value);
    void setHumRasp0Signal(const double value);
    void setTvocRasp0Signal(const double value);
    void setCo2Rasp0Signal(const double value);

    void setTempFreqRasp3BSignal(const double value);
    void setHumFreqRasp3BSignal(const double value);
    void setTvocFreqRasp3BSignal(const double value);
    void setCo2FreqRasp3BSignal(const double value);

    void setTempFreqRasp0Signal(const double value);
    void setHumFreqRasp0Signal(const double value);
    void setTvocFreqRasp0Signal(const double value);
    void setCo2FreqRasp0Signal(const double value);

public:
    MqttConfData mqttConfData;

};

} // namespace mqtt_wrapper


#endif // MQTTWRAPPER_H
