#include "sunshinedesktop.h"
#include "./ui_sunshinedesktop.h"
#include <QDebug>
#include <clocale>

SunshineDesktop::SunshineDesktop(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SunshineDesktop)
    , mqttReceiverThread(&mqtt_wrapper::MqttWrapper::Receiver,
                         std::ref(mqttWrapper),
                         std::ref(rasp0SendorData),
                         std::ref(rasp3BSendorData),
                         std::ref(*this)
                         )
{
    std::setlocale(LC_NUMERIC, "C"); // dot instead of comma in coding floating numbers

    this->ui->setupUi(this);
    this->ui->titleRasp0Label->setStyleSheet("font-weight: bold; color: red; font-size:20px");
    this->ui->titleRasp3bLabel->setStyleSheet("font-weight: bold; color: red; font-size:20px");

    this->chartRasp3BTemp.initLineChart("Temperature (Celsius)");
    this->chartRasp3BHum.initLineChart("Humidity (%)");
    this->chartRasp3BTvoc.initBarChart("TVOC");
    this->chartRasp3BCo2.initBarChart("Co2");

    this->chartRasp0Temp.initLineChart("Temperature (Celsius)");
    this->chartRasp0Hum.initLineChart("Humidity (%)");
    this->chartRasp0Tvoc.initBarChart("TVOC");
    this->chartRasp0Co2.initBarChart("Co2");

    this->layout = new QGridLayout();
    this->menuBar = new QMenuBar(nullptr);
    this->menu = new QMenu();
    this->newSessionAction = new QAction("&New Session");
    this->loadSessionAction = new QAction("&Load Session");
    this->measAnalyzerAction = new QAction("&Open Data Analyzer");

    connect(this->newSessionAction, &QAction::triggered, this, &SunshineDesktop::newSessionAction_clicked);
    connect(this->loadSessionAction, &QAction::triggered, this, &SunshineDesktop::loadSessionAction_clicked);
    connect(this->measAnalyzerAction, &QAction::triggered, this, &SunshineDesktop::measAnalyzerAction_clicked);

    this->menu = this->menuBar->addMenu("--> Click for options <--");
    this->menu->addAction(this->newSessionAction);
    this->menu->addAction(this->loadSessionAction);
    this->menu->addAction(this->measAnalyzerAction);
    this->menu->addSeparator();


    this->menuBar->setMaximumWidth(170);
    this->layout->addWidget(this->menuBar, 0,0);
    this->layout->addWidget(chartRasp3BTemp.chartView, 1, 0);
    this->layout->addWidget(chartRasp3BHum.chartView, 1, 1);
    this->layout->addWidget(chartRasp3BTvoc.chartView, 1, 2);
    this->layout->addWidget(chartRasp3BCo2.chartView, 1, 3);

    this->layout->addWidget(chartRasp0Temp.chartView, 2, 0);
    this->layout->addWidget(chartRasp0Hum.chartView, 2, 1);
    this->layout->addWidget(chartRasp0Tvoc.chartView, 2, 2);
    this->layout->addWidget(chartRasp0Co2.chartView, 2, 3);

    this->layout->addWidget(ui->rasp3bDataWidget, 1, 4);
    this->layout->addWidget(ui->rasp0DataWidget, 2, 4);

    this->ui->centralwidget->setLayout(layout);
    this->ui->rasp0DataWidget->setEnabled(false);
    this->ui->rasp3bDataWidget->setEnabled(false);
}

SunshineDesktop::~SunshineDesktop()
{
    /* check if thread was detached before program termination
       if not program will crashed */
    if(this->mqttReceiverThread.joinable()) {
        this->mqttReceiverThread.detach();
    }
    delete ui;
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
    qDebug() << "<Debug> Action load session application =" << 2;

    this->ui->rasp0DataWidget->setEnabled(true);
    this->ui->rasp3bDataWidget->setEnabled(true);
    this->dataStoringStatus = true;

    if(this->mqttReceiverThread.joinable()) {
        this->mqttReceiverThread.detach();
    }
}

void SunshineDesktop::loadSessionAction_clicked()
{
    qDebug() << "<Debug> Action save session application" << 3;
    this->ui->rasp0DataWidget->setEnabled(true);
    this->ui->rasp3bDataWidget->setEnabled(true);
    this->dataStoringStatus = false;
}

void SunshineDesktop::measAnalyzerAction_clicked()
{
    this->dataStoringStatus = false;
    this->ui->rasp0DataWidget->setEnabled(false);
    this->ui->rasp3bDataWidget->setEnabled(false);
    qDebug() << "<Debug> Action analyzer application" << 4;
}

void SunshineDesktop::setTempRasp3BSignal(const double value)
{
    if(this->dataStoringStatus) {
        this->chartRasp3BTemp.addPointToLineChart(value);
        this->ui->tempRasp3BMeasLabel->setText(QString::number(value));
    }
}

void SunshineDesktop::setHumRasp3BSignal(const double value)
{
    if(this->dataStoringStatus) {
        this->chartRasp3BHum.addPointToLineChart(value);
        this->ui->humRasp3BMeasLabel->setText(QString::number(value));
    }
}

void SunshineDesktop::setTvocRasp3BSignal(const double value)
{
    if(this->dataStoringStatus) {
        this->chartRasp3BTvoc.addPointToBarChart(value);
        this->ui->tvocRasp3BMeasLabel->setText(QString::number(value));
    }
}

void SunshineDesktop::setCo2Rasp3BSignal(const double value)
{
    if(this->dataStoringStatus) {
        this->chartRasp3BCo2.addPointToBarChart(value);
        this->ui->co2Rasp3BMeasLabel->setText(QString::number(value));
    }
}

void SunshineDesktop::setTempRasp0Signal(const double value)
{
    if(this->dataStoringStatus) {
        this->chartRasp0Temp.addPointToLineChart(value);
        this->ui->tempRasp0MeasLabel->setText(QString::number(value));
    }
}

void SunshineDesktop::setHumRasp0Signal(const double value)
{
    if(this->dataStoringStatus) {
        this->chartRasp0Hum.addPointToLineChart(value);
        this->ui->humRasp0MeasLabel->setText(QString::number(value));
    }
}

void SunshineDesktop::setTvocRasp0Signal(const double value)
{
    if(this->dataStoringStatus) {
        this->chartRasp0Tvoc.addPointToBarChart(value);
        this->ui->tvocRasp0MeasLabel->setText(QString::number(value));
    }
}

void SunshineDesktop::setCo2Rasp0Signal(const double value)
{
    if(this->dataStoringStatus) {
        this->chartRasp0Co2.addPointToBarChart(value);
        this->ui->co2Rasp0MeasLabel->setText(QString::number(value));
    }
}
