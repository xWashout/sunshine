#include <qt_chart_wrapper.h>

#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

namespace qt_chart_wrapper{

QT_CHARTS_USE_NAMESPACE

QtChartWrapper::QtChartWrapper()
{
    this->lineSeries = new QLineSeries();
    this->chart = new QChart();
    this->chartView = new QChartView();
    this->barSeries = new QBarSeries();
    this->barData = new QBarSet("");
    this->axis = new QBarCategoryAxis();
}

void QtChartWrapper::initLineChart(const QString title)
{
    this->lineSeries->setPointLabelsVisible(true);
    this->lineSeries->setPointLabelsColor(Qt::black);
    this->lineSeries->setPointLabelsFormat("@yPoint");

    QFont fontPoint("Times", 13, QFont::ExtraBold);
    this->lineSeries->setPointLabelsFont(fontPoint);
    this->lineSeries->setPointLabelsClipping(false);
    this->lineSeries->setPointLabelsColor("red");

    this->chart->legend()->hide();
    this->chart->addSeries(lineSeries);
    this->chart->createDefaultAxes();

    QFont font;
    font.setPixelSize(18);
    this->chart->setTitleFont(font);
    this->chart->setTitleBrush(QBrush(Qt::black));
    this->chart->setTitle(title);

    QPen pen(QRgb(0x000000));
    pen.setWidth(1);
    this->lineSeries->setPen(pen);
    this->chartView->setMinimumWidth(500);
    this->chartView->setChart(chart);
    this->chartView->setRenderHint(QPainter::Antialiasing);
}

void QtChartWrapper::initBarChart(const QString title)
{
    this->barData->setLabel(title);
    this->barSeries->setLabelsVisible(true);
    this->barSeries->append(barData);
    this->chart->addSeries(barSeries);
    this->chart->setTitle(title);

    QBarCategoryAxis *axis = new QBarCategoryAxis();
    QFont font;
    font.setPixelSize(18);
    this->chart->setTitleFont(font);
    this->chart->setTitleBrush(QBrush(Qt::black));
    this->chart->createDefaultAxes();
    this->chart->setAxisX(axis, barSeries);
    this->chart->legend()->setVisible(true);
    this->chart->legend()->setAlignment(Qt::AlignBottom);

    this->chartView = new QChartView(chart);
    this->chartView->setRenderHint(QPainter::Antialiasing);

    this->chartView->setMinimumWidth(700);

    QPalette pal = qApp->palette();

    pal.setColor(QPalette::Window, QRgb(0xffffff));
    pal.setColor(QPalette::WindowText, QRgb(0x404044));
    qApp->setPalette(pal);
}

void QtChartWrapper::addPointToLineChart(const double yValue)
{
    chart->removeSeries(lineSeries);
    lineSeries->append(++index, yValue);
    chart->addSeries(lineSeries);
    chart->createDefaultAxes();
}

void QtChartWrapper::addPointToBarChart(const double yValue)
{
    chart->removeSeries(barSeries);
    *barData << yValue;
    barSeries->append(barData);
    chart->addSeries(barSeries);
    chart->createDefaultAxes();
}

} // qt_chart_wrapper

