
#include "./MagneticSensorTLE5012B.h"

#if defined(ARDUINO_ARCH_STM32) && !defined(USE_HALV2_DRIVER)

MagneticSensorTLE5012B::MagneticSensorTLE5012B(int data, int sck, int nCS) : TLE5012B(data, sck, nCS) { };
MagneticSensorTLE5012B::~MagneticSensorTLE5012B(){ };

void MagneticSensorTLE5012B::init() {
    this->TLE5012B::init();
    this->Sensor::init();
};

float MagneticSensorTLE5012B::getSensorAngle() {
    return getCurrentAngle();
};

#endif
