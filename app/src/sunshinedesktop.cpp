#include "sunshinedesktop.h"
#include "./ui_sunshinedesktop.h"
#include <QDebug>
#include <clocale>

SunshineDesktop::SunshineDesktop(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SunshineDesktop)
    , mqttReceiverThread(&mqtt_wrapper::MqttWrapper::Receiver,
                         std::ref(mqttWrapper),
                         std::ref(*this))
    , sessionAnalyzer(rasp0SensorData, rasp3BSensorData)
    , chartRasp3BCo2("Sensor CCS811"), chartRasp3BTvoc("Sensor CCS811"), chartRasp3BHum("Sensor HDC2010"), chartRasp3BTemp("Sensor HDC2010")
    , chartRasp0Co2("Sensor CCS811"), chartRasp0Tvoc("Sensor CCS811"), chartRasp0Hum("Sensor BME280"), chartRasp0Temp("Sensor BME280")
{
    std::setlocale(LC_NUMERIC, "C"); // dot instead of comma in coding floating numbers

    if(this->mqttReceiverThread.joinable()) {
        this->mqttReceiverThread.detach();
    }

    this->ui->setupUi(this);
    this->ui->titleRasp0Label->setStyleSheet("font-weight: bold; color: red; font-size:20px");
    this->ui->titleRasp3bLabel->setStyleSheet("font-weight: bold; color: red; font-size:20px");

    this->chartRasp3BTemp.initLineChart("Temperature (Celsius)");
    this->chartRasp3BHum.initLineChart("Humidity (%)");
    this->chartRasp3BTvoc.initLineChart("TVOC (ppb)");
    this->chartRasp3BCo2.initLineChart("Co2 (ppm)");

    this->chartRasp0Temp.initLineChart("Temperature (Celsius)");
    this->chartRasp0Hum.initLineChart("Humidity (%)");
    this->chartRasp0Tvoc.initLineChart("TVOC (ppb)");
    this->chartRasp0Co2.initLineChart("Co2 (ppm)");

    this->chartRasp3BTemp.lineSeries->setName("Sensor HDC2010");
    this->chartRasp3BHum.lineSeries->setName("Sensor HDC2010");
    this->chartRasp3BTvoc.lineSeries->setName("Sensor CCS811");
    this->chartRasp3BCo2.lineSeries->setName("Sensor CCS811");

    this->chartRasp0Temp.lineSeries->setName("Sensor BME280");
    this->chartRasp0Hum.lineSeries->setName("Sensor BME280");
    this->chartRasp0Tvoc.lineSeries->setName("Sensor CCS811");
    this->chartRasp0Co2.lineSeries->setName("Sensor CCS811");

    this->chartRasp3BTemp.initAndDefaultAxes();
    this->chartRasp3BHum.initAndDefaultAxes();
    this->chartRasp3BTvoc.initAndDefaultAxes();
    this->chartRasp3BCo2.initAndDefaultAxes();

    this->chartRasp0Temp.initAndDefaultAxes();
    this->chartRasp0Hum.initAndDefaultAxes();
    this->chartRasp0Tvoc.initAndDefaultAxes();
    this->chartRasp0Co2.initAndDefaultAxes();

    this->chartRasp3BTemp.chart->createDefaultAxes();
    this->chartRasp3BHum.chart->createDefaultAxes();
    this->chartRasp3BTvoc.chart->createDefaultAxes();
    this->chartRasp3BCo2.chart->createDefaultAxes();

    this->chartRasp0Temp.chart->createDefaultAxes();
    this->chartRasp0Hum.chart->createDefaultAxes();
    this->chartRasp0Tvoc.chart->createDefaultAxes();
    this->chartRasp0Co2.chart->createDefaultAxes();

    this->layout = new QGridLayout();
    this->menuBar = new QMenuBar(nullptr);
    this->menu = new QMenu();
    this->newSessionAction = new QAction("&New Session");
    this->loadSessionAction = new QAction("&Load Session");
    this->measAnalyzerAction = new QAction("&Open Data Analyzer");

    connect(this->newSessionAction, &QAction::triggered, this, &SunshineDesktop::newSessionAction_clicked);
    connect(this->loadSessionAction, &QAction::triggered, this, &SunshineDesktop::loadSessionAction_clicked);
    connect(this->measAnalyzerAction, &QAction::triggered, this, &SunshineDesktop::measAnalyzerAction_clicked);

    this->menu = this->menuBar->addMenu("MENU");
    this->menu->addAction(this->newSessionAction);
    this->menu->addAction(this->loadSessionAction);
    this->menu->addAction(this->measAnalyzerAction);

    this->setMenuBar(this->menuBar);

    this->layout->addWidget(this->ui->startStopWidget, 0,0);

    this->layout->addWidget(this->chartRasp3BTemp.chartView, 1, 0);
    this->layout->addWidget(this->chartRasp3BHum.chartView, 1, 1);
    this->layout->addWidget(this->chartRasp3BTvoc.chartView, 1, 2);
    this->layout->addWidget(this->chartRasp3BCo2.chartView, 1, 3);

    this->layout->addWidget(this->chartRasp0Temp.chartView, 2, 0);
    this->layout->addWidget(this->chartRasp0Hum.chartView, 2, 1);
    this->layout->addWidget(this->chartRasp0Tvoc.chartView, 2, 2);
    this->layout->addWidget(this->chartRasp0Co2.chartView, 2, 3);

    this->layout->addWidget(this->ui->rasp3bDataWidget, 1, 4);
    this->layout->addWidget(this->ui->rasp0DataWidget, 2, 4);

    this->ui->centralwidget->setLayout(layout);
    this->ui->rasp0DataWidget->setEnabled(false);
    this->ui->rasp3bDataWidget->setEnabled(false);
    this->ui->stopCaptureDataButton->setEnabled(false);
    this->ui->startCaptureDataButton->setEnabled(false);

    this->mqttWrapper.Publisher("empty", "microcontrollerInit");
}

