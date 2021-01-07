#include "sunshinedesktop.h"
#include "./ui_sunshinedesktop.h"
#include <QDebug>
#include <clocale>

SunshineDesktop::SunshineDesktop(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SunshineDesktop)
    , mqttReceiverThread(&mqtt_wrapper::MqttWrapper::Receiver,
                         std::ref(mqttWrapper),
                         std::ref(*this)
                         )
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
    this->chartRasp3BTvoc.initLineChart("TVOC");
    this->chartRasp3BCo2.initLineChart("Co2");

    this->chartRasp0Temp.initLineChart("Temperature (Celsius)");
    this->chartRasp0Hum.initLineChart("Humidity (%)");
    this->chartRasp0Tvoc.initLineChart("TVOC");
    this->chartRasp0Co2.initLineChart("Co2");

    this->layout = new QGridLayout();
    this->menuBar = new QMenuBar(nullptr);
    this->menu = new QMenu();
    this->newSessionAction = new QAction("&New Session");
    this->loadSessionAction = new QAction("&Load Session");
    this->measAnalyzerAction = new QAction("&Open Data Analyzer");

    connect(this->newSessionAction, &QAction::triggered, this, &SunshineDesktop::newSessionAction_clicked);
    connect(this->loadSessionAction, &QAction::triggered, this, &SunshineDesktop::loadSessionAction_clicked);
    connect(this->measAnalyzerAction, &QAction::triggered, this, &SunshineDesktop::measAnalyzerAction_clicked);

    this->menu = this->menuBar->addMenu("START");
    this->menu->addAction(this->newSessionAction);
    this->menu->addAction(this->loadSessionAction);
    this->menu->addAction(this->measAnalyzerAction);
    this->menu->addSeparator();


    this->menuBar->setMaximumWidth(170);
    this->ui->stopCaptureDataButton->setMinimumHeight(40);
    this->ui->startCaptureDataButton->setMinimumHeight(40);
    this->ui->stopCaptureDataButton->setMaximumWidth(300);
    this->ui->startCaptureDataButton->setMaximumWidth(300);

    this->layout->addWidget(this->menuBar, 0,0);
    this->layout->addWidget(this->ui->startCaptureDataButton, 0,1);
    this->layout->addWidget(this->ui->stopCaptureDataButton, 0,2);

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
}

SunshineDesktop::~SunshineDesktop()
{
    this->serializator.closeSession(this->rasp0SendorData, this->rasp3BSendorData);
    delete this->ui;
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
        this->chartRasp0Temp.cleanCharts();
        this->chartRasp0Hum.cleanCharts();
        this->chartRasp0Tvoc.cleanCharts();
        this->chartRasp0Co2.cleanCharts();

        this->chartRasp3BTemp.cleanCharts();
        this->chartRasp3BHum.cleanCharts();
        this->chartRasp3BTvoc.cleanCharts();
        this->chartRasp3BCo2.cleanCharts();

        this->serializator.newSession(fileName.toStdString(), this->rasp0SendorData, this->rasp3BSendorData);
    } else {
        qDebug() <<"<Debug> Session isn't created";
        return;
    }

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
        this->serializator.loadSession(fileName.toStdString(), this->rasp0SendorData, this->rasp3BSendorData);
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
    this->dataStoringStatus = false;
    this->ui->rasp0DataWidget->setEnabled(false);
    this->ui->rasp3bDataWidget->setEnabled(false);
    this->ui->startCaptureDataButton->setEnabled(false);
    this->ui->stopCaptureDataButton->setEnabled(false);
    qDebug() << "<Debug> Action analyzer application";
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
        this->rasp3BSendorData.addTemperatureMeasurement(value);
    }
}

void SunshineDesktop::setHumRasp3BSignal(const double value)
{
    if(this->dataStoringStatus) {
        this->chartRasp3BHum.addPointToLineChart(value);
        this->ui->humRasp3BMeasLabel->setText(QString::number(value));
        this->rasp3BSendorData.addHumidityMeasurement(value);
    }
}

void SunshineDesktop::setTvocRasp3BSignal(const double value)
{
    if(this->dataStoringStatus) {
        this->chartRasp3BTvoc.addPointToLineChart(value);
        this->ui->tvocRasp3BMeasLabel->setText(QString::number(value));
        this->rasp3BSendorData.addTvocMeasurement(value);
    }
}

void SunshineDesktop::setCo2Rasp3BSignal(const double value)
{
    if(this->dataStoringStatus) {
        this->chartRasp3BCo2.addPointToLineChart(value);
        this->ui->co2Rasp3BMeasLabel->setText(QString::number(value));
        this->rasp3BSendorData.addCo2Measurement(value);
    }
}

void SunshineDesktop::setTempRasp0Signal(const double value)
{
    if(this->dataStoringStatus) {
        this->chartRasp0Temp.addPointToLineChart(value);
        this->ui->tempRasp0MeasLabel->setText(QString::number(value));
        this->rasp0SendorData.addTemperatureMeasurement(value);
    }
}

void SunshineDesktop::setHumRasp0Signal(const double value)
{
    if(this->dataStoringStatus) {
        this->chartRasp0Hum.addPointToLineChart(value);
        this->ui->humRasp0MeasLabel->setText(QString::number(value));
        this->rasp0SendorData.addHumidityMeasurement(value);
    }
}

void SunshineDesktop::setTvocRasp0Signal(const double value)
{
    if(this->dataStoringStatus) {
        this->chartRasp0Tvoc.addPointToLineChart(value);
        this->ui->tvocRasp0MeasLabel->setText(QString::number(value));
        this->rasp0SendorData.addTvocMeasurement(value);
    }
}

void SunshineDesktop::setCo2Rasp0Signal(const double value)
{
    if(this->dataStoringStatus) {
        this->chartRasp0Co2.addPointToLineChart(value);
        this->ui->co2Rasp0MeasLabel->setText(QString::number(value));
        this->rasp0SendorData.addCo2Measurement(value);
    }
}
