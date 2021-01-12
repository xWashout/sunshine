#ifndef SERIALIZATOR_H
#define SERIALIZATOR_H

#include <QFile>
#include <rasp0_sensor_data.h>
#include <rasp3b_sensor_data.h>
#include <measurements_data.h>
#include <memory>
#include <QDebug>
#include <QDir>
#include <cstdio>
#include <string>
#include <iostream>
#include <cstring>

namespace tool {

template <class T1, class T2>
class Serializator
{
public:

    Serializator():
        sessionFile(nullptr, &std::fclose)
    {
        QDir::setCurrent("/home/washout/repos/sunshine/serialized_sessions");
    }

    ~Serializator() = default;

    void newSession(const std::string& fileName,
                                  sensor_data::Rasp0SensorData& rasp0SensorData,
                                  sensor_data::Rasp3BSensorData& rasp3BSensorData)
    {
        std::cerr << "fileName == " << fileName;
        if(this->sessionFile)
        {
            qDebug() << "<Debug> File already opened, close file and open new";
            this->closeSession(rasp0SensorData, rasp3BSensorData);
            this->sessionFile.reset(std::fopen(fileName.c_str(), "a+"));
        }
        else
        {
            this->sessionFile.reset(std::fopen(fileName.c_str(), "a+"));
        }

        if(this->sessionFile)
        {
            qDebug() << "<Debug> File created correctly";
        }
        else
        {
            qDebug() << "<Debug> File didn't open";
        }
    }



    int loadSession(const std::string& fileName, T1& rasp0SensorData, T2& rasp3BSensorData)
    {
        std::cerr << "fileName == " << fileName;
        if(this->sessionFile)
        {
            qDebug() << "<Debug> File already opened, close file and open new";
            this->closeSession(rasp0SensorData, rasp3BSensorData);
            this->sessionFile.reset(std::fopen(fileName.c_str(), "a+"));
        }
        else
        {
            this->sessionFile.reset(std::fopen(fileName.c_str(), "a+"));
        }

        if(this->sessionFile) {
            qDebug() << "<Debug> File loaded correctly";
        }
        else
        {
            qDebug() << "<Debug> File didn't open";
        }

        std::fseek (this->sessionFile.get(), 0, SEEK_END);
        const long int size = std::ftell(this->sessionFile.get());
        if (!size)
        {
            qDebug() << "<Debug> File is empty. Parser skipped";
            this->sessionFile.reset(nullptr);
            return -1;
        }
        std::fseek (this->sessionFile.get(), 0, SEEK_SET);
        constexpr int bufor = 100;
        char line[bufor];
        const char *delim{" \n"};
        char *words = nullptr;

        while(fgets(line, bufor, this->sessionFile.get()))
        {
            if(line != nullptr)
            {
                words = std::strtok(line, delim);
            }

            while(words != nullptr)
            {   qDebug() << "word=" << words;
                if(!std::strcmp(words, "rasp3b_temp"))
                {
                    words = std::strtok(nullptr, delim);
                    rasp3BSensorData.addTemperatureMeasurement(std::strtod(words, nullptr));
                    break;
                }
                else if(!std::strcmp(words, "rasp3b_hum"))
                {
                    words = std::strtok(nullptr, delim);
                    rasp3BSensorData.addHumidityMeasurement(std::strtod(words, nullptr));
                    break;
                }
                else if(!std::strcmp(words, "rasp3b_tvoc"))
                {
                    words = std::strtok(nullptr, delim);
                    rasp3BSensorData.addTvocMeasurement(std::strtod(words, nullptr));
                    break;
                }
                else if(!std::strcmp(words, "rasp3b_co2"))
                {
                    words = std::strtok(nullptr, delim);
                    rasp3BSensorData.addCo2Measurement(std::strtod(words, nullptr));
                    break;
                }
                else if(!std::strcmp(words, "rasp0_temp"))
                {
                    words = std::strtok(nullptr, delim);
                    rasp0SensorData.addTemperatureMeasurement(std::strtod(words, nullptr));
                    break;
                }
                else if(!std::strcmp(words, "rasp0_hum"))
                {
                    words = std::strtok(nullptr, delim);
                    rasp0SensorData.addHumidityMeasurement(std::strtod(words, nullptr));
                    break;
                }
                else if(!std::strcmp(words, "rasp0_tvoc"))
                {
                    words = std::strtok(nullptr, delim);
                    rasp0SensorData.addTvocMeasurement(std::strtod(words, nullptr));
                    break;
                }
                else if(!std::strcmp(words, "rasp0_co2"))
                {
                    words = std::strtok(nullptr, delim);
                    rasp0SensorData.addCo2Measurement(std::strtod(words, nullptr));
                    break;
                }
                break;
            }
        }
        this->sessionFile.reset(std::fopen(fileName.c_str(), "w")); // clean file
        return 0;
    }

