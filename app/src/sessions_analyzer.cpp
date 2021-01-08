#include <sessions_analyzer.h>
#include "./ui_sessions_analyzer.h"
namespace tool {

SessionsAnalyzer::SessionsAnalyzer(sensor_data::Rasp0SensorData &rasp0SendorData,
                                   sensor_data::Rasp3BSensorData &rasp3BSendorData):
    rasp0SendorData(rasp0SendorData), rasp3BSendorData(rasp3BSendorData), ui(new Ui::Dialog())
{
    this->ui->setupUi(this);
    this->setWindowTitle("Sessions Analyzer");
    this->chartRasp3BTemp.initLineChart("Temperature (Celsius)");
    this->chartRasp3BHum.initLineChart("Humidity (%)");
    this->chartRasp3BTvoc.initLineChart("TVOC");
    this->chartRasp3BCo2.initLineChart("Co2");

    this->chartRasp0Temp.initLineChart("Temperature (Celsius)");
    this->chartRasp0Hum.initLineChart("Humidity (%)");
    this->chartRasp0Tvoc.initLineChart("TVOC");
    this->chartRasp0Co2.initLineChart("Co2");

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
}

SessionsAnalyzer::~SessionsAnalyzer()
{
    this->serializator.closeSession(this->rasp0SendorData, this->rasp3BSendorData);
    delete this->ui;
}

void tool::SessionsAnalyzer::on_loadDataButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Session"), "/home/washout/repos/sunshine/serialized_sessions");
    qDebug() << "<Debug> Action save session application" << fileName;

    if(fileName != "")
    {
        this->rasp0SendorDataFile.clearData();
        this->rasp3BSendorDataFile.clearData();

        this->serializator.loadSession(fileName.toStdString(),
                                       this->rasp0SendorDataFile,
                                       this->rasp3BSendorDataFile);

        this->chartRasp0Temp.readSerializedData(this->rasp0SendorDataFile.getTemperatureMeasurements());
        this->chartRasp0Hum.readSerializedData(this->rasp0SendorDataFile.getHumidityMeasurements());
        this->chartRasp0Tvoc.readSerializedData(this->rasp0SendorDataFile.getTvocMeasurements());
        this->chartRasp0Co2.readSerializedData(this->rasp0SendorDataFile.getCo2Measurements());

        this->chartRasp3BTemp.readSerializedData(this->rasp3BSendorDataFile.getTemperatureMeasurements());
        this->chartRasp3BHum.readSerializedData(this->rasp3BSendorDataFile.getHumidityMeasurements());
        this->chartRasp3BTvoc.readSerializedData(this->rasp3BSendorDataFile.getTvocMeasurements());
        this->chartRasp3BCo2.readSerializedData(this->rasp3BSendorDataFile.getCo2Measurements());
    }
    else
    {
        qDebug() <<"<Debug> No file selected";
        return;
    }
    this->chartRasp0Temp.drawNextDataset(this->rasp0SendorData.getTemperatureMeasurements());
    this->chartRasp0Hum.drawNextDataset(this->rasp0SendorData.getHumidityMeasurements());
    this->chartRasp0Tvoc.drawNextDataset(this->rasp0SendorData.getTvocMeasurements());
    this->chartRasp0Co2.drawNextDataset(this->rasp0SendorData.getCo2Measurements());

    this->chartRasp3BTemp.drawNextDataset(this->rasp3BSendorData.getTemperatureMeasurements());
    this->chartRasp3BHum.drawNextDataset(this->rasp3BSendorData.getHumidityMeasurements());
    this->chartRasp3BTvoc.drawNextDataset(this->rasp3BSendorData.getTvocMeasurements());
    this->chartRasp3BCo2.drawNextDataset(this->rasp3BSendorData.getCo2Measurements());
}

void tool::SessionsAnalyzer::on_saveResultsButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Session"), "/home/washout/repos/sunshine/serialized_sessions");

    qDebug() << "<Debug> Action load session application =" << fileName;
    if(fileName != "")
    {
    }
    else
    {
        qDebug() << "<Debug> Session isn't created";
        return;
    }
}

} // tool