SunshineDesktop::~SunshineDesktop()
{
    this->serializator.closeSession(rasp0SensorData, rasp3BSensorData);
    delete this->ui;
}

void SunshineDesktop::clenupMainWindow()
{
    this->chartRasp0Temp.cleanCharts();
    this->chartRasp0Hum.cleanCharts();
    this->chartRasp0Tvoc.cleanCharts();
    this->chartRasp0Co2.cleanCharts();

    this->chartRasp3BTemp.cleanCharts();
    this->chartRasp3BHum.cleanCharts();
    this->chartRasp3BTvoc.cleanCharts();
    this->chartRasp3BCo2.cleanCharts();

    this->ui->tempRasp0MeasLabel->setText("0");
    this->ui->humRasp0MeasLabel->setText("0");
    this->ui->tvocRasp0MeasLabel->setText("0");
    this->ui->co2Rasp0MeasLabel->setText("0");

    this->ui->tempRasp3BMeasLabel->setText("0");
    this->ui->humRasp3BMeasLabel->setText("0");
    this->ui->tvocRasp3BMeasLabel->setText("0");
    this->ui->co2Rasp3BMeasLabel->setText("0");

    this->mqttWrapper.Publisher("empty", "microcontrollerInit");

    this->chartRasp3BTemp.initAndDefaultAxes();
    this->chartRasp3BHum.initAndDefaultAxes();
    this->chartRasp3BTvoc.initAndDefaultAxes();
    this->chartRasp3BCo2.initAndDefaultAxes();

    this->chartRasp0Temp.initAndDefaultAxes();
    this->chartRasp0Hum.initAndDefaultAxes();
    this->chartRasp0Tvoc.initAndDefaultAxes();
    this->chartRasp0Co2.initAndDefaultAxes();

    this->chartRasp3BTemp.chart->createDefaultAxes();
    this->chartRasp3BHum.chart->createDefaultAxes();
    this->chartRasp3BTvoc.chart->createDefaultAxes();
    this->chartRasp3BCo2.chart->createDefaultAxes();

    this->chartRasp0Temp.chart->createDefaultAxes();
    this->chartRasp0Hum.chart->createDefaultAxes();
    this->chartRasp0Tvoc.chart->createDefaultAxes();
    this->chartRasp0Co2.chart->createDefaultAxes();
}

