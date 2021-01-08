#ifndef SERIALIZATOR_H
#define SERIALIZATOR_H

#include <QFile>
#include <rasp0_sensor_data.h>
#include <rasp3b_sensor_data.h>
#include <memory>

namespace tool {

class Serializator
{
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

private:
    std::unique_ptr<std::FILE, decltype(&std::fclose)> sessionFile;
};

} // namespace tool

#endif // SERIALIZATOR_H
