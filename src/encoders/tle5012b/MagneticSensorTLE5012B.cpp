
#include "./MagneticSensorTLE5012B.h"

#if defined(_STM32_DEF_)

MagneticSensorTLE5012B::MagneticSensorTLE5012B(int data, int sck, int nCS) : TLE5012B(data, sck, nCS) {
    #ifdef INTEGER_ANGLE
    steps_per_revolution = TLE5012B_CPR;
    #endif
 };
MagneticSensorTLE5012B::~MagneticSensorTLE5012B(){ };

void MagneticSensorTLE5012B::init() {
    this->TLE5012B::init();
    this->Sensor::init();
};

angle_type MagneticSensorTLE5012B::getSensorAngle() {
    #ifdef INTEGER_ANGLE
    return readRawAngle();
    #else
    return getCurrentAngle();
    #endif
};

#endif
