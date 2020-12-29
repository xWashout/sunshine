#include "rasp3b_sensor_data.h"

namespace sensor_data {

double Rasp3BSensorData::getHumidity()
{
    mtx.lock();
    double humidity = this->humidity;
    mtx.unlock();
    return humidity;
}

void Rasp3BSensorData::setHumidity(double value)
{
    mtx.lock();
    this->humidity = value;
    mtx.unlock();
}

double Rasp3BSensorData::getTvoc()
{
    mtx.lock();
    double tvoc = this->tvoc;
    mtx.unlock();
    return tvoc;
}

void Rasp3BSensorData::setTvoc(double value)
{
    mtx.lock();
    this->tvoc = value;
    mtx.unlock();
}

double Rasp3BSensorData::getCo2()
{
    mtx.lock();
    double co2 = this->co2;
    mtx.unlock();
    return co2;
}

void Rasp3BSensorData::setCo2(double value)
{
    mtx.lock();
    this->co2 = value;
    mtx.unlock();
}

int Rasp3BSensorData::getCurrentMeasFreq()
{
    mtx.lock();
    double currentMeasFreq = this->currentMeasFreq;
    mtx.unlock();
    return currentMeasFreq;
}

void Rasp3BSensorData::setCurrentMeasFreq(int value)
{
    mtx.lock();
    this->currentMeasFreq = value;
    mtx.unlock();
}

double Rasp3BSensorData::getTemperature()
{
    mtx.lock();
    double temperature = this->temperature;
    mtx.unlock();
    return temperature;
}

void Rasp3BSensorData::setTemperature(double value)
{
    mtx.lock();
    this->temperature = value;
    mtx.unlock();
}

} // namespace sensor_data
