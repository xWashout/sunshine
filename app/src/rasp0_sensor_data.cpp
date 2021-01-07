#include "rasp0_sensor_data.h"
#include <QDebug>

namespace sensor_data {

Rasp0SensorData::Rasp0SensorData()
{
    temperatureMeasurements.reserve(100);
    humidityMeasurements.reserve(100);
    tvocMeasurements.reserve(100);
    co2Measurements.reserve(100);
}

const std::vector<double> Rasp0SensorData::getTemperatureMeasurements() const
{
    std::lock_guard lck(mtx);
    return this->temperatureMeasurements;
}

const std::vector<double> Rasp0SensorData::getHumidityMeasurements() const
{
    std::lock_guard lck(mtx);
    return this->humidityMeasurements;
}

const std::vector<double> Rasp0SensorData::getTvocMeasurements() const
{
    std::lock_guard lck(mtx);
    return this->tvocMeasurements;
}

const std::vector<double> Rasp0SensorData::getCo2Measurements() const
{
    std::lock_guard lck(mtx);
    return this->co2Measurements;
}

void Rasp0SensorData::addTemperatureMeasurement(double value)
{
    std::lock_guard lck(mtx);
    this->temperatureMeasurements.emplace_back(value);
}

void Rasp0SensorData::addHumidityMeasurement(double value)
{
    std::lock_guard lck(mtx);
    this->humidityMeasurements.emplace_back(value);
}

void Rasp0SensorData::addTvocMeasurement(double value)
{
    std::lock_guard lck(mtx);
    this->tvocMeasurements.emplace_back(value);
}

void Rasp0SensorData::addCo2Measurement(double value)
{
    std::lock_guard lck(mtx);
    this->co2Measurements.emplace_back(value);
}

void Rasp0SensorData::clearData()
{
    this->co2Measurements.clear();
    this->tvocMeasurements.clear();
    this->humidityMeasurements.clear();
    this->temperatureMeasurements();
    qDebug() << "Rasp0SensorData cleaned";
}

} // namespace sensor_data
