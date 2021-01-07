#include "rasp3b_sensor_data.h"
#include <QDebug>

namespace sensor_data {

Rasp3BSensorData::Rasp3BSensorData()
{
    temperatureMeasurements.reserve(100);
    humidityMeasurements.reserve(100);
    tvocMeasurements.reserve(100);
    co2Measurements.reserve(100);
}

const std::vector<double> Rasp3BSensorData::getTemperatureMeasurements() const
{
    std::lock_guard lck(mtx);
    return this->temperatureMeasurements;
}

const std::vector<double> Rasp3BSensorData::getHumidityMeasurements() const
{
    std::lock_guard lck(mtx);
    return this->humidityMeasurements;
}

const std::vector<double> Rasp3BSensorData::getTvocMeasurements() const
{
    std::lock_guard lck(mtx);
    return this->tvocMeasurements;
}

const std::vector<double> Rasp3BSensorData::getCo2Measurements() const
{
    std::lock_guard lck(mtx);
    return this->co2Measurements;
}

void Rasp3BSensorData::addTemperatureMeasurement(double value)
{
    std::lock_guard lck(mtx);
    this->temperatureMeasurements.emplace_back(value);
}

void Rasp3BSensorData::addHumidityMeasurement(double value)
{
    std::lock_guard lck(mtx);
    this->humidityMeasurements.emplace_back(value);
}

void Rasp3BSensorData::addTvocMeasurement(double value)
{
    std::lock_guard lck(mtx);
    this->tvocMeasurements.emplace_back(value);
}

void Rasp3BSensorData::addCo2Measurement(double value)
{
    std::lock_guard lck(mtx);
    this->co2Measurements.emplace_back(value);
}

void Rasp3BSensorData::clearData()
{
    this->co2Measurements.clear();
    this->tvocMeasurements.clear();
    this->humidityMeasurements.clear();
    this->temperatureMeasurements();
    qDebug() << "Rasp3BSensorData cleaned";
}

} // namespace sensor_data
