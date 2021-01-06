#ifndef SERIALIZATOR_H
#define SERIALIZATOR_H

#include <QFile>

namespace tool {

class Serializator
{
private:
    FILE *sessionFile = NULL; // C FILE (fstream don't work with QT)
public:
    Serializator();
    ~Serializator();

    void newSession(const std::string& fileName);
    void addValueToFile(std::string dataType, const double value);
    void loadSession();

};

} // namespace tool

#endif // SERIALIZATOR_H
