#ifndef MQTT_CONF_DATA_H
#define MQTT_CONF_DATA_H

#include <string>
#include <mqtt/string_collection.h>

namespace mqtt_wrapper {

struct MqttConfData {
    const std::string serverAddress { "broker.hivemq.com:1883" };

    const mqtt::string_collection topics { "rasp3BTemperature", "rasp3BHumidity", "rasp3BTvoc", "rasp3BCo2",
                                           "rasp0Temperature", "rasp0Humidity", "rasp0Tvoc", "rasp0Co2",
                                           "rasp3BFreqTemp", "rasp3BFreqHum", "rasp3BFreqTvoc", "rasp3BFreqCo2",
                                           "rasp0FreqTemp", "rasp0FreqHum", "rasp0FreqTvoc", "rasp0FreqCo2"};

    const std::vector<int> qualityOfServices { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

    const std::string clientIdReceiver { "desktop_application_receiver" };
    const std::string clientIdPublisher { "desktop_application_publisher" };

    const char* lastWillAndStatement = "Last will and testament.";

    const std::string rasp3bTempTopic { "rasp3BTemperature" };
    const std::string rasp3bHumTopic  { "rasp3BHumidity" };
    const std::string rasp3bTvocTopic { "rasp3BTvoc" };
    const std::string rasp3bCo2Topic  { "rasp3BCo2" };

    const std::string rasp0TempTopic { "rasp0Temperature" };
    const std::string rasp0HummTopic { "rasp0Humidity" };
    const std::string rasp0TvocTopic { "rasp0Tvoc" };
    const std::string rasp0Co2Topic  { "rasp0Co2" };

    const std::string rasp3bFreqTemp { "rasp3BFreqTemp" };
    const std::string rasp3bFreqHum  { "rasp3BFreqHum" };
    const std::string rasp3bFreqTvoc { "rasp3BFreqTvoc" };
    const std::string rasp3bFreqCo2  { "rasp3BFreqCo2" };

    const std::string rasp0FreqTemp { "rasp0FreqTemp" };
    const std::string rasp0FreqHum  { "rasp0FreqHum" };
    const std::string rasp0FreqTvoc { "rasp0FreqTvoc" };
    const std::string rasp0FreqCo2  { "rasp0FreqCo2" };
};

} // namespace mqtt_wrapper
#endif // MQTT_CONF_DATA_H