    void closeSession(T1& rasp0SensorData, T2& rasp3BSensorData)
    {
        if(!this->sessionFile)
        {
            qDebug() << "<Debug> close session-> File didn't open, serialization skipped";
            return;
        }

        for(const auto value: rasp3BSensorData.getTemperatureMeasurements())
        {
            std::string rasp3bName {"rasp3b_temp "};
            rasp3bName.append(std::to_string(value) + "\n");
            std:fputs(rasp3bName.c_str(), this->sessionFile.get());
            std::fflush(this->sessionFile.get());
        }

        for(const auto value: rasp3BSensorData.getHumidityMeasurements())
        {
            std::string rasp3bName {"rasp3b_hum "};
            rasp3bName.append(std::to_string(value) + "\n");
            std::fputs(rasp3bName.c_str(), this->sessionFile.get());
            std::fflush(this->sessionFile.get());
        }

        for(const auto value: rasp3BSensorData.getTvocMeasurements())
        {
            std::string rasp3bName {"rasp3b_tvoc "};
            rasp3bName.append(std::to_string(value) + "\n");
            std::fputs(rasp3bName.c_str(), this->sessionFile.get());
            std::fflush(this->sessionFile.get());
        }

        for(const auto value: rasp3BSensorData.getCo2Measurements())
        {
            std::string rasp3bName {"rasp3b_co2 "};
            rasp3bName.append(std::to_string(value) + "\n");
            std::fputs(rasp3bName.c_str(), this->sessionFile.get());
            std::fflush(this->sessionFile.get());
        }

        for(const auto value: rasp0SensorData.getTemperatureMeasurements())
        {
            std::string rasp0Name {"rasp0_temp "};
            rasp0Name.append(std::to_string(value) + "\n");
            std::fputs(rasp0Name.c_str(), this->sessionFile.get());
            std::fflush(this->sessionFile.get());
        }

        for(const auto value: rasp0SensorData.getHumidityMeasurements())
        {
            std::string rasp0Name {"rasp0_hum "};
            rasp0Name.append(std::to_string(value) + "\n");
            std::fputs(rasp0Name.c_str(), this->sessionFile.get());
            std::fflush(this->sessionFile.get());
        }

        for(const auto value: rasp0SensorData.getTvocMeasurements())
        {
            std::string rasp0Name {"rasp0_tvoc "};
            rasp0Name.append(std::to_string(value) + "\n");
            std::fputs(rasp0Name.c_str(), this->sessionFile.get());
            std::fflush(this->sessionFile.get());
        }

        for(const auto value: rasp0SensorData.getCo2Measurements())
        {
            std::string rasp0Name {"rasp0_co2 "};
            rasp0Name.append(std::to_string(value) + "\n");
            std::fputs(rasp0Name.c_str(), this->sessionFile.get());
            std::fflush(this->sessionFile.get());
        }
        rasp0SensorData.clearData();
        rasp3BSensorData.clearData();

        qDebug() << "<Debug> Serialization complete";
    }

private:
    std::unique_ptr<std::FILE, decltype(&std::fclose)> sessionFile;
};
} // namespace tool

#endif // SERIALIZATOR_H
