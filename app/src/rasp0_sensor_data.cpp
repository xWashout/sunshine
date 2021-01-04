#include "rasp0_sensor_data.h"

namespace sensor_data {

double Rasp0SensorData::getHumidity()
{
    std::lock_guard lck(mtx);
    double humidity = this->humidity;

    return humidity;
}

void Rasp0SensorData::setHumidity(double value)
{
    std::lock_guard lck(mtx);
    this->humidity = value;
}

double Rasp0SensorData::getTvoc()
{
    std::lock_guard lck(mtx);
    double tvoc = this->tvoc;

    return tvoc;
}

void Rasp0SensorData::setTvoc(double value)
{
    std::lock_guard lck(mtx);
    this->tvoc = value;
}

double Rasp0SensorData::getCo2()
{
    std::lock_guard lck(mtx);
    double co2 = this->co2;

    return co2;
}

void Rasp0SensorData::setCo2(double value)
{
    std::lock_guard lck(mtx);
    this->co2 = value;
}

int Rasp0SensorData::getCurrentMeasFreq()
{
    std::lock_guard lck(mtx);
    double currentMeasFreq = this->currentMeasFreq;

    return currentMeasFreq;
}

void Rasp0SensorData::setCurrentMeasFreq(int value)
{
    std::lock_guard lck(mtx);
    this->currentMeasFreq = value;
}

double Rasp0SensorData::getTemperature()
{
    std::lock_guard lck(mtx);
    double temperature = this->temperature;

    return temperature;
}

void Rasp0SensorData::setTemperature(double value)
{
    std::lock_guard lck(mtx);
    this->temperature = value;
}

void Rasp0SensorData::debugPrint() {
    std::lock_guard lck(mtx);
    printf(
    "--Rasp0 Data--\n"
    "temperature = %f\n"
    "humidity = %f\n"
    "tvoc = %f\n"
    "co2 = %f\n"
    "currentMeasFreq = %d\n",
    this->temperature, this->humidity, this->tvoc, this->co2, this->currentMeasFreq);
}

} // namespace sensor_data