void SunshineDesktop::on_tempFreqRasp3BButton_clicked()
{
    qDebug() << "<Debug> Buttton rasp3b freq temp =" << ui->tempFreqRasp3BInput->text();
    this->mqttWrapper.Publisher(ui->tempFreqRasp3BInput->text().toStdString().data(), rasp3bFreqTemp);
}

void SunshineDesktop::on_humFreqRasp3BButton_clicked()
{
    qDebug() << "<Debug> Buttton rasp3b freq hum =" << ui->humFreqRasp3BInput->text();
    this->mqttWrapper.Publisher(ui->humFreqRasp3BInput->text().toStdString().data(), rasp3bFreqHum);
}

void SunshineDesktop::on_tvocFreqRasp3BButton_clicked()
{
    qDebug() << "<Debug> Buttton rasp3b freq tvoc =" << ui->tvocFreqRasp3BInput->text();
    this->mqttWrapper.Publisher(ui->tvocFreqRasp3BInput->text().toStdString().data(), rasp3bFreqTvoc);
}

void SunshineDesktop::on_co2FreqRasp3BButton_clicked()
{
    qDebug() << "<Debug> Buttton rasp3b freq co2 =" << ui->co2FreqRasp3BInput->text();
    this->mqttWrapper.Publisher(ui->co2FreqRasp3BInput->text().toStdString().data(), rasp3bFreqCo2);
}

void SunshineDesktop::on_tempFreqRasp0Button_clicked()
{
    qDebug() << "<Debug> Buttton rasp0 freq temp =" << ui->tempFreqRasp0Input->text();
    this->mqttWrapper.Publisher(ui->tempFreqRasp0Input->text().toStdString().data(), rasp0FreqTemp);
}

void SunshineDesktop::on_humFreqRasp0Button_clicked()
{
    qDebug() << "<Debug> Buttton rasp0 freq hum =" << ui->humFreqRasp0Input->text();
    this->mqttWrapper.Publisher(ui->humFreqRasp0Input->text().toStdString().data(), rasp0FreqHum);
}

void SunshineDesktop::on_tvocFreqRasp0Button_clicked()
{
    qDebug() << "<Debug> Buttton rasp0 freq tvoc =" << ui->tvocFreqRasp0Input->text();
    this->mqttWrapper.Publisher(ui->tvocFreqRasp0Input->text().toStdString().data(), rasp0FreqTvoc);
}

void SunshineDesktop::on_co2FreqRasp0Button_clicked()
{
    qDebug() << "<Debug> Buttton rasp0 freq co2 =" << ui->co2FreqRasp0Input->text();
    this->mqttWrapper.Publisher(ui->co2FreqRasp0Input->text().toStdString().data(), rasp0FreqCo2);
}

void SunshineDesktop::newSessionAction_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Session"), "/home/washout/repos/sunshine/serialized_sessions");

    qDebug() << "<Debug> Action load session application =" << fileName;
    if(fileName != "") {
        this->clenupMainWindow();

        this->serializator.newSession(fileName.toStdString(), this->rasp0SensorData, this->rasp3BSensorData);
    } else {
        qDebug() <<"<Debug> Session isn't created";
        return;
    }

    this->dataStoringStatus = false;
    this->ui->rasp0DataWidget->setEnabled(true);
    this->ui->rasp3bDataWidget->setEnabled(true);
    this->ui->startCaptureDataButton->setEnabled(true);
    if(this->ui->stopCaptureDataButton->isEnabled()) {
        this->ui->stopCaptureDataButton->setEnabled(false);
    }
}

