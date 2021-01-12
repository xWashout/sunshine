#include <measurements_data.h>

namespace sensor_data {

std::vector<double>& MeasurementsData::getTemperatureMeasurements()
{
    return temperatureMeasurements;
}

void MeasurementsData::setTemperatureMeasurements(const std::vector<double> &value)
{
    temperatureMeasurements = value;
}

std::vector<double>& MeasurementsData::getHumidityMeasurements()
{
    return humidityMeasurements;
}

void MeasurementsData::setHumidityMeasurements(const std::vector<double> &value)
{
    humidityMeasurements = value;
}

std::vector<double>& MeasurementsData::getTvocMeasurements()
{
    return tvocMeasurements;
}

void MeasurementsData::setTvocMeasurements(const std::vector<double> &value)
{
    tvocMeasurements = value;
}

void MeasurementsData::setCo2Measurements(const std::vector<double> &value)
{
    co2Measurements = value;
}

std::vector<double>& MeasurementsData::getCo2Measurements()
{
    return co2Measurements;
}

void sensor_data::MeasurementsData::clearData()
{
    temperatureMeasurements.clear();
    humidityMeasurements.clear();
    tvocMeasurements.clear();
    co2Measurements.clear();
}

void sensor_data::MeasurementsData::addTemperatureMeasurement(double value)
{
    this->temperatureMeasurements.emplace_back(value);
}

void sensor_data::MeasurementsData::addHumidityMeasurement(double value)
{
    this->humidityMeasurements.emplace_back(value);
}

void sensor_data::MeasurementsData::addTvocMeasurement(double value)
{
    this->tvocMeasurements.emplace_back(value);
}

void sensor_data::MeasurementsData::addCo2Measurement(double value)
{
    this->co2Measurements.emplace_back(value);
}

}
