#ifndef SERIALIZATOR_H
#define SERIALIZATOR_H

#include <QFile>
#include <rasp0_sensor_data.h>
#include <rasp3b_sensor_data.h>

namespace tool {

class Serializator
{
private:
    FILE *sessionFile = NULL; // C FILE (fstream doesn't work with QT)
public:
    Serializator();
    ~Serializator() = default;

    void newSession(const std::string fileName,
                    sensor_data::Rasp0SensorData& rasp0SendorData,
                    sensor_data::Rasp3BSensorData& rasp3BSendorData);
    void loadSession(const std::string fileName, sensor_data::Rasp0SensorData& rasp0SendorData,
                     sensor_data::Rasp3BSensorData& rasp3BSendorData);
    void closeSession(sensor_data::Rasp0SensorData& rasp0SendorData,
                      sensor_data::Rasp3BSensorData& rasp3BSendorData);
};

} // namespace tool

#endif // SERIALIZATOR_H