void SunshineDesktop::loadSessionAction_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Session"), "/home/washout/repos/sunshine/serialized_sessions");
    qDebug() << "<Debug> Action save session application" << fileName;

    if(fileName != "") {
        this->clenupMainWindow();

        if(this->serializator.loadSession(fileName.toStdString(),
                                          this->rasp0SensorData, this->rasp3BSensorData) == -1)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Error");
            msgBox.setText("Empty file selected");
            msgBox.exec();
            return;
        }

        this->dataStoringStatus = false;

        this->chartRasp0Temp.readSerializedData(this->rasp0SensorData.getTemperatureMeasurements());
        this->chartRasp0Hum.readSerializedData(this->rasp0SensorData.getHumidityMeasurements());
        this->chartRasp0Tvoc.readSerializedData(this->rasp0SensorData.getTvocMeasurements());
        this->chartRasp0Co2.readSerializedData(this->rasp0SensorData.getCo2Measurements());

        this->chartRasp3BTemp.readSerializedData(this->rasp3BSensorData.getTemperatureMeasurements());
        this->chartRasp3BHum.readSerializedData(this->rasp3BSensorData.getHumidityMeasurements());
        this->chartRasp3BTvoc.readSerializedData(this->rasp3BSensorData.getTvocMeasurements());
        this->chartRasp3BCo2.readSerializedData(this->rasp3BSensorData.getCo2Measurements());

        if(this->rasp3BSensorData.getTemperatureMeasurements().size() != 0)
        {
            this->ui->tempRasp3BMeasLabel->setText(
                        QString::number(this->rasp3BSensorData.getTemperatureMeasurements().back()));
        }

        if(this->rasp3BSensorData.getHumidityMeasurements().size() != 0)
        {
            this->ui->humRasp3BMeasLabel->setText(
                        QString::number(this->rasp3BSensorData.getHumidityMeasurements().back()));
        }

        if(this->rasp3BSensorData.getTvocMeasurements().size() != 0)
        {
            this->ui->tvocRasp3BMeasLabel->setText(
                        QString::number(this->rasp3BSensorData.getTvocMeasurements().back()));
        }

        if(this->rasp3BSensorData.getCo2Measurements().size() != 0)
        {
            this->ui->co2Rasp3BMeasLabel->setText(
                        QString::number(this->rasp3BSensorData.getCo2Measurements().back()));
        }

        if(this->rasp0SensorData.getTemperatureMeasurements().size() != 0)
        {
            this->ui->tempRasp0MeasLabel->setText(
                        QString::number(this->rasp0SensorData.getTemperatureMeasurements().back()));
        }

        if(this->rasp0SensorData.getHumidityMeasurements().size() != 0)
        {
            this->ui->humRasp0MeasLabel->setText(
                        QString::number(this->rasp0SensorData.getHumidityMeasurements().back()));
        }

        if(this->rasp0SensorData.getTvocMeasurements().size() != 0)
        {
            this->ui->tvocRasp0MeasLabel->setText(
                        QString::number(this->rasp0SensorData.getTvocMeasurements().back()));
        }

        if(this->rasp0SensorData.getCo2Measurements().size() != 0)
        {
            this->ui->co2Rasp0MeasLabel->setText(
                        QString::number(this->rasp0SensorData.getCo2Measurements().back()));
        }
    } else {
        qDebug() <<"<Debug> No file selected";
        return;
    }
    this->ui->rasp0DataWidget->setEnabled(true);
    this->ui->rasp3bDataWidget->setEnabled(true);
    this->ui->startCaptureDataButton->setEnabled(true);
    if(this->ui->stopCaptureDataButton->isEnabled()) {
        this->ui->stopCaptureDataButton->setEnabled(false);
    }
}

void SunshineDesktop::measAnalyzerAction_clicked()
{
    if(this->ui->stopCaptureDataButton->isEnabled())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("You are capturing data right know!");
        msgBox.exec();
        return;
    }
    else if (!this->ui->stopCaptureDataButton->isEnabled() &&
             !this->ui->startCaptureDataButton->isEnabled())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("No data to compare in main window!");
        msgBox.exec();
        return;
    }
    else
    {
        qDebug() << "<Debug> Action analyzer application";
        this->sessionAnalyzer.exec();
    }
}

void SunshineDesktop::on_startCaptureDataButton_clicked()
{
    this->dataStoringStatus = true;
    this->ui->startCaptureDataButton->setEnabled(false);
    this->ui->stopCaptureDataButton->setEnabled(true);
}

