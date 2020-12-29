#ifndef MQTTWRAPPER_H
#define MQTTWRAPPER_H

#include <mqtt_conf_data.h>

namespace mqtt_wrapper
{

class MqttWrapper
{
public:
    MqttWrapper() = default;
    ~MqttWrapper() = default;
    int Receiver();
    int Publisher(const char* data, const std::string topic);

private:
    MqttConfData mqttConfData;
};

} // namespace mqtt_wrapper


#endif // MQTTWRAPPER_H
