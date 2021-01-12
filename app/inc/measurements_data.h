#ifndef MEASUREMENTSDATA_H
#define MEASUREMENTSDATA_H

#include <vector>

namespace sensor_data {

class MeasurementsData {

    std::vector<double> temperatureMeasurements;
    std::vector<double> humidityMeasurements;
    std::vector<double> tvocMeasurements;
    std::vector<double> co2Measurements;

public:
    MeasurementsData() = default;
    ~MeasurementsData() = default;

    std::vector<double>& getTemperatureMeasurements();
    void setTemperatureMeasurements(const std::vector<double> &value);
    std::vector<double>& getHumidityMeasurements();
    void setHumidityMeasurements(const std::vector<double> &value);
    std::vector<double>& getTvocMeasurements();
    void setTvocMeasurements(const std::vector<double> &value);
    std::vector<double>& getCo2Measurements();
    void setCo2Measurements(const std::vector<double> &value);

    void addTemperatureMeasurement(double value);
    void addHumidityMeasurement(double value);
    void addTvocMeasurement(double value);
    void addCo2Measurement(double value);

    void clearData();
};

} // sensor_data

#endif // MEASUREMENTSDATA_H
