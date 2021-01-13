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
    this->lineSeriesLoaded = new QLineSeries();
    this->chart = new QChart();
    this->chartView = new QChartView();
    this->barSeries = new QBarSeries();
    this->barData = new QBarSet("");
    this->axis = new QBarCategoryAxis();
}

void QtChartWrapper::initLineChart(const QString title)
{
    QFont fontPoint("Times", 13, QFont::ExtraBold);
    this->lineSeries->setPointLabelsFont(fontPoint);
    this->lineSeries->setPointLabelsClipping(false);
    this->lineSeries->setPointLabelsColor("red");

    this->lineSeriesLoaded->setPointLabelsFont(fontPoint);
    this->lineSeriesLoaded->setPointLabelsClipping(false);
    this->lineSeriesLoaded->setPointLabelsColor("red");

    this->chart->legend()->hide();

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

//    chartView->chart()->setTheme(QChart::ChartThemeBlueCerulean);
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
    if(this->index < this->measuremenetLimit) {
        this->chart->removeSeries(this->lineSeries);
        this->lineSeries->append(++index, yValue);
        this->chart->addSeries(this->lineSeries);
        this->chart->createDefaultAxes();
    }
    else {
        this->index = 0;
        this->lineSeries->clear();
    }
}

void QtChartWrapper::addPointToBarChart(const double yValue)
{
    if(this->index < this->measuremenetLimit) {
        ++index;
        this->chart->removeSeries(this->barSeries);
        this->barData->append(yValue);
        this->barSeries->append(this->barData);
        this->chart->addSeries(this->barSeries);
        this->chart->createDefaultAxes();
    }
    else {
        this->index = 0;
        this->barSeries->clear();
        this->barData = new QBarSet("");
    }
}

void QtChartWrapper::cleanCharts()
{
    this->index = 0;
    this->indexSessionAnalizator = 0;
    this->lineSeries->clear();
    this->lineSeriesLoaded->clear();
    this->barSeries->clear();
    this->barData = new QBarSet("");
}

void QtChartWrapper::readSerializedData(const std::vector<double> &dataSet)
{
    this->chart->removeSeries(this->lineSeries);

    this->lineSeries->
            append(index++, 0.0); // to make scale 0 to 'first_val'
    for(const auto val : dataSet)
    {
        this->lineSeries->append(index++, val);
    }
    this->chart->addSeries(this->lineSeries);
    this->chart->createDefaultAxes();
}

void QtChartWrapper::drawNextDataset(const std::vector<double> &dataSet)
{
    this->chart->removeSeries(this->lineSeriesLoaded);
    this->chart->removeSeries(this->lineSeries);

    this->lineSeriesLoaded->
            append(indexSessionAnalizator++, 0.0); // to make scale 0 to 'first_val'
    for(const auto val : dataSet)
    {
        this->lineSeriesLoaded->append(indexSessionAnalizator++, val);
    }
    this->chart->addSeries(this->lineSeriesLoaded);
    this->chart->createDefaultAxes();
}

void QtChartWrapper::initAndDefaultAxes()
{
    this->chart->addSeries(this->lineSeries);
    this->chart->createDefaultAxes();
    this->lineSeries->append(0, 0.0);
}


} // qt_chart_wrapper

