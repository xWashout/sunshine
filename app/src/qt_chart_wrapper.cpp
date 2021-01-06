#include <qt_chart_wrapper.h>

// The main window to which you add toolbars,
// menubars, widgets and status bar
#include <QtWidgets/QMainWindow>

// Widget used to display charts
#include <QtCharts/QChartView>

// Used to draw bars representing data provided
// grouped into categories
#include <QtCharts/QBarSeries>

// Represents 1 set of bars in a bar chart
#include <QtCharts/QBarSet>

// Displays the color used to represent each
// QBarSet
#include <QtCharts/QLegend>

// Adds categories to the charts axes
#include <QtCharts/QBarCategoryAxis>

// Used to create stacked bar charts
#include <QtCharts/QHorizontalStackedBarSeries>

// Used to create a line chart
#include <QtCharts/QLineSeries>

// Used to change names on axis
#include <QtCharts/QCategoryAxis>

// Used to make Pie Charts
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

// Define the scope for your variables and functions


namespace qt_chart_wrapper{

QT_CHARTS_USE_NAMESPACE

QtChartWrapper::QtChartWrapper()
{
    lineSeries = new QLineSeries();
    chart = new QChart();
    chartView = new QChartView();
    barSeries = new QBarSeries();
    barData = new QBarSet("");
    axis = new QBarCategoryAxis();
}

void QtChartWrapper::initLineChart(const QString title)
{
    lineSeries->setPointLabelsVisible(true);
    lineSeries->setPointLabelsColor(Qt::black);
    lineSeries->setPointLabelsFormat("@yPoint");

    QFont fontPoint("Times", 13, QFont::ExtraBold);
    lineSeries->setPointLabelsFont(fontPoint);
    lineSeries->setPointLabelsClipping(false);
    lineSeries->setPointLabelsColor("red");

    chart->legend()->hide();
    chart->addSeries(lineSeries);
    chart->createDefaultAxes();

    QFont font;
    font.setPixelSize(18);
    chart->setTitleFont(font);
    chart->setTitleBrush(QBrush(Qt::black));
    chart->setTitle(title);

    QPen pen(QRgb(0x000000));
    pen.setWidth(1);
    lineSeries->setPen(pen);
    chartView->setMinimumWidth(500);
    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
}

void QtChartWrapper::initBarChart(const QString title)
{
    barData->setLabel(title);
    barSeries->setLabelsVisible(true);
    barSeries->append(barData);
    chart->addSeries(barSeries);
    chart->setTitle(title);

    QBarCategoryAxis *axis = new QBarCategoryAxis();
    QFont font;
    font.setPixelSize(18);
    chart->setTitleFont(font);
    chart->setTitleBrush(QBrush(Qt::black));
    chart->createDefaultAxes();
    chart->setAxisX(axis, barSeries);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    chartView->setMinimumWidth(700);

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

