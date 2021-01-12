#ifndef SUNSHINEDESKTOP_H
#define SUNSHINEDESKTOP_H

#include <QMainWindow>
#include <mqtt_wrapper.h>
#include <rasp0_sensor_data.h>
#include <rasp3b_sensor_data.h>
#include <qt_chart_wrapper.h>
#include <thread>
#include <serializator.h>
#include <sessions_analyzer.h>

QT_BEGIN_NAMESPACE
namespace Ui { class SunshineDesktop; }
QT_END_NAMESPACE

class SunshineDesktop : public QMainWindow
{
    Q_OBJECT

    bool dataStoringStatus = false;

    std::thread mqttReceiverThread;
    mqtt_wrapper::MqttWrapper mqttWrapper;
    sensor_data::Rasp0SensorData rasp0SensorData;
    sensor_data::Rasp3BSensorData rasp3BSensorData;
    tool::Serializator<sensor_data::Rasp0SensorData, sensor_data::Rasp3BSensorData> serializator;
    tool::SessionsAnalyzer sessionAnalyzer;

//    std::thread mqttPublisherThread;

    const std::string rasp3bInit { "rasp3bInit" };
    const std::string rasp3bFreqTemp { "rasp3bFreqTemp" };
    const std::string rasp3bFreqHum { "rasp3bFreqHum" };
    const std::string rasp3bFreqTvoc { "rasp3bFreqTvoc" };
    const std::string rasp3bFreqCo2 { "rasp3bFreqCo2" };

    const std::string rasp0Init { "rasp0Init" };
    const std::string rasp0FreqTemp { "rasp0FreqTemp" };
    const std::string rasp0FreqHum { "rasp0FreqHumm" };
    const std::string rasp0FreqTvoc { "rasp0FreqTvoc" };
    const std::string rasp0FreqCo2 { "rasp0FreqCo2" };

    QGridLayout *layout;
    QMenu *menu;
    QMenuBar *menuBar;
    QAction *newSessionAction;
    QAction *loadSessionAction;
    QAction *measAnalyzerAction;

    qt_chart_wrapper::QtChartWrapper chartRasp3BCo2;
    qt_chart_wrapper::QtChartWrapper chartRasp3BTvoc;
    qt_chart_wrapper::QtChartWrapper chartRasp3BHum;
    qt_chart_wrapper::QtChartWrapper chartRasp3BTemp;

    qt_chart_wrapper::QtChartWrapper chartRasp0Co2;
    qt_chart_wrapper::QtChartWrapper chartRasp0Tvoc;
    qt_chart_wrapper::QtChartWrapper chartRasp0Hum;
    qt_chart_wrapper::QtChartWrapper chartRasp0Temp;

public:
    Ui::SunshineDesktop *ui;
    SunshineDesktop(QWidget *parent = nullptr);
    ~SunshineDesktop();

    void clenupMainWindow();

private slots:
    void on_co2FreqRasp3BButton_clicked();
    void on_tvocFreqRasp3BButton_clicked();
    void on_humFreqRasp3BButton_clicked();
    void on_tempFreqRasp3BButton_clicked();
    void on_co2FreqRasp0Button_clicked();
    void on_tvocFreqRasp0Button_clicked();
    void on_humFreqRasp0Button_clicked();
    void on_tempFreqRasp0Button_clicked();
    void newSessionAction_clicked();
    void loadSessionAction_clicked();
    void measAnalyzerAction_clicked();
    void on_stopCaptureDataButton_clicked();
    void on_startCaptureDataButton_clicked();

public slots:
    void setTempRasp3BSignal(const double value);
    void setHumRasp3BSignal(const double value);
    void setTvocRasp3BSignal(const double value);
    void setCo2Rasp3BSignal(const double value);

    void setTempRasp0Signal(const double value);
    void setHumRasp0Signal(const double value);
    void setTvocRasp0Signal(const double value);
    void setCo2Rasp0Signal(const double value);
};
#endif // SUNSHINEDESKTOP_H
