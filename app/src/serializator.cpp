#include <serializator.h>

#include <QDebug>
#include <QDir>
#include <cstdio>
#include <string>
#include <iostream>
#include <cstring>

namespace tool {

Serializator::Serializator():sessionFile(nullptr, &std::fclose)
{
    QDir::setCurrent("/home/washout/repos/sunshine/serialized_sessions");
}

void Serializator::newSession(const std::string fileName,
                              sensor_data::Rasp0SensorData& rasp0SendorData,
                              sensor_data::Rasp3BSensorData& rasp3BSendorData)
{
    std::cerr << "fileName == " << fileName;
    if(this->sessionFile) {
        qDebug() << "File already opened, close file and open new";
        this->closeSession(rasp0SendorData, rasp3BSendorData);
        this->sessionFile.reset(std::fopen(fileName.c_str(), "a+"));
    }
    else {
        this->sessionFile.reset(std::fopen(fileName.c_str(), "a+"));
    }

    if(this->sessionFile) {
        qDebug() << "File created correctly";
    }
    else {
        qDebug() << "File didn't open";
    }
}

void Serializator::loadSession(const std::string fileName,
                               sensor_data::Rasp0SensorData& rasp0SendorData,
                               sensor_data::Rasp3BSensorData& rasp3BSendorData)
{
    std::cerr << "fileName == " << fileName;
    if(this->sessionFile) {
        qDebug() << "File already opened, close file and open new";
        this->closeSession(rasp0SendorData, rasp3BSendorData);
        this->sessionFile.reset(std::fopen(fileName.c_str(), "a+"));
    }
    else {
        this->sessionFile.reset(std::fopen(fileName.c_str(), "a+"));
    }

    if(this->sessionFile) {
        qDebug() << "File created correctly";
    }
    else {
        qDebug() << "File didn't open";
    }

    int lineLength = 50;
    char line[lineLength];
    const char *delim{" \n"};
    char *words = nullptr;
    int i = 0;
    while(fgets(line, lineLength, this->sessionFile.get()))
    {qDebug() << "i=" << line;
        ++i;
        if(line != nullptr)
        {
            words = std::strtok(line, delim);
        }

        while(words != nullptr)
        {
            qDebug() << words << "\n";
            if(!std::strcmp(words, "rasp3b_temp"))
            {
                words = std::strtok(nullptr, delim);
                rasp3BSendorData.addTemperatureMeasurement(std::strtod(words, nullptr));
                break;
            }
            else if(!std::strcmp(words, "rasp3b_hum"))
            {
                words = std::strtok(nullptr, delim);
                rasp3BSendorData.addHumidityMeasurement(std::strtod(words, nullptr));
                break;
            }
            else if(!std::strcmp(words, "rasp3b_tvoc"))
            {
                words = std::strtok(nullptr, delim);
                rasp3BSendorData.addTvocMeasurement(std::strtod(words, nullptr));
                break;
            }
            else if(!std::strcmp(words, "rasp3b_co2"))
            {
                words = std::strtok(nullptr, delim);
                rasp3BSendorData.addCo2Measurement(std::strtod(words, nullptr));
                break;
            }
            else if(!std::strcmp(words, "rasp0_temp"))
            {
                words = std::strtok(nullptr, delim);
                rasp0SendorData.addTemperatureMeasurement(std::strtod(words, nullptr));
                break;
            }
            else if(!std::strcmp(words, "rasp0_hum"))
            {
                words = std::strtok(nullptr, delim);
                rasp0SendorData.addHumidityMeasurement(std::strtod(words, nullptr));
                break;
            }
            else if(!std::strcmp(words, "rasp0_tvoc"))
            {
                words = std::strtok(nullptr, delim);
                rasp0SendorData.addTvocMeasurement(std::strtod(words, nullptr));
                break;
            }
            else if(!std::strcmp(words, "rasp0_co2"))
            {
                words = std::strtok(nullptr, delim);
                rasp0SendorData.addCo2Measurement(std::strtod(words, nullptr));
                break;
            }
            break;
        }
    }
    this->sessionFile.reset(std::fopen(fileName.c_str(), "w"));
}

void Serializator::closeSession(sensor_data::Rasp0SensorData& rasp0SendorData,
                                sensor_data::Rasp3BSensorData& rasp3BSendorData)
{
    if(!this->sessionFile) {
        qDebug() << "close session-> File didn't open, serialization skipped";
        return;
    }

    for(const auto value: rasp3BSendorData.getTemperatureMeasurements()) {
        std::string rasp3bName {"rasp3b_temp "};
        rasp3bName.append(std::to_string(value) + "\n");
        std:fputs(rasp3bName.c_str(), this->sessionFile.get());
        std::fflush(this->sessionFile.get());
    }

    for(const auto value: rasp3BSendorData.getHumidityMeasurements()) {
        std::string rasp3bName {"rasp3b_hum "};
        rasp3bName.append(std::to_string(value) + "\n");
        std::fputs(rasp3bName.c_str(), this->sessionFile.get());
        std::fflush(this->sessionFile.get());
    }

    for(const auto value: rasp3BSendorData.getTvocMeasurements()) {
        std::string rasp3bName {"rasp3b_tvoc "};
        rasp3bName.append(std::to_string(value) + "\n");
        std::fputs(rasp3bName.c_str(), this->sessionFile.get());
        std::fflush(this->sessionFile.get());
    }

    for(const auto value: rasp3BSendorData.getCo2Measurements()) {
        std::string rasp3bName {"rasp3b_co2 "};
        rasp3bName.append(std::to_string(value) + "\n");
        std::fputs(rasp3bName.c_str(), this->sessionFile.get());
        std::fflush(this->sessionFile.get());
    }

    for(const auto value: rasp0SendorData.getTemperatureMeasurements()) {
        std::string rasp0Name {"rasp0_temp "};
        rasp0Name.append(std::to_string(value) + "\n");
        std::fputs(rasp0Name.c_str(), this->sessionFile.get());
        std::fflush(this->sessionFile.get());
    }

    for(const auto value: rasp0SendorData.getHumidityMeasurements()) {
        std::string rasp0Name {"rasp0_hum "};
        rasp0Name.append(std::to_string(value) + "\n");
        std::fputs(rasp0Name.c_str(), this->sessionFile.get());
        std::fflush(this->sessionFile.get());
    }

    for(const auto value: rasp0SendorData.getTvocMeasurements()) {
        std::string rasp0Name {"rasp0_tvoc "};
        rasp0Name.append(std::to_string(value) + "\n");
        std::fputs(rasp0Name.c_str(), this->sessionFile.get());
        std::fflush(this->sessionFile.get());
    }

    for(const auto value: rasp0SendorData.getCo2Measurements()) {
        std::string rasp0Name {"rasp0_co2 "};
        rasp0Name.append(std::to_string(value) + "\n");
        std::fputs(rasp0Name.c_str(), this->sessionFile.get());
        std::fflush(this->sessionFile.get());
    }
    rasp0SendorData.clearData();
    rasp3BSendorData.clearData();

    qDebug() << "Serialization complete";
}

} // tool