void SunshineDesktop::on_stopCaptureDataButton_clicked()
{
    this->dataStoringStatus = false;
    this->ui->startCaptureDataButton->setEnabled(true);
    this->ui->stopCaptureDataButton->setEnabled(false);
}

void SunshineDesktop::setTempRasp3BSignal(const double value)
{
    if(this->dataStoringStatus) {
        this->chartRasp3BTemp.addPointToLineChart(value);
        this->ui->tempRasp3BMeasLabel->setText(QString::number(value));
        this->rasp3BSensorData.addTemperatureMeasurement(value);
    }
}

void SunshineDesktop::setHumRasp3BSignal(const double value)
{
    if(this->dataStoringStatus) {
        this->chartRasp3BHum.addPointToLineChart(value);
        this->ui->humRasp3BMeasLabel->setText(QString::number(value));
        this->rasp3BSensorData.addHumidityMeasurement(value);
    }
}

void SunshineDesktop::setTvocRasp3BSignal(const double value)
{
    if(this->dataStoringStatus) {
        this->chartRasp3BTvoc.addPointToLineChart(value);
        this->ui->tvocRasp3BMeasLabel->setText(QString::number(value));
        this->rasp3BSensorData.addTvocMeasurement(value);
    }
}

void SunshineDesktop::setCo2Rasp3BSignal(const double value)
{
    if(this->dataStoringStatus) {
        this->chartRasp3BCo2.addPointToLineChart(value);
        this->ui->co2Rasp3BMeasLabel->setText(QString::number(value));
        this->rasp3BSensorData.addCo2Measurement(value);
    }
}

void SunshineDesktop::setTempRasp0Signal(const double value)
{
    if(this->dataStoringStatus) {
        this->chartRasp0Temp.addPointToLineChart(value);
        this->ui->tempRasp0MeasLabel->setText(QString::number(value));
        this->rasp0SensorData.addTemperatureMeasurement(value);
    }
}

void SunshineDesktop::setHumRasp0Signal(const double value)
{
    if(this->dataStoringStatus) {
        this->chartRasp0Hum.addPointToLineChart(value);
        this->ui->humRasp0MeasLabel->setText(QString::number(value));
        this->rasp0SensorData.addHumidityMeasurement(value);
    }
}

void SunshineDesktop::setTvocRasp0Signal(const double value)
{
    if(this->dataStoringStatus) {
        this->chartRasp0Tvoc.addPointToLineChart(value);
        this->ui->tvocRasp0MeasLabel->setText(QString::number(value));
        this->rasp0SensorData.addTvocMeasurement(value);
    }
}

void SunshineDesktop::setCo2Rasp0Signal(const double value)
{
    if(this->dataStoringStatus) {
        this->chartRasp0Co2.addPointToLineChart(value);
        this->ui->co2Rasp0MeasLabel->setText(QString::number(value));
        this->rasp0SensorData.addCo2Measurement(value);
    }
}

void SunshineDesktop::setTempFreqRasp3BSignal(const double value)
{
    this->ui->tempFreqRasp3BInput->setText(QString::number(value));
}

void SunshineDesktop::setHumFreqRasp3BSignal(const double value)
{
    this->ui->humFreqRasp3BInput->setText(QString::number(value));
}

void SunshineDesktop::setTvocFreqRasp3BSignal(const double value)
{
    this->ui->tvocFreqRasp3BInput->setText(QString::number(value));
}

void SunshineDesktop::setCo2FreqRasp3BSignal(const double value)
{
    this->ui->co2FreqRasp3BInput->setText(QString::number(value));
}

void SunshineDesktop::setTempFreqRasp0Signal(const double value)
{
    this->ui->tempFreqRasp0Input->setText(QString::number(value));
}

void SunshineDesktop::setHumFreqRasp0Signal(const double value)
{
    this->ui->humFreqRasp0Input->setText(QString::number(value));
}

void SunshineDesktop::setTvocFreqRasp0Signal(const double value)
{
    this->ui->tvocFreqRasp0Input->setText(QString::number(value));
}

void SunshineDesktop::setCo2FreqRasp0Signal(const double value)
{
    this->ui->co2FreqRasp0Input->setText(QString::number(value));
}
