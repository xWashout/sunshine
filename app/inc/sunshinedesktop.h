#ifndef SUNSHINEDESKTOP_H
#define SUNSHINEDESKTOP_H

#include <QMainWindow>
#include <mqtt_wrapper.h>
#include <rasp0_sensor_data.h>
#include <rasp3b_sensor_data.h>
#include <thread>

QT_BEGIN_NAMESPACE
namespace Ui { class SunshineDesktop; }
QT_END_NAMESPACE

class SunshineDesktop : public QMainWindow
{
    Q_OBJECT
    mqtt_wrapper::MqttWrapper mqttWrapper;
    sensor_data::Rasp0SensorData rasp0SendorData;
    sensor_data::Rasp3BSensorData rasp3BSendorData;

    std::thread mqttReceiverThread;
//    std::thread mqttPublisherThread;

    const std::string rasp3bFreqTemp { "rasp3bFreqTemp" };
    const std::string rasp3bFreqHum { "rasp3bFreqHum" };
    const std::string rasp3bFreqTvoc { "rasp3bFreqTvoc" };
    const std::string rasp3bFreqCo2 { "rasp3bFreqCo2" };

    const std::string rasp0FreqTemp { "rasp0FreqTemp" };
    const std::string rasp0FreqHum { "rasp0FreqHumm" };
    const std::string rasp0FreqTvoc { "rasp0FreqTvoc" };
    const std::string rasp0FreqCo2 { "rasp0FreqCo2" };

public:
    SunshineDesktop(QWidget *parent = nullptr);
    ~SunshineDesktop();

public slots:
    void on_co2FreqRasp3BButton_clicked();
    void on_tvocFreqRasp3BButton_clicked();
    void on_humFreqRasp3BButton_clicked();
    void on_tempFreqRasp3BButton_clicked();

public slots:
    void setTempRasp3BSignal(const double value);
    void setHumRasp3BSignal(const double value);
    void setTvocRasp3BSignal(const double value);
    void setCo2Rasp3BSignal(const double value);

    void setTempRasp0Signal(const double value);
    void setHumRasp0Signal(const double value);
    void setTvocRasp0Signal(const double value);
    void setCo2Rasp0Signal(const double value);

public:
    Ui::SunshineDesktop *ui;

private slots:
    void on_co2FreqRasp0Button_clicked();

private slots:
    void on_tvocFreqRasp0Button_clicked();

private slots:
    void on_humFreqRasp0Button_clicked();

private slots:
    void on_tempFreqRasp0Button_clicked();
};
#endif // SUNSHINEDESKTOP_H
