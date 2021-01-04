#include "rasp3b_sensor_data.h"

namespace sensor_data {

double Rasp3BSensorData::getHumidity()
{
    std::lock_guard lck(mtx);
    double humidity = this->humidity;

    return humidity;
}

void Rasp3BSensorData::setHumidity(double value)
{
    std::lock_guard lck(mtx);
    this->humidity = value;
}

double Rasp3BSensorData::getTvoc()
{
    std::lock_guard lck(mtx);
    double tvoc = this->tvoc;

    return tvoc;
}

void Rasp3BSensorData::setTvoc(double value)
{
    std::lock_guard lck(mtx);
    this->tvoc = value;
}

double Rasp3BSensorData::getCo2()
{
    std::lock_guard lck(mtx);
    double co2 = this->co2;

    return co2;
}

void Rasp3BSensorData::setCo2(double value)
{
    std::lock_guard lck(mtx);
    this->co2 = value;
}

int Rasp3BSensorData::getCurrentMeasFreq()
{
    std::lock_guard lck(mtx);
    double currentMeasFreq = this->currentMeasFreq;

    return currentMeasFreq;
}

void Rasp3BSensorData::setCurrentMeasFreq(int value)
{
    std::lock_guard lck(mtx);
    this->currentMeasFreq = value;
}

double Rasp3BSensorData::getTemperature()
{
    std::lock_guard lck(mtx);
    double temperature = this->temperature;

    return temperature;
}

void Rasp3BSensorData::setTemperature(double value)
{
    std::lock_guard lck(mtx);
    this->temperature = value;
}

void Rasp3BSensorData::debugPrint() {
    std::lock_guard lck(mtx);
    printf(
    "--Rasp3B Data--\n"
    "temperature = %f\n"
    "humidity = %f\n"
    "tvoc = %f\n"
    "co2 = %f\n"
    "currentMeasFreq = %d\n",
    this->temperature, this->humidity, this->tvoc, this->co2, this->currentMeasFreq);
}

} // namespace sensor_data
