#include <serializator.h>

#include <QDebug>
#include <QDir>
#include <stdio.h>
#include <string>
#include <iostream>

namespace tool {

Serializator::Serializator()
{
    QDir::setCurrent("/home/washout/repos/sunshine/serialized_sessions");
}

void Serializator::newSession(const std::string fileName, sensor_data::Rasp0SensorData& rasp0SendorData,
                              sensor_data::Rasp3BSensorData& rasp3BSendorData)
{
    if(this->sessionFile == NULL) {
        this->sessionFile = fopen(fileName.c_str(), "a+");
    }
    else {
        qDebug() << "File already opened, close file and open new";
        this->closeSession(rasp0SendorData, rasp3BSendorData);
    }

    if(this->sessionFile == NULL) {
        qDebug() << "File didn't open";
        return;
    }
    else {
        qDebug() << "File created correctly";
    }
}

void Serializator::loadSession(const std::string fileName, sensor_data::Rasp0SensorData& rasp0SendorData,
                               sensor_data::Rasp3BSensorData& rasp3BSendorData)
{
    if(this->sessionFile == NULL) {
        this->sessionFile = fopen(fileName.c_str(), "a+");
    }
    else {
        qDebug() << "File already opened, close file and open new";
        this->closeSession(rasp0SendorData, rasp3BSendorData);
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
        qDebug() << "close session-> File didn't open, serialization skipped";
        return;
    }

    for(const auto value: rasp3BSendorData.getTemperatureMeasurements()) {
        std::string rasp3bName {"rasp3b_temp "};
        rasp3bName.append(std::to_string(value) + "\n");
        std::cerr << rasp3bName;
        fputs(rasp3bName.c_str(), this->sessionFile);
        fflush(this->sessionFile);
    }

    for(const auto value: rasp3BSendorData.getHumidityMeasurements()) {
        std::string rasp3bName {"rasp3b_hum "};
        rasp3bName.append(std::to_string(value) + "\n");
        fputs(rasp3bName.c_str(), this->sessionFile);
        fflush(this->sessionFile);
    }

    for(const auto value: rasp3BSendorData.getTvocMeasurements()) {
        std::string rasp3bName {"rasp3b_tvoc "};
        rasp3bName.append(std::to_string(value) + "\n");
        fputs(rasp3bName.c_str(), this->sessionFile);
        fflush(this->sessionFile);
    }

    for(const auto value: rasp3BSendorData.getCo2Measurements()) {
        std::string rasp3bName {"rasp3b_co2 "};
        rasp3bName.append(std::to_string(value) + "\n");
        fputs(rasp3bName.c_str(), this->sessionFile);
        fflush(this->sessionFile);
    }

    for(const auto value: rasp0SendorData.getTemperatureMeasurements()) {
        std::string rasp0Name {"rasp0_temp "};
        rasp0Name.append(std::to_string(value) + "\n");
        fputs(rasp0Name.c_str(), this->sessionFile);
        fflush(this->sessionFile);
    }

    for(const auto value: rasp0SendorData.getHumidityMeasurements()) {
        std::string rasp0Name {"rasp0_hum "};
        rasp0Name.append(std::to_string(value) + "\n");
        fputs(rasp0Name.c_str(), this->sessionFile);
        fflush(this->sessionFile);
    }

    for(const auto value: rasp0SendorData.getTvocMeasurements()) {
        std::string rasp0Name {"rasp0_tvoc "};
        rasp0Name.append(std::to_string(value) + "\n");
        fputs(rasp0Name.c_str(), this->sessionFile);
        fflush(this->sessionFile);
    }

    for(const auto value: rasp0SendorData.getCo2Measurements()) {
        std::string rasp0Name {"rasp0_co2 "};
        rasp0Name.append(std::to_string(value) + "\n");
        fputs(rasp0Name.c_str(), this->sessionFile);
        fflush(this->sessionFile);
    }

    fclose(this->sessionFile);
    raspSendorData.clearData();
    rasp3BSendorData.clearData();

    qDebug() << "Serialization complete -> File closed";
}

} // tool
