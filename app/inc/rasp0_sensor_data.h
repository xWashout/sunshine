#ifndef RASP0SENSORDATA_H
#define RASP0SENSORDATA_H

#include <mutex>
#include <vector>

namespace sensor_data {

class Rasp0SensorData
{
private:
    mutable std::mutex mtx;

    std::vector<double> temperatureMeasurements;
    std::vector<double> humidityMeasurements;
    std::vector<double> tvocMeasurements;
    std::vector<double> co2Measurements;

public:
    Rasp0SensorData();
    ~Rasp0SensorData() = default;

    const std::vector<double> getTemperatureMeasurements() const;
    const std::vector<double> getHumidityMeasurements() const;
    const std::vector<double> getTvocMeasurements() const;
    const std::vector<double> getCo2Measurements() const;

    void addTemperatureMeasurement(double value);
    void addHumidityMeasurement(double value);
    void addTvocMeasurement(double value);
    void addCo2Measurement(double value);
};

} // namespace sensor_data

#endif // RASP0SENSORDATA_H
