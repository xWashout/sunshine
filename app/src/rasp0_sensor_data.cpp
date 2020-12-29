#include "rasp0_sensor_data.h"

namespace sensor_data {

double Rasp0SensorData::getHumidity()
{
    mtx.lock();
    double humidity = this->humidity;
    mtx.unlock();
    return humidity;
}

void Rasp0SensorData::setHumidity(double value)
{
    mtx.lock();
    this->humidity = value;
    mtx.unlock();
}

double Rasp0SensorData::getTvoc()
{
    mtx.lock();
    double tvoc = this->tvoc;
    mtx.unlock();
    return tvoc;
}

void Rasp0SensorData::setTvoc(double value)
{
    mtx.lock();
    this->tvoc = value;
    mtx.unlock();
}

double Rasp0SensorData::getCo2()
{
    mtx.lock();
    double co2 = this->co2;
    mtx.unlock();
    return co2;
}

void Rasp0SensorData::setCo2(double value)
{
    mtx.lock();
    this->co2 = value;
    mtx.unlock();
}

int Rasp0SensorData::getCurrentMeasFreq()
{
    mtx.lock();
    double currentMeasFreq = this->currentMeasFreq;
    mtx.unlock();
    return currentMeasFreq;
}

void Rasp0SensorData::setCurrentMeasFreq(int value)
{
    mtx.lock();
    this->currentMeasFreq = value;
    mtx.unlock();
}

double Rasp0SensorData::getTemperature()
{
    mtx.lock();
    double temperature = this->temperature;
    mtx.unlock();
    return temperature;
}

void Rasp0SensorData::setTemperature(double value)
{
    mtx.lock();
    this->temperature = value;
    mtx.unlock();
}

} // namespace sensor_data
