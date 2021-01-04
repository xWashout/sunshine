#include "sunshinedesktop.h"
#include "./ui_sunshinedesktop.h"
#include <QDebug>

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
    ui->setupUi(this);

    mqttReceiverThread.detach();
}

SunshineDesktop::~SunshineDesktop()
{
    delete ui;
}

void SunshineDesktop::on_tempFreqRasp3BButton_clicked()
{
    qDebug() << "<Debug> Buttton rasp3b freq temp =" << ui->tempFreqRasp3BInput->text();
    mqttWrapper.Publisher(ui->tempFreqRasp3BInput->text().toStdString().data(), rasp3bFreqTemp);
}

void SunshineDesktop::on_humFreqRasp3BButton_clicked()
{
    qDebug() << "<Debug> Buttton rasp3b freq hum =" << ui->humFreqRasp3BInput->text();
    mqttWrapper.Publisher(ui->humFreqRasp3BInput->text().toStdString().data(), rasp3bFreqHum);
}

void SunshineDesktop::on_tvocFreqRasp3BButton_clicked()
{
    qDebug() << "<Debug> Buttton rasp3b freq tvoc =" << ui->tvocFreqRasp3BInput->text();
    mqttWrapper.Publisher(ui->tvocFreqRasp3BInput->text().toStdString().data(), rasp3bFreqTvoc);
}

void SunshineDesktop::on_co2FreqRasp3BButton_clicked()
{
    qDebug() << "<Debug> Buttton rasp3b freq co2 =" << ui->co2FreqRasp3BInput->text();
    mqttWrapper.Publisher(ui->co2FreqRasp3BInput->text().toStdString().data(), rasp3bFreqCo2);
}

void SunshineDesktop::on_tempFreqRasp0Button_clicked()
{
    qDebug() << "<Debug> Buttton rasp0 freq temp =" << ui->tempFreqRasp0Input->text();
    mqttWrapper.Publisher(ui->tempFreqRasp0Input->text().toStdString().data(), rasp0FreqTemp);
}

void SunshineDesktop::on_humFreqRasp0Button_clicked()
{
    qDebug() << "<Debug> Buttton rasp0 freq hum =" << ui->humFreqRasp0Input->text();
    mqttWrapper.Publisher(ui->humFreqRasp0Input->text().toStdString().data(), rasp0FreqHum);
}

void SunshineDesktop::on_tvocFreqRasp0Button_clicked()
{
    qDebug() << "<Debug> Buttton rasp0 freq tvoc =" << ui->tvocFreqRasp0Input->text();
    mqttWrapper.Publisher(ui->tvocFreqRasp0Input->text().toStdString().data(), rasp0FreqTvoc);
}

void SunshineDesktop::on_co2FreqRasp0Button_clicked()
{
    qDebug() << "<Debug> Buttton rasp0 freq co2 =" << ui->co2FreqRasp0Input->text();
    mqttWrapper.Publisher(ui->co2FreqRasp0Input->text().toStdString().data(), rasp0FreqCo2);
}

void SunshineDesktop::setTempRasp3BSignal(const double value)
{
    ui->tempRasp3BMeasLabel->setText(QString::number(value));
}

void SunshineDesktop::setHumRasp3BSignal(const double value)
{
    ui->humRasp3BMeasLabel->setText(QString::number(value));
}

void SunshineDesktop::setTvocRasp3BSignal(const double value)
{
    ui->tvocRasp3BMeasLabel->setText(QString::number(value));
}

void SunshineDesktop::setCo2Rasp3BSignal(const double value)
{
    ui->co2Rasp3BMeasLabel->setText(QString::number(value));
}

void SunshineDesktop::setTempRasp0Signal(const double value)
{
    ui->tempRasp0MeasLabel->setText(QString::number(value));
}

void SunshineDesktop::setHumRasp0Signal(const double value)
{
    ui->humRasp0MeasLabel->setText(QString::number(value));
}

void SunshineDesktop::setTvocRasp0Signal(const double value)
{
    ui->tvocRasp0MeasLabel->setText(QString::number(value));
}

void SunshineDesktop::setCo2Rasp0Signal(const double value)
{
    ui->co2Rasp0MeasLabel->setText(QString::number(value));
}
