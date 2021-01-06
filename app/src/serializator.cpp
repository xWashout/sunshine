#include <serializator.h>

#include <QDebug>
#include <QDir>
#include <stdio.h>
#include <string>

namespace tool {

Serializator::Serializator()
{
    QDir::setCurrent("/home/washout/repos/sunshine/serialized_sessions");
}

Serializator::~Serializator()
{
}

void Serializator::newSession(const std::string& fileName)
{
    if(this->sessionFile == NULL) {
        this->sessionFile = fopen(fileName.c_str(), "a+");
    }
    else {
        qDebug() << "File already opened, close file and open new";
        fclose(this->sessionFile);
        this->sessionFile = fopen(fileName.c_str(), "a+");
    }

    if(this->sessionFile == NULL) {
        qDebug() << "File didn't open";
        return;
    }
    else {
        qDebug() << "File created correctly";
    }
}

void Serializator::closeSession(sensor_data::Rasp0SensorData& rasp0SendorData,
                                sensor_data::Rasp3BSensorData& rasp3BSendorData)
{
    if(this->sessionFile == NULL) {
        qDebug() << "close session-> File didn't open, serialization failed";
        return;
    }

    std::string rasp0Name {"rasp0"};

    for(const auto value: rasp0SendorData.getTemperatureMeasurements()) {
        rasp0Name.append(" ");
        rasp0Name.append(std::to_string(value) + "\n");
        fputs(rasp0Name.c_str(), this->sessionFile);
        fflush(this->sessionFile);
    }

    for(const auto value: rasp0SendorData.getHumidityMeasurements()) {
        rasp0Name.append(" ");
        rasp0Name.append(std::to_string(value) + "\n");
        fputs(rasp0Name.c_str(), this->sessionFile);
        fflush(this->sessionFile);
    }

    for(const auto value: rasp0SendorData.getTvocMeasurements()) {
        rasp0Name.append(" ");
        rasp0Name.append(std::to_string(value) + "\n");
        fputs(rasp0Name.c_str(), this->sessionFile);
        fflush(this->sessionFile);
    }

    for(const auto value: rasp0SendorData.getCo2Measurements()) {
        rasp0Name.append(" ");
        rasp0Name.append(std::to_string(value) + "\n");
        fputs(rasp0Name.c_str(), this->sessionFile);
        fflush(this->sessionFile);
    }

    std::string rasp3bName {"rasp3b"};

    for(const auto value: rasp0SendorData.getTemperatureMeasurements()) {
        rasp3bName.append(" ");
        rasp3bName.append(std::to_string(value) + "\n");
        fputs(rasp3bName.c_str(), this->sessionFile);
        fflush(this->sessionFile);
    }

    for(const auto value: rasp0SendorData.getHumidityMeasurements()) {
        rasp3bName.append(" ");
        rasp3bName.append(std::to_string(value) + "\n");
        fputs(rasp3bName.c_str(), this->sessionFile);
        fflush(this->sessionFile);
    }

    for(const auto value: rasp0SendorData.getTvocMeasurements()) {
        rasp3bName.append(" ");
        rasp3bName.append(std::to_string(value) + "\n");
        fputs(rasp3bName.c_str(), this->sessionFile);
        fflush(this->sessionFile);
    }

    for(const auto value: rasp0SendorData.getCo2Measurements()) {
        rasp3bName.append(" ");
        rasp3bName.append(std::to_string(value) + "\n");
        fputs(rasp3bName.c_str(), this->sessionFile);
        fflush(this->sessionFile);
    }

    fclose(this->sessionFile);
    qDebug() << "Serialization complete -> File closed";
}

void Serializator::loadSession(const std::string fileName)
{

}


} // tool
