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
#include <analyzer_table_cells_enum.h>

namespace tool {

template <class T1, class T2>
class Serializator
{
    std::unique_ptr<std::FILE, decltype(&std::fclose)> sessionFile;

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


    void saveCalculations(std::string filename, std::string fileNameLoaded, std::array<QTableWidgetItem*, 48> tableArray) {

        std::unique_ptr<std::FILE, decltype(&std::fclose)> fileWithResults(nullptr, &std::fclose);
        fileWithResults.reset(std::fopen(filename.c_str(), "w"));

        if(fileWithResults)
        {
            qDebug() << "<Debug> File created correctly";

            if(!fileNameLoaded.empty())
            {
                const std::string title {"#### SESSIONS ANALYZER RESULTS ####\n"
                                         "Compare to data from file: "};
                std::fputs(title.c_str(), fileWithResults.get());


                std::fputs(this->getFileName(fileNameLoaded).c_str(), fileWithResults.get());
                fileNameLoaded.append("\n\n");

                // Add measurements

                const std::string mictrocontroller1 = "\n\n#### Controller #1 Analysis ####\n";
                std::fputs(mictrocontroller1.c_str(), fileWithResults.get());

                std::string value {tableArray[tempMaxFileRasp3BItem]->text().toStdString()};
                std::string measurement;
                // temperature
                if(!value.empty()) {
                    measurement = "MAXIMUM TEMPERATURE FROM FILE: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[tempMaxAppRasp3BItem]->text().toStdString();
                if(!value.empty()) {
                    measurement = "MAXIMUM TEMPERATURE FROM APPLICATION: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[tempMinFileRasp3BItem]->text().toStdString();
                if(!value.empty()) {
                    measurement = "MINIMAL TEMPERATURE FROM FILE: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[tempMinAppRasp3BItem]->text().toStdString();
                if(!value.empty()) {
                    measurement = "MINIMAL TEMPERATURE FROM APPLICATION: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[tempAvgFileRasp3BItem]->text().toStdString();
                if(!value.empty()) {
                    measurement = "AVERAGE TEMPERATURE FROM FILE: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[tempAvgAppRasp3BItem]->text().toStdString();
                if(!value.empty()) {
                    measurement = "AVERAGE TEMPERATURE FROM APPLICATION: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                // HUMIDITY
                value = tableArray[humMaxFileRasp3BItem]->text().toStdString();
                if(!value.empty()) {
                    measurement = "MAXIMUM HUMIDITY FROM FILE: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[humMaxAppRasp3BItem]->text().toStdString();
                if(!value.empty()) {
                    measurement = "MAXIMUM HUMIDITY FROM APPLICATION: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[humMinFileRasp3BItem]->text().toStdString();
                if(!value.empty()) {
                    measurement = "MINIMAL HUMIDITY FROM FILE: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[humMinAppRasp3BItem]->text().toStdString();
                if(!value.empty()) {
                    measurement = "MINIMAL HUMIDITY FROM APPLICATION: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[humAvgFileRasp3BItem]->text().toStdString();
                if(!value.empty()) {
                    measurement = "AVERAGE HUMIDITY FROM FILE: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[humAvgAppRasp3BItem]->text().toStdString();
                if(!value.empty()) {
                    measurement = "AVERAGE HUMIDITY FROM APPLICATION: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                // TVOC
                value = tableArray[tvocMaxFileRasp3BItem]->text().toStdString();
                if(!value.empty()) {
                    measurement = "MAXIMUM TVOC FROM FILE: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[tvocMaxAppRasp3BItem]->text().toStdString();
                if(!value.empty()) {
                    measurement = "MAXIMUM TVOC FROM APPLICATION: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[tvocMinFileRasp3BItem]->text().toStdString();
                if(!value.empty()) {
                    measurement = "MINIMAL TVOC FROM FILE: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[tvocMinAppRasp3BItem]->text().toStdString();
                if(!value.empty()) {
                    measurement = "MINIMAL TVOC FROM APPLICATION: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[tvocAvgFileRasp3BItem]->text().toStdString();
                if(!value.empty()) {
                    measurement = "AVERAGE TVOC FROM FILE: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[tvocAvgAppRasp3BItem]->text().toStdString();
                if(!value.empty()) {
                    measurement = "AVERAGE TVOC FROM APPLICATION: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                // CO2
                value = tableArray[co2MaxFileRasp3BItem]->text().toStdString();
                if(!value.empty()) {
                    measurement = "MAXIMUM CO2 FROM FILE: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[co2MaxAppRasp3BItem]->text().toStdString();
                if(!value.empty()) {
                    measurement = "MAXIMUM CO2 FROM APPLICATION: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[co2MinFileRasp3BItem]->text().toStdString();
                if(!value.empty()) {
                    measurement = "MINIMAL CO2 FROM FILE: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[co2MinAppRasp3BItem]->text().toStdString();
                if(!value.empty()) {
                    measurement = "MINIMAL CO2 FROM APPLICATION: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[co2AvgFileRasp3BItem]->text().toStdString();
                if(!value.empty()) {
                    measurement = "AVERAGE CO2 FROM FILE: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[co2AvgAppRasp3BItem]->text().toStdString();
                if(!value.empty()) {
                    measurement = "AVERAGE CO2 FROM APPLICATION: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                const std::string mictrocontroller2 = "#### Controller #2 Analysis ####\n";
                std::fputs(mictrocontroller2.c_str(), fileWithResults.get());

                // temperature
                value = tableArray[tempMaxFileRasp0Item]->text().toStdString();
                if(!value.empty()) {
                    measurement = "MAXIMUM TEMPERATURE FROM FILE: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[tempMaxAppRasp0Item]->text().toStdString();
                if(!value.empty()) {
                    measurement = "MAXIMUM TEMPERATURE FROM APPLICATION: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[tempMinFileRasp0Item]->text().toStdString();
                if(!value.empty()) {
                    measurement = "MINIMAL TEMPERATURE FROM FILE: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[tempMinAppRasp0Item]->text().toStdString();
                if(!value.empty()) {
                    measurement = "MINIMAL TEMPERATURE FROM APPLICATION: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[tempAvgFileRasp0Item]->text().toStdString();
                if(!value.empty()) {
                    measurement = "AVERAGE TEMPERATURE FROM FILE: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[tempAvgAppRasp0Item]->text().toStdString();
                if(!value.empty()) {
                    measurement = "AVERAGE TEMPERATURE FROM APPLICATION: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                // HUMIDITY
                value = tableArray[humMaxFileRasp0Item]->text().toStdString();
                if(!value.empty()) {
                    measurement = "MAXIMUM HUMIDITY FROM FILE: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[humMaxAppRasp0Item]->text().toStdString();
                if(!value.empty()) {
                    measurement = "MAXIMUM HUMIDITY FROM APPLICATION: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[humMinFileRasp0Item]->text().toStdString();
                if(!value.empty()) {
                    measurement = "MINIMAL HUMIDITY FROM FILE: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[humMinAppRasp0Item]->text().toStdString();
                if(!value.empty()) {
                    measurement = "MINIMAL HUMIDITY FROM APPLICATION: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[humAvgFileRasp0Item]->text().toStdString();
                if(!value.empty()) {
                    measurement = "AVERAGE HUMIDITY FROM FILE: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[humAvgAppRasp0Item]->text().toStdString();
                if(!value.empty()) {
                    measurement = "AVERAGE HUMIDITY FROM APPLICATION: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                // TVOC
                value = tableArray[tvocMaxFileRasp0Item]->text().toStdString();
                if(!value.empty()) {
                    measurement = "MAXIMUM TVOC FROM FILE: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[tvocMaxAppRasp0Item]->text().toStdString();
                if(!value.empty()) {
                    measurement = "MAXIMUM TVOC FROM APPLICATION: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[tvocMinFileRasp0Item]->text().toStdString();
                if(!value.empty()) {
                    measurement = "MINIMAL TVOC FROM FILE: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[tvocMinAppRasp0Item]->text().toStdString();
                if(!value.empty()) {
                    measurement = "MINIMAL TVOC FROM APPLICATION: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[tvocAvgFileRasp0Item]->text().toStdString();
                if(!value.empty()) {
                    measurement = "AVERAGE TVOC FROM FILE: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }

                value = tableArray[tvocAvgAppRasp0Item]->text().toStdString();
                if(!value.empty()) {
                    measurement = "AVERAGE TVOC FROM APPLICATION: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                // CO2
                value = tableArray[co2MaxFileRasp0Item]->text().toStdString();
                if(!value.empty()) {
                    measurement = "MAXIMUM CO2 FROM FILE: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[co2MaxAppRasp0Item]->text().toStdString();
                if(!value.empty()) {
                    measurement = "MAXIMUM CO2 FROM APPLICATION: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[co2MinFileRasp0Item]->text().toStdString();
                if(!value.empty()) {
                    measurement = "MINIMAL CO2 FROM FILE: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[co2MinAppRasp0Item]->text().toStdString();
                if(!value.empty()) {
                    measurement = "MINIMAL CO2 FROM APPLICATION: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[co2AvgFileRasp0Item]->text().toStdString();
                if(!value.empty()) {
                    measurement = "AVERAGE CO2 FROM FILE: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                value = tableArray[co2AvgAppRasp0Item]->text().toStdString();
                if(!value.empty()) {
                    measurement = "AVERAGE CO2 FROM APPLICATION: ";
                    std::fputs(measurement.c_str(), fileWithResults.get());

                    value.append("\n\n");
                    std::fputs(value.c_str(), fileWithResults.get());
                }
                value.clear();

                std::fflush(fileWithResults.get());
            }

        }
        else
        {
            qDebug() << "<Debug> File didn't open";
        }
    }

    std::string getFileName(const std::string& s) {

       char sep = '/';

       size_t i = s.rfind(sep, s.length());
       if (i != std::string::npos) {
          return(s.substr(i+1, s.size()));
       }

       return("");
    }

};
} // namespace tool

#endif // SERIALIZATOR_H
