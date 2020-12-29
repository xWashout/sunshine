#ifndef RASP0SENSORDATA_H
#define RASP0SENSORDATA_H

#include <mutex>

namespace sensor_data {

class Rasp0SensorData
{
private:
    std::mutex mtx;

    double temperature = 0;
    double humidity = 0;
    double tvoc = 0;
    double co2 = 0;
    int currentMeasFreq = 0; //seconds
public:
    Rasp0SensorData() = default;
    ~Rasp0SensorData() = default;

    double getTemperature();
    void setTemperature(double value);
    double getHumidity();
    void setHumidity(double value);
    double getTvoc();
    void setTvoc(double value);
    double getCo2();
    void setCo2(double value);
    int getCurrentMeasFreq();
    void setCurrentMeasFreq(int value);
};

} // namespace sensor_data

#endif // RASP0SENSORDATA_H
