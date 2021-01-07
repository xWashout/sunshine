#ifndef RASP3BSENSORDATA_H
#define RASP3BSENSORDATA_H

#include<mutex>
#include <vector>

namespace sensor_data {

class Rasp3BSensorData
{
private:
    mutable std::mutex mtx;

    std::vector<double> temperatureMeasurements;
    std::vector<double> humidityMeasurements;
    std::vector<double> tvocMeasurements;
    std::vector<double> co2Measurements;

public:
    Rasp3BSensorData();
    ~Rasp3BSensorData() = default;

    const std::vector<double> getTemperatureMeasurements() const;
    const std::vector<double> getHumidityMeasurements() const;
    const std::vector<double> getTvocMeasurements() const;
    const std::vector<double> getCo2Measurements() const;

    void addTemperatureMeasurement(double value);
    void addHumidityMeasurement(double value);
    void addTvocMeasurement(double value);
    void addCo2Measurement(double value);

    void clearData();
};

} // namespace sensor_data

#endif // RASP3BSENSORDATA_H
