#ifndef MQTT_CONF_DATA_H
#define MQTT_CONF_DATA_H

#include <string>
#include <mqtt/string_collection.h>

namespace mqtt_wrapper {

struct MqttConfData {
    const std::string serverAddress { "broker.hivemq.com:1883" };

    const mqtt::string_collection topics { "rasp3b_temperature", "rasp3b_humidity", "rasp3b_tvoc", "rasp3b_co2",
                                           "rasp0_temperature", "rasp0_humidity", "rasp0_tvoc", "rasp0_co2" };

    const std::vector<int> qualityOfServices { 1, 1, 1, 1, 1, 1, 1, 1 };

    const std::string clientId { "desktop_application" };

    const std::string outTopic {"measFreq"};

    const char* lastWillAndStatement = "Last will and testament.";
};

} // namespace mqtt_wrapper
#endif // MQTT_CONF_DATA_H
