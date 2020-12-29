#ifndef RASP3BSENSORDATA_H
#define RASP3BSENSORDATA_H

#include<mutex>

namespace sensor_data {

class Rasp3BSensorData
{
private:
    std::mutex mtx;

    double temperature = 0;
    double humidity = 0;
    double tvoc = 0;
    double co2 = 0;
    int currentMeasFreq = 0; //seconds
public:
    Rasp3BSensorData() = default;
    ~Rasp3BSensorData() = default;

    double getTemperature();
    void setTemperature(double value);
    double getHumidity();
    void setHumidity(double value);
    double getTvoc();
    void setTvoc(double value);
    double getCo2();
    void setCo2(double value);
    int getCurrentMeasFreq();
    void setCurrentMeasFreq(int value);
};

} // namespace sensor_data

#endif // RASP3BSENSORDATA_H
