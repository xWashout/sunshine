#include <serializator.h>

#include <QDebug>
#include <QDir>
#include <stdio.h>
#include <string>
#include <iostream>

namespace tool {

Serializator::Serializator()
{
    QDir::setCurrent("/home/washout/repos/sunshine/serialized_sessions");
}

Serializator::~Serializator()
{
    if(this->sessionFile != NULL) {
        fclose(this->sessionFile);
        qDebug() << "File closed";
    }
}

void Serializator::newSession(const std::string& fileName)
{
    this->sessionFile = fopen(fileName.c_str(), "a+");

    if(this->sessionFile == NULL) {
        qDebug() << "File didn't open";
        return;
    }
    else {
        qDebug() << "File created correctly";
    }
}

void Serializator::addValueToFile(std::string dataType, const double value)
{
    if(this->sessionFile != NULL) {
        dataType.append(" ");
        dataType.append(std::to_string(value) + "\n");
        fputs(dataType.c_str(), this->sessionFile);
        fflush(this->sessionFile);
    }
    else {
        qDebug() << "Add file -> File didn't open";
    }
}

void Serializator::loadSession()
{

}


} // tool
