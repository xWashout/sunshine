#ifndef QTCHARTWRAPPER_H
#define QTCHARTWRAPPER_H

#include <QObject>
#include <QtCharts/QtCharts>

namespace qt_chart_wrapper {

class QtChartWrapper : public QObject
{
    Q_OBJECT

public:
    QChartView *chartView;
    QLineSeries *lineSeries;
    QBarSeries *barSeries;
    QChart *chart;
    QBarSet *barData;
    QBarCategoryAxis *axis;

    QtChartWrapper();
    ~QtChartWrapper() = default;

    void initLineChart(const QString title);
    void initBarChart(const QString title);

    void addPointToLineChart(const double yValue);
    void addPointToBarChart(const double yValue);

    void cleanCharts();
    void readSerializedData(const std::vector<double>& dataSet);

private:
    int index = 0; // reset after measuremenetLimit value
    const int measuremenetLimit = 100;
};

} // namespace qt_chart_wrapper

#endif // QTCHARTWRAPPER_H
