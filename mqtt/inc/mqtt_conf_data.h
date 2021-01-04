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

    const std::string clientIdReceiver { "desktop_application_receiver" };
    const std::string clientIdPublisher { "desktop_application_publisher" };

    const char* lastWillAndStatement = "Last will and testament.";

    const std::string rasp3bTempTopic { "rasp3b_temperature" };
    const std::string rasp3bHumTopic { "rasp3b_humidity" };
    const std::string rasp3bTvocTopic { "rasp3b_tvoc" };
    const std::string rasp3bCo2Topic { "rasp3b_co2" };

    const std::string rasp0TempTopic { "rasp0_temperature" };
    const std::string rasp0HummTopic { "rasp0_humidity" };
    const std::string rasp0TvocTopic { "rasp0_tvoc" };
    const std::string rasp0Co2Topic { "rasp0_co2" };
};

} // namespace mqtt_wrapper
#endif // MQTT_CONF_DATA_H
