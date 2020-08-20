#include "sunshinedesktop.h"
#include "./ui_sunshinedesktop.h"

SunshineDesktop::SunshineDesktop(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SunshineDesktop)
{
    ui->setupUi(this);
}

SunshineDesktop::~SunshineDesktop()
{
    delete ui;
}

