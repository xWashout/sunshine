#include <sessions_analyzer.h>
#include "./ui_sessions_analyzer.h"
#include <algorithm>

namespace tool {

SessionsAnalyzer::SessionsAnalyzer(sensor_data::Rasp0SensorData &rasp0SensorData,
                                   sensor_data::Rasp3BSensorData &rasp3BSensorData):
      rasp0SensorData(rasp0SensorData)
    , rasp3BSensorData(rasp3BSensorData)
    , ui(new Ui::Dialog())
    , chartRasp3BCo2("Application Data"), chartRasp3BTvoc("Application Data")
    , chartRasp3BHum("Application Data"), chartRasp3BTemp("Application Data")
    , chartRasp0Co2("Application Data"), chartRasp0Tvoc("Application Data")
    , chartRasp0Hum("Application Data"), chartRasp0Temp("Application Data")
{
    this->ui->setupUi(this);
    this->setWindowTitle("Sessions Analyzer");
    this->chartRasp3BTemp.initLineChart("Temperature (Celsius)");
    this->chartRasp3BHum.initLineChart("Humidity (%)");
    this->chartRasp3BTvoc.initLineChart("TVOC (ppb)");
    this->chartRasp3BCo2.initLineChart("Co2 (ppm)");

    this->chartRasp0Temp.initLineChart("Temperature (Celsius)");
    this->chartRasp0Hum.initLineChart("Humidity (%)");
    this->chartRasp0Tvoc.initLineChart("TVOC (ppb)");
    this->chartRasp0Co2.initLineChart("Co2 (ppm)");

    this->ui->gridLayout->addWidget(this->ui->loadDataButton, 0,0);
    this->ui->gridLayout->addWidget(this->ui->saveResultsButton, 0,1);

    this->ui->gridLayout->addWidget(this->chartRasp3BTemp.chartView, 1, 0);
    this->ui->gridLayout->addWidget(this->chartRasp3BHum.chartView, 1, 1);
    this->ui->gridLayout->addWidget(this->chartRasp3BTvoc.chartView, 1, 2);
    this->ui->gridLayout->addWidget(this->chartRasp3BCo2.chartView, 1, 3);

    this->ui->gridLayout->addWidget(this->chartRasp0Temp.chartView, 2, 0);
    this->ui->gridLayout->addWidget(this->chartRasp0Hum.chartView, 2, 1);
    this->ui->gridLayout->addWidget(this->chartRasp0Tvoc.chartView, 2, 2);
    this->ui->gridLayout->addWidget(this->chartRasp0Co2.chartView, 2, 3);

    this->ui->titleRasp0AnalizatorLabel->setStyleSheet("font-weight: bold; color: red; font-size:20px");
    this->ui->titleRasp3bAnalizatorLabel->setStyleSheet("font-weight: bold; color: red; font-size:20px");

    this->ui->tableMinRasp3b->setMinimumWidth(305);
    this->ui->tableMinRasp3b->setMinimumHeight(150);

    this->ui->tableMaxRasp3b->setMinimumWidth(305);
    this->ui->tableMaxRasp3b->setMinimumHeight(150);

    this->ui->tableAvgRasp3b->setMinimumWidth(305);
    this->ui->tableAvgRasp3b->setMinimumHeight(150);

    this->ui->tableMinRasp0->setMinimumWidth(305);
    this->ui->tableMinRasp0->setMinimumHeight(150);

    this->ui->tableMaxRasp0->setMinimumWidth(305);
    this->ui->tableMaxRasp0->setMinimumHeight(150);

    this->ui->tableAvgRasp0->setMinimumWidth(305);
    this->ui->tableAvgRasp0->setMinimumHeight(150);

    this->ui->titleRasp3bAnalizatorLabel->setMaximumHeight(20);
    this->ui->titleRasp0AnalizatorLabel->setMaximumHeight(20);

    this->ui->gridLayout->addWidget(this->ui->tableWidgetRasp3b, 1, 4);
    this->ui->gridLayout->addWidget(this->ui->tableWidgetRasp0, 2, 4);

    for(auto& ptr : tableItemArray)
    {
        ptr = new QTableWidgetItem();
    }
}

SessionsAnalyzer::~SessionsAnalyzer()
{
    this->serializator.closeSession(this->rasp0SensorDataFile, this->rasp3BSensorDataFile);
    delete this->ui;
}

void SessionsAnalyzer::reject()
{
    /* overrided QDialog function invoking after closing window */
    this->loadedFileName.clear();
    QDialog::reject();
}

void SessionsAnalyzer::showEvent(QShowEvent *ev)
{
    this->cleanAndInitializeData();
    QDialog::showEvent(ev);
}

void SessionsAnalyzer::cleanAndInitializeData()
{

    this->chartRasp0Temp.cleanCharts();
    this->chartRasp0Hum.cleanCharts();
    this->chartRasp0Tvoc.cleanCharts();
    this->chartRasp0Co2.cleanCharts();

    this->chartRasp3BTemp.cleanCharts();
    this->chartRasp3BHum.cleanCharts();
    this->chartRasp3BTvoc.cleanCharts();
    this->chartRasp3BCo2.cleanCharts();
    qDebug() << this->rasp0SensorDataBufor.getTemperatureMeasurements().size();

    this->rasp0SensorDataBufor.setTemperatureMeasurements(rasp0SensorData.getTemperatureMeasurements());
    this->rasp0SensorDataBufor.setHumidityMeasurements(rasp0SensorData.getHumidityMeasurements());
    this->rasp0SensorDataBufor.setTvocMeasurements(rasp0SensorData.getTvocMeasurements());
    this->rasp0SensorDataBufor.setCo2Measurements(rasp0SensorData.getCo2Measurements());

    this->rasp3BSensorDataBufor.setTemperatureMeasurements(rasp3BSensorData.getTemperatureMeasurements());
    this->rasp3BSensorDataBufor.setHumidityMeasurements(rasp3BSensorData.getHumidityMeasurements());
    this->rasp3BSensorDataBufor.setTvocMeasurements(rasp3BSensorData.getTvocMeasurements());
    this->rasp3BSensorDataBufor.setCo2Measurements(rasp3BSensorData.getCo2Measurements());

    this->chartRasp0Temp.drawNextDataset(this->rasp0SensorDataBufor.getTemperatureMeasurements());
    this->chartRasp0Hum.drawNextDataset(this->rasp0SensorDataBufor.getHumidityMeasurements());
    this->chartRasp0Tvoc.drawNextDataset(this->rasp0SensorDataBufor.getTvocMeasurements());
    this->chartRasp0Co2.drawNextDataset(this->rasp0SensorDataBufor.getCo2Measurements());

    this->chartRasp3BTemp.drawNextDataset(this->rasp3BSensorDataBufor.getTemperatureMeasurements());
    this->chartRasp3BHum.drawNextDataset(this->rasp3BSensorDataBufor.getHumidityMeasurements());
    this->chartRasp3BTvoc.drawNextDataset(this->rasp3BSensorDataBufor.getTvocMeasurements());
    this->chartRasp3BCo2.drawNextDataset(this->rasp3BSensorDataBufor.getCo2Measurements());

    this->setCalculationsFromApp();
}

void SessionsAnalyzer::setCalculationsFromFile()
{
    /* ============================== RASP0 ============================== */

    const auto[minTempFileRasp0, maxTempFileRasp0] = std::minmax_element(this->rasp0SensorDataFile.getTemperatureMeasurements().begin(),
                                                                         this->rasp0SensorDataFile.getTemperatureMeasurements().end());
    if(minTempFileRasp0 != this->rasp0SensorDataFile.getTemperatureMeasurements().end())
    {
        tableItemArray[MeasId::tempMinFileRasp0Item]->setText(QString::number(*minTempFileRasp0));
        this->ui->tableMinRasp0->setItem(0, 0, tableItemArray[MeasId::tempMinFileRasp0Item]);
    }
    if(maxTempFileRasp0 != this->rasp0SensorDataFile.getTemperatureMeasurements().end())
    {
        tableItemArray[MeasId::tempMaxFileRasp0Item]->setText(QString::number(*maxTempFileRasp0));
        this->ui->tableMaxRasp0->setItem(0, 0, tableItemArray[MeasId::tempMaxFileRasp0Item]);
    }

    const auto[minHumFileRasp0, maxHumFileRasp0] = std::minmax_element(this->rasp0SensorDataFile.getHumidityMeasurements().begin(),
                                                                         this->rasp0SensorDataFile.getHumidityMeasurements().end());
    if(minHumFileRasp0 != this->rasp0SensorDataFile.getHumidityMeasurements().end())
    {
        tableItemArray[MeasId::humMinFileRasp0Item]->setText(QString::number(*minHumFileRasp0));
        this->ui->tableMinRasp0->setItem(1, 0, tableItemArray[MeasId::humMinFileRasp0Item]);
    }
    if(maxHumFileRasp0 != this->rasp0SensorDataFile.getHumidityMeasurements().end())
    {
        tableItemArray[MeasId::humMaxFileRasp0Item]->setText(QString::number(*maxHumFileRasp0));
        this->ui->tableMaxRasp0->setItem(1, 0, tableItemArray[MeasId::humMaxFileRasp0Item]);
    }

    const auto[minTvocFileRasp0, maxTvocFileRasp0] = std::minmax_element(this->rasp0SensorDataFile.getTvocMeasurements().begin(),
                                                                         this->rasp0SensorDataFile.getTvocMeasurements().end());
    if(minTvocFileRasp0 != this->rasp0SensorDataFile.getTvocMeasurements().end())
    {
        tableItemArray[MeasId::tvocMinFileRasp0Item]->setText(QString::number(*minTvocFileRasp0));
        this->ui->tableMinRasp0->setItem(2, 0, tableItemArray[MeasId::tvocMinFileRasp0Item]);
    }
    if(maxTvocFileRasp0 != this->rasp0SensorDataFile.getTvocMeasurements().end())
    {
        tableItemArray[MeasId::tvocMaxFileRasp0Item]->setText(QString::number(*maxTvocFileRasp0));
        this->ui->tableMaxRasp0->setItem(2, 0, tableItemArray[MeasId::tvocMaxFileRasp0Item]);
    }

    const auto[minCo2FileRasp0, maxCo2FileRasp0] = std::minmax_element(this->rasp0SensorDataFile.getCo2Measurements().begin(),
                                                                         this->rasp0SensorDataFile.getCo2Measurements().end());
    if(minCo2FileRasp0 != this->rasp0SensorDataFile.getCo2Measurements().end())
    {
        tableItemArray[MeasId::co2MinFileRasp0Item]->setText(QString::number(*minCo2FileRasp0));
        this->ui->tableMinRasp0->setItem(3, 0, tableItemArray[MeasId::co2MinFileRasp0Item]);
    }
    if(maxCo2FileRasp0 != this->rasp0SensorDataFile.getCo2Measurements().end())
    {
        tableItemArray[MeasId::co2MaxFileRasp0Item]->setText(QString::number(*maxCo2FileRasp0));
        this->ui->tableMaxRasp0->setItem(3, 0, tableItemArray[MeasId::co2MaxFileRasp0Item]);
    }


    if(std::size_t size = this->rasp0SensorDataFile.getTemperatureMeasurements().size(); size != 0)
    {
        double avgTemp = 0.0;
        avgTemp = std::accumulate(this->rasp0SensorDataFile.getTemperatureMeasurements().begin(),
                                  this->rasp0SensorDataFile.getTemperatureMeasurements().end(),
                                  0.0) / size;
        tableItemArray[MeasId::tempAvgFileRasp0Item]->setText(QString::number(avgTemp));
        this->ui->tableAvgRasp0->setItem(0, 0, tableItemArray[MeasId::tempAvgFileRasp0Item]);
    }

    if(std::size_t size = this->rasp0SensorDataFile.getHumidityMeasurements().size(); size != 0)
    {
        double avgHum = 0.0;
        avgHum = std::accumulate(this->rasp0SensorDataFile.getHumidityMeasurements().begin(),
                                  this->rasp0SensorDataFile.getHumidityMeasurements().end(),
                                  0.0) / size;
        tableItemArray[MeasId::humAvgFileRasp0Item]->setText(QString::number(avgHum));
        this->ui->tableAvgRasp0->setItem(1, 0, tableItemArray[MeasId::humAvgFileRasp0Item]);
    }

    if(std::size_t size = this->rasp0SensorDataFile.getTvocMeasurements().size(); size != 0)
    {
        double avgTvoc = 0.0;
        avgTvoc = std::accumulate(this->rasp0SensorDataFile.getTvocMeasurements().begin(),
                                  this->rasp0SensorDataFile.getTvocMeasurements().end(),
                                  0.0) / size;
        tableItemArray[MeasId::tvocAvgFileRasp0Item]->setText(QString::number(avgTvoc));
        this->ui->tableAvgRasp0->setItem(2, 0, tableItemArray[MeasId::tvocAvgFileRasp0Item]);
    }

    if(std::size_t size = this->rasp0SensorDataFile.getCo2Measurements().size(); size != 0)
    {
        double avgCo2 = 0.0;
        avgCo2 = std::accumulate(this->rasp0SensorDataFile.getCo2Measurements().begin(),
                                  this->rasp0SensorDataFile.getCo2Measurements().end(),
                                  0.0) / size;
        tableItemArray[MeasId::co2AvgFileRasp0Item]->setText(QString::number(avgCo2));
        this->ui->tableAvgRasp0->setItem(3, 0, tableItemArray[MeasId::co2AvgFileRasp0Item]);
    }


    /* ============================== RASP3B ============================== */

    const auto[minTempFileRasp3B, maxTempFileRasp3B] = std::minmax_element(this->rasp3BSensorDataFile.getTemperatureMeasurements().begin(),
                                                                         this->rasp3BSensorDataFile.getTemperatureMeasurements().end());
    if(minTempFileRasp3B != this->rasp3BSensorDataFile.getTemperatureMeasurements().end())
    {
        tableItemArray[MeasId::tempMinFileRasp3BItem]->setText(QString::number(*minTempFileRasp3B));
        this->ui->tableMinRasp3b->setItem(0, 0, tableItemArray[MeasId::tempMinFileRasp3BItem]);
    }
    if(maxTempFileRasp3B != this->rasp3BSensorDataFile.getTemperatureMeasurements().end())
    {
        tableItemArray[MeasId::tempMaxFileRasp3BItem]->setText(QString::number(*maxTempFileRasp3B));
        this->ui->tableMaxRasp3b->setItem(0, 0, tableItemArray[MeasId::tempMaxFileRasp3BItem]);
    }

    const auto[minHumFileRasp3B, maxHumFileRasp3B] = std::minmax_element(this->rasp3BSensorDataFile.getHumidityMeasurements().begin(),
                                                                         this->rasp3BSensorDataFile.getHumidityMeasurements().end());
    if(minHumFileRasp3B != this->rasp3BSensorDataFile.getHumidityMeasurements().end())
    {
        tableItemArray[MeasId::humMinFileRasp3BItem]->setText(QString::number(*minHumFileRasp3B));
        this->ui->tableMinRasp3b->setItem(1, 0, tableItemArray[MeasId::humMinFileRasp3BItem]);
    }
    if(maxHumFileRasp3B != this->rasp3BSensorDataFile.getHumidityMeasurements().end())
    {
        tableItemArray[MeasId::humMaxFileRasp3BItem]->setText(QString::number(*maxHumFileRasp3B));
        this->ui->tableMaxRasp3b->setItem(1, 0, tableItemArray[MeasId::humMaxFileRasp3BItem]);
    }

    const auto[minTvocFileRasp3B, maxTvocFileRasp3B] = std::minmax_element(this->rasp3BSensorDataFile.getTvocMeasurements().begin(),
                                                                         this->rasp3BSensorDataFile.getTvocMeasurements().end());
    if(minTvocFileRasp3B != this->rasp3BSensorDataFile.getTvocMeasurements().end())
    {
        tableItemArray[MeasId::tvocMinFileRasp3BItem]->setText(QString::number(*minTvocFileRasp3B));
        this->ui->tableMinRasp3b->setItem(2, 0, tableItemArray[MeasId::tvocMinFileRasp3BItem]);
    }
    if(maxTvocFileRasp3B != this->rasp3BSensorDataFile.getTvocMeasurements().end())
    {
        tableItemArray[MeasId::tvocMaxFileRasp3BItem]->setText(QString::number(*maxTvocFileRasp3B));
        this->ui->tableMaxRasp3b->setItem(2, 0, tableItemArray[MeasId::tvocMaxFileRasp3BItem]);
    }

    const auto[minCo2FileRasp3B, maxCo2FileRasp3B] = std::minmax_element(this->rasp3BSensorDataFile.getCo2Measurements().begin(),
                                                                         this->rasp3BSensorDataFile.getCo2Measurements().end());
    if(minCo2FileRasp3B != this->rasp3BSensorDataFile.getCo2Measurements().end())
    {
        tableItemArray[MeasId::co2MinFileRasp3BItem]->setText(QString::number(*minCo2FileRasp3B));
        this->ui->tableMinRasp3b->setItem(3, 0, tableItemArray[MeasId::co2MinFileRasp3BItem]);
    }
    if(maxCo2FileRasp3B != this->rasp3BSensorDataFile.getCo2Measurements().end())
    {
        tableItemArray[MeasId::co2MaxFileRasp3BItem]->setText(QString::number(*maxCo2FileRasp3B));
        this->ui->tableMaxRasp3b->setItem(3, 0, tableItemArray[MeasId::co2MaxFileRasp3BItem]);
    }


    if(std::size_t size = this->rasp3BSensorDataFile.getTemperatureMeasurements().size(); size != 0)
    {
        double avgTemp = 0.0;
        avgTemp = std::accumulate(this->rasp3BSensorDataFile.getTemperatureMeasurements().begin(),
                                  this->rasp3BSensorDataFile.getTemperatureMeasurements().end(),
                                  0.0) / size;
        tableItemArray[MeasId::tempAvgFileRasp3BItem]->setText(QString::number(avgTemp));
        this->ui->tableAvgRasp3b->setItem(0, 0, tableItemArray[MeasId::tempAvgFileRasp3BItem]);
    }

    if(std::size_t size = this->rasp3BSensorDataFile.getHumidityMeasurements().size(); size != 0)
    {
        double avgHum = 0.0;
        avgHum = std::accumulate(this->rasp3BSensorDataFile.getHumidityMeasurements().begin(),
                                  this->rasp3BSensorDataFile.getHumidityMeasurements().end(),
                                  0.0) / size;
        tableItemArray[MeasId::humAvgFileRasp3BItem]->setText(QString::number(avgHum));
        this->ui->tableAvgRasp3b->setItem(1, 0, tableItemArray[MeasId::humAvgFileRasp3BItem]);
    }

    if(std::size_t size = this->rasp3BSensorDataFile.getTvocMeasurements().size(); size != 0)
    {
        double avgTvoc = 0.0;
        avgTvoc = std::accumulate(this->rasp3BSensorDataFile.getTvocMeasurements().begin(),
                                  this->rasp3BSensorDataFile.getTvocMeasurements().end(),
                                  0.0) / size;
        tableItemArray[MeasId::tvocAvgFileRasp3BItem]->setText(QString::number(avgTvoc));
        this->ui->tableAvgRasp3b->setItem(2, 0, tableItemArray[MeasId::tvocAvgFileRasp3BItem]);
    }

    if(std::size_t size = this->rasp3BSensorDataFile.getCo2Measurements().size(); size != 0)
    {
        double avgCo2 = 0.0;
        avgCo2 = std::accumulate(this->rasp3BSensorDataFile.getCo2Measurements().begin(),
                                  this->rasp3BSensorDataFile.getCo2Measurements().end(),
                                  0.0) / size;
        tableItemArray[MeasId::co2AvgFileRasp3BItem]->setText(QString::number(avgCo2));
        this->ui->tableAvgRasp3b->setItem(3, 0, tableItemArray[MeasId::co2AvgFileRasp3BItem]);
    }
}

void SessionsAnalyzer::setCalculationsFromApp()
{
    /* ============================== RASP0 ============================== */

    const auto[minTempAppRasp0, maxTempAppRasp0] = std::minmax_element(this->rasp0SensorDataBufor.getTemperatureMeasurements().begin(),
                                                                         this->rasp0SensorDataBufor.getTemperatureMeasurements().end());
    if(minTempAppRasp0 != this->rasp0SensorDataBufor.getTemperatureMeasurements().end())
    {
        tableItemArray[MeasId::tempMinAppRasp0Item]->setText(QString::number(*minTempAppRasp0));
        this->ui->tableMinRasp0->setItem(0, 1, tableItemArray[MeasId::tempMinAppRasp0Item]);
    }
    if(maxTempAppRasp0 != this->rasp0SensorDataBufor.getTemperatureMeasurements().end())
    {
        tableItemArray[MeasId::tempMaxAppRasp0Item]->setText(QString::number(*maxTempAppRasp0));
        this->ui->tableMaxRasp0->setItem(0, 1, tableItemArray[MeasId::tempMaxAppRasp0Item]);
    }

    const auto[minHumAppRasp0, maxHumAppRasp0] = std::minmax_element(this->rasp0SensorDataBufor.getHumidityMeasurements().begin(),
                                                                         this->rasp0SensorDataBufor.getHumidityMeasurements().end());
    if(minHumAppRasp0 != this->rasp0SensorDataBufor.getHumidityMeasurements().end())
    {
        tableItemArray[MeasId::humMinAppRasp0Item]->setText(QString::number(*minHumAppRasp0));
        this->ui->tableMinRasp0->setItem(1, 1, tableItemArray[MeasId::humMinAppRasp0Item]);
    }
    if(maxHumAppRasp0 != this->rasp0SensorDataBufor.getHumidityMeasurements().end())
    {
        tableItemArray[MeasId::humMaxAppRasp0Item]->setText(QString::number(*maxHumAppRasp0));
        this->ui->tableMaxRasp0->setItem(1, 1, tableItemArray[MeasId::humMaxAppRasp0Item]);
    }

    const auto[minTvocAppRasp0, maxTvocAppRasp0] = std::minmax_element(this->rasp0SensorDataBufor.getTvocMeasurements().begin(),
                                                                         this->rasp0SensorDataBufor.getTvocMeasurements().end());
    if(minTvocAppRasp0 != this->rasp0SensorDataBufor.getTvocMeasurements().end())
    {
        tableItemArray[MeasId::tvocMinAppRasp0Item]->setText(QString::number(*minTvocAppRasp0));
        this->ui->tableMinRasp0->setItem(2, 1, tableItemArray[MeasId::tvocMinAppRasp0Item]);
    }
    if(maxTvocAppRasp0 != this->rasp0SensorDataBufor.getTvocMeasurements().end())
    {
        tableItemArray[MeasId::tvocMaxAppRasp0Item]->setText(QString::number(*maxTvocAppRasp0));
        this->ui->tableMaxRasp0->setItem(2, 1, tableItemArray[MeasId::tvocMaxAppRasp0Item]);
    }

    const auto[minCo2AppRasp0, maxCo2AppRasp0] = std::minmax_element(this->rasp0SensorDataBufor.getCo2Measurements().begin(),
                                                                         this->rasp0SensorDataBufor.getCo2Measurements().end());
    if(minCo2AppRasp0 != this->rasp0SensorDataBufor.getCo2Measurements().end())
    {
        tableItemArray[MeasId::co2MinAppRasp0Item]->setText(QString::number(*minCo2AppRasp0));
        this->ui->tableMinRasp0->setItem(3, 1, tableItemArray[MeasId::co2MinAppRasp0Item]);
    }
    if(maxCo2AppRasp0 != this->rasp0SensorDataBufor.getCo2Measurements().end())
    {
        tableItemArray[MeasId::co2MaxAppRasp0Item]->setText(QString::number(*maxCo2AppRasp0));
        this->ui->tableMaxRasp0->setItem(3, 1, tableItemArray[MeasId::co2MaxAppRasp0Item]);
    }


    if(std::size_t size = this->rasp0SensorDataBufor.getTemperatureMeasurements().size(); size != 0)
    {
        double avgTemp = 0.0;
        avgTemp = std::accumulate(this->rasp0SensorDataBufor.getTemperatureMeasurements().begin(),
                                  this->rasp0SensorDataBufor.getTemperatureMeasurements().end(),
                                  0.0) / size;
        tableItemArray[MeasId::tempAvgAppRasp0Item]->setText(QString::number(avgTemp));
        this->ui->tableAvgRasp0->setItem(0, 1, tableItemArray[MeasId::tempAvgAppRasp0Item]);
    }

    if(std::size_t size = this->rasp0SensorDataBufor.getHumidityMeasurements().size(); size != 0)
    {
        double avgHum = 0.0;
        avgHum = std::accumulate(this->rasp0SensorDataBufor.getHumidityMeasurements().begin(),
                                  this->rasp0SensorDataBufor.getHumidityMeasurements().end(),
                                  0.0) / size;
        tableItemArray[MeasId::humAvgAppRasp0Item]->setText(QString::number(avgHum));
        this->ui->tableAvgRasp0->setItem(1, 1, tableItemArray[MeasId::humAvgAppRasp0Item]);
    }

    if(std::size_t size = this->rasp0SensorDataBufor.getTvocMeasurements().size(); size != 0)
    {
        double avgTvoc = 0.0;
        avgTvoc = std::accumulate(this->rasp0SensorDataBufor.getTvocMeasurements().begin(),
                                  this->rasp0SensorDataBufor.getTvocMeasurements().end(),
                                  0.0) / size;
        tableItemArray[MeasId::tvocAvgAppRasp0Item]->setText(QString::number(avgTvoc));
        this->ui->tableAvgRasp0->setItem(2, 1, tableItemArray[MeasId::tvocAvgAppRasp0Item]);
    }

    if(std::size_t size = this->rasp0SensorDataBufor.getCo2Measurements().size(); size != 0)
    {
        double avgCo2 = 0.0;
        avgCo2 = std::accumulate(this->rasp0SensorDataBufor.getCo2Measurements().begin(),
                                  this->rasp0SensorDataBufor.getCo2Measurements().end(),
                                  0.0) / size;
        tableItemArray[MeasId::co2AvgAppRasp0Item]->setText(QString::number(avgCo2));
        this->ui->tableAvgRasp0->setItem(3, 1, tableItemArray[MeasId::co2AvgAppRasp0Item]);
    }


    /* ============================== RASP3B ============================== */

    const auto[minTempAppRasp3B, maxTempAppRasp3B] = std::minmax_element(this->rasp3BSensorDataBufor.getTemperatureMeasurements().begin(),
                                                                         this->rasp3BSensorDataBufor.getTemperatureMeasurements().end());
    if(minTempAppRasp3B != this->rasp3BSensorDataBufor.getTemperatureMeasurements().end())
    {
        tableItemArray[MeasId::tempMinAppRasp3BItem]->setText(QString::number(*minTempAppRasp3B));
        this->ui->tableMinRasp3b->setItem(0, 1, tableItemArray[MeasId::tempMinAppRasp3BItem]);
    }
    if(maxTempAppRasp3B != this->rasp3BSensorDataBufor.getTemperatureMeasurements().end())
    {
        tableItemArray[MeasId::tempMaxAppRasp3BItem]->setText(QString::number(*maxTempAppRasp3B));
        this->ui->tableMaxRasp3b->setItem(0, 1, tableItemArray[MeasId::tempMaxAppRasp3BItem]);
    }

    const auto[minHumAppRasp3B, maxHumAppRasp3B] = std::minmax_element(this->rasp3BSensorDataBufor.getHumidityMeasurements().begin(),
                                                                         this->rasp3BSensorDataBufor.getHumidityMeasurements().end());
    if(minHumAppRasp3B != this->rasp3BSensorDataBufor.getHumidityMeasurements().end())
    {
        tableItemArray[MeasId::humMinAppRasp3BItem]->setText(QString::number(*minHumAppRasp3B));
        this->ui->tableMinRasp3b->setItem(1, 1, tableItemArray[MeasId::humMinAppRasp3BItem]);
    }
    if(maxHumAppRasp3B != this->rasp3BSensorDataBufor.getHumidityMeasurements().end())
    {
        tableItemArray[MeasId::humMaxAppRasp3BItem]->setText(QString::number(*maxHumAppRasp3B));
        this->ui->tableMaxRasp3b->setItem(1, 1, tableItemArray[MeasId::humMaxAppRasp3BItem]);
    }

    const auto[minTvocAppRasp3B, maxTvocAppRasp3B] = std::minmax_element(this->rasp3BSensorDataBufor.getTvocMeasurements().begin(),
                                                                         this->rasp3BSensorDataBufor.getTvocMeasurements().end());
    if(minTvocAppRasp3B != this->rasp3BSensorDataBufor.getTvocMeasurements().end())
    {
        tableItemArray[MeasId::tvocMinAppRasp3BItem]->setText(QString::number(*minTvocAppRasp3B));
        this->ui->tableMinRasp3b->setItem(2, 1, tableItemArray[MeasId::tvocMinAppRasp3BItem]);
    }
    if(maxTvocAppRasp3B != this->rasp3BSensorDataBufor.getTvocMeasurements().end())
    {
        tableItemArray[MeasId::tvocMaxAppRasp3BItem]->setText(QString::number(*maxTvocAppRasp3B));
        this->ui->tableMaxRasp3b->setItem(2, 1, tableItemArray[MeasId::tvocMaxAppRasp3BItem]);
    }

    const auto[minCo2AppRasp3B, maxCo2AppRasp3B] = std::minmax_element(this->rasp3BSensorDataBufor.getCo2Measurements().begin(),
                                                                         this->rasp3BSensorDataBufor.getCo2Measurements().end());
    if(minCo2AppRasp3B != this->rasp3BSensorDataBufor.getCo2Measurements().end())
    {
        tableItemArray[MeasId::co2MinAppRasp3BItem]->setText(QString::number(*minCo2AppRasp3B));
        this->ui->tableMinRasp3b->setItem(3, 1, tableItemArray[MeasId::co2MinAppRasp3BItem]);
    }
    if(maxCo2AppRasp3B != this->rasp3BSensorDataBufor.getCo2Measurements().end())
    {
        tableItemArray[MeasId::co2MaxAppRasp3BItem]->setText(QString::number(*maxCo2AppRasp3B));
        this->ui->tableMaxRasp3b->setItem(3, 1, tableItemArray[MeasId::co2MaxAppRasp3BItem]);
    }


    if(std::size_t size = this->rasp3BSensorDataBufor.getTemperatureMeasurements().size(); size != 0)
    {
        double avgTemp = 0.0;
        avgTemp = std::accumulate(this->rasp3BSensorDataBufor.getTemperatureMeasurements().begin(),
                                  this->rasp3BSensorDataBufor.getTemperatureMeasurements().end(),
                                  0.0) / size;
        tableItemArray[MeasId::tempAvgAppRasp3BItem]->setText(QString::number(avgTemp));
        this->ui->tableAvgRasp3b->setItem(0, 1, tableItemArray[MeasId::tempAvgAppRasp3BItem]);
    }

    if(std::size_t size = this->rasp3BSensorDataBufor.getHumidityMeasurements().size(); size != 0)
    {
        double avgHum = 0.0;
        avgHum = std::accumulate(this->rasp3BSensorDataBufor.getHumidityMeasurements().begin(),
                                 this->rasp3BSensorDataBufor.getHumidityMeasurements().end(),
                                 0.0) / size;
        tableItemArray[MeasId::humAvgAppRasp3BItem]->setText(QString::number(avgHum));
        this->ui->tableAvgRasp3b->setItem(1, 1, tableItemArray[MeasId::humAvgAppRasp3BItem]);
    }

    if(std::size_t size = this->rasp3BSensorDataBufor.getTvocMeasurements().size(); size != 0)
    {
        double avgTvoc = 0.0;
        avgTvoc = std::accumulate(this->rasp3BSensorDataBufor.getTvocMeasurements().begin(),
                                  this->rasp3BSensorDataBufor.getTvocMeasurements().end(),
                                  0.0) / size;
        tableItemArray[MeasId::tvocAvgAppRasp3BItem]->setText(QString::number(avgTvoc));
        this->ui->tableAvgRasp3b->setItem(2, 1, tableItemArray[MeasId::tvocAvgAppRasp3BItem]);
    }

    if(std::size_t size = this->rasp3BSensorDataBufor.getCo2Measurements().size(); size != 0)
    {
        double avgCo2 = 0.0;
        avgCo2 = std::accumulate(this->rasp3BSensorDataBufor.getCo2Measurements().begin(),
                                 this->rasp3BSensorDataBufor.getCo2Measurements().end(),
                                 0.0) / size;
        tableItemArray[MeasId::co2AvgAppRasp3BItem]->setText(QString::number(avgCo2));
        this->ui->tableAvgRasp3b->setItem(3, 1, tableItemArray[MeasId::co2AvgAppRasp3BItem]);
    }
}

void tool::SessionsAnalyzer::on_loadDataButton_clicked()
{
    this->loadedFileName = QFileDialog::getOpenFileName(this,
        tr("Open Session"), "/home/washout/repos/sunshine/serialized_sessions");
    qDebug() << "<Debug> (Analyzer) Action save session application" << this->loadedFileName;

    if(this->loadedFileName != "")
    {
        this->cleanAndInitializeData();

        if(this->serializator.loadSession(this->loadedFileName.toStdString(),
                                          this->rasp0SensorDataFile, this->rasp3BSensorDataFile) == -1)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Error");
            msgBox.setText("Empty file selected");
            msgBox.exec();

            this->loadedFileName.clear();
            return;
        }
        this->chartRasp0Temp.readSerializedData(this->rasp0SensorDataFile.getTemperatureMeasurements());
        this->chartRasp0Hum.readSerializedData(this->rasp0SensorDataFile.getHumidityMeasurements());
        this->chartRasp0Tvoc.readSerializedData(this->rasp0SensorDataFile.getTvocMeasurements());
        this->chartRasp0Co2.readSerializedData(this->rasp0SensorDataFile.getCo2Measurements());

        this->chartRasp3BTemp.readSerializedData(this->rasp3BSensorDataFile.getTemperatureMeasurements());
        this->chartRasp3BHum.readSerializedData(this->rasp3BSensorDataFile.getHumidityMeasurements());
        this->chartRasp3BTvoc.readSerializedData(this->rasp3BSensorDataFile.getTvocMeasurements());
        this->chartRasp3BCo2.readSerializedData(this->rasp3BSensorDataFile.getCo2Measurements());
    }
    else
    {
        qDebug() <<"<Debug> (Analyzer) No file selected";
        return;
    }
    this->setCalculationsFromFile();

}

void tool::SessionsAnalyzer::on_saveResultsButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Session"), "/home/washout/repos/sunshine/sessions_analyzer_results");

    if(fileName != "")
    {
        this->serializator.saveCalculations(fileName.toStdString(), this->loadedFileName.toStdString(), this->tableItemArray);
    }
    else
    {
        qDebug() << "<Debug> (Sessions Analyzer) Results not created.";
        return;
    }
}



} // tool
