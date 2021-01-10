#ifndef SESSIONSANALYZER_H
#define SESSIONSANALYZER_H

#include <qt_chart_wrapper.h>
#include <QDialog>
#include <serializator.h>
#include <qt_chart_wrapper.h>
#include <rasp0_sensor_data.h>
#include <rasp3b_sensor_data.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

namespace tool {

class SessionsAnalyzer: public QDialog
{
    Q_OBJECT

    Ui::Dialog* ui;
    qt_chart_wrapper::QtChartWrapper chartRasp3BCo2;
    qt_chart_wrapper::QtChartWrapper chartRasp3BTvoc;
    qt_chart_wrapper::QtChartWrapper chartRasp3BHum;
    qt_chart_wrapper::QtChartWrapper chartRasp3BTemp;

    qt_chart_wrapper::QtChartWrapper chartRasp0Co2;
    qt_chart_wrapper::QtChartWrapper chartRasp0Tvoc;
    qt_chart_wrapper::QtChartWrapper chartRasp0Hum;
    qt_chart_wrapper::QtChartWrapper chartRasp0Temp;

    tool::Serializator serializator;
    qt_chart_wrapper::QtChartWrapper qtChartWrapper;
    sensor_data::Rasp0SensorData &rasp0SendorData;
    sensor_data::Rasp3BSensorData &rasp3BSendorData;

    sensor_data::Rasp0SensorData rasp0SendorDataFile;
    sensor_data::Rasp3BSensorData rasp3BSendorDataFile;
public:
    SessionsAnalyzer(sensor_data::Rasp0SensorData &rasp0SendorData, sensor_data::Rasp3BSensorData &rasp3BSendorData);
    ~SessionsAnalyzer();

    void reject();

private slots:
    void on_saveResultsButton_clicked();
    void on_loadDataButton_clicked();
};

} // namespace tool

#endif // SESSIONSANALYZER_H
