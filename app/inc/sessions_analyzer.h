#ifndef SESSIONSANALYZER_H
#define SESSIONSANALYZER_H

#include <qt_chart_wrapper.h>
#include <QDialog>
#include <serializator.h>
#include <qt_chart_wrapper.h>
#include <measurements_data.h>
#include <array>
#include <analyzer_table_cells_enum.h>

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

    QString loadedFileName;

public:
    SessionsAnalyzer(sensor_data::Rasp0SensorData &rasp0SensorData, sensor_data::Rasp3BSensorData &rasp3BSensorData);
    ~SessionsAnalyzer();

    void reject();
    void showEvent(QShowEvent *ev);
    void cleanAndInitializeData();
    void setCalculationsFromFile();
    void setCalculationsFromApp();

    std::array<QTableWidgetItem*, 48> tableItemArray{};

private slots:
    void on_saveResultsButton_clicked();
    void on_loadDataButton_clicked();
};

} // namespace tool

#endif // SESSIONSANALYZER_H
