#ifndef SESSIONSANALYZER_H
#define SESSIONSANALYZER_H

#include <qt_chart_wrapper.h>
#include <QDialog>
#include <serializator.h>
#include <qt_chart_wrapper.h>
#include <measurements_data.h>
#include <array>

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

    tool::Serializator<sensor_data::MeasurementsData, sensor_data::MeasurementsData> serializator;
    qt_chart_wrapper::QtChartWrapper qtChartWrapper;

    sensor_data::MeasurementsData rasp0SensorDataBufor; // copied mutex class vectors
    sensor_data::MeasurementsData rasp3BSensorDataBufor; // copied mutex class vectors

    sensor_data::MeasurementsData rasp0SensorDataFile;
    sensor_data::MeasurementsData rasp3BSensorDataFile;

    sensor_data::Rasp0SensorData& rasp0SensorData;
    sensor_data::Rasp3BSensorData& rasp3BSensorData;

public:
    SessionsAnalyzer(sensor_data::Rasp0SensorData &rasp0SensorData, sensor_data::Rasp3BSensorData &rasp3BSensorData);
    ~SessionsAnalyzer();

    void reject();
    void showEvent(QShowEvent *ev);
    void cleanAndInitializeData();
    void setCalculationsFromFile();
    void setCalculationsFromApp();

    std::array<QTableWidgetItem*, 48> tableItemArray { nullptr };

    enum MeasId {
        // START FILE RASP0
        tempMaxFileRasp0Item = 0,
        tempMinFileRasp0Item = 1,
        tempAvgFileRasp0Item = 2,

        humMaxFileRasp0Item = 3,
        humMinFileRasp0Item = 4,
        humAvgFileRasp0Item = 5,

        tvocMaxFileRasp0Item = 6,
        tvocMinFileRasp0Item = 7,
        tvocAvgFileRasp0Item = 8,

        co2MaxFileRasp0Item = 9,
        co2MinFileRasp0Item = 10,
        co2AvgFileRasp0Item = 11,
        // END FILE RASP0

        // START APP RASP0
        tempMaxAppRasp0Item = 12,
        tempMinAppRasp0Item = 13,
        tempAvgAppRasp0Item = 14,

        humMaxAppRasp0Item = 15,
        humMinAppRasp0Item = 16,
        humAvgAppRasp0Item = 17,

        tvocMaxAppRasp0Item = 18,
        tvocMinAppRasp0Item = 19,
        tvocAvgAppRasp0Item = 20,

        co2MaxAppRasp0Item = 21,
        co2MinAppRasp0Item = 22,
        co2AvgAppRasp0Item = 23,
        // APP FILE RASP0

        // START FILE RASP3B
        tempMaxFileRasp3BItem = 24,
        tempMinFileRasp3BItem = 25,
        tempAvgFileRasp3BItem = 26,

        humMaxFileRasp3BItem = 27,
        humMinFileRasp3BItem = 28,
        humAvgFileRasp3BItem = 29,

        tvocMaxFileRasp3BItem = 30,
        tvocMinFileRasp3BItem = 31,
        tvocAvgFileRasp3BItem = 32,

        co2MaxFileRasp3BItem = 33,
        co2MinFileRasp3BItem = 34,
        co2AvgFileRasp3BItem = 35,
        // END FILE RASP3B

        // START APP RASP3B
        tempMaxAppRasp3BItem = 36,
        tempMinAppRasp3BItem = 37,
        tempAvgAppRasp3BItem = 38,

        humMaxAppRasp3BItem = 39,
        humMinAppRasp3BItem = 40,
        humAvgAppRasp3BItem = 41,

        tvocMaxAppRasp3BItem = 42,
        tvocMinAppRasp3BItem = 43,
        tvocAvgAppRasp3BItem = 44,

        co2MaxAppRasp3BItem = 45,
        co2MinAppRasp3BItem = 46,
        co2AvgAppRasp3BItem = 47,
        // APP FILE RASP0
    };

private slots:
    void on_saveResultsButton_clicked();
    void on_loadDataButton_clicked();
};

} // namespace tool

#endif // SESSIONSANALYZER_H
