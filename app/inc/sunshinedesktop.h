#ifndef SUNSHINEDESKTOP_H
#define SUNSHINEDESKTOP_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class SunshineDesktop; }
QT_END_NAMESPACE

class SunshineDesktop : public QMainWindow
{
    Q_OBJECT

public:
    SunshineDesktop(QWidget *parent = nullptr);
    ~SunshineDesktop();

private:
    Ui::SunshineDesktop *ui;
};
#endif // SUNSHINEDESKTOP_H
