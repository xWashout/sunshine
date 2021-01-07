#ifndef SERIALIZATOR_H
#define SERIALIZATOR_H

#include <QFile>
#include <rasp0_sensor_data.h>
#include <rasp3b_sensor_data.h>

namespace tool {

class Serializator
{
private:
    FILE *sessionFile = NULL; // C FILE (fstream don't work with QT)
public:
    Serializator();
    ~Serializator();

    void newSession(const std::string fileName);
    void closeSession(sensor_data::Rasp0SensorData& rasp0SendorData,
                      sensor_data::Rasp3BSensorData& rasp3BSendorData);
    void loadSession(const std::string fileName);

};

} // namespace tool

#endif // SERIALIZATOR_H
