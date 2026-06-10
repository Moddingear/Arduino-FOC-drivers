
#include "./MagneticSensorAS5047U.h"
#include "common/foc_utils.h"
#include "common/time_utils.h"

MagneticSensorAS5047U::MagneticSensorAS5047U(int nCS, bool fastMode, SPISettings settings) : AS5047U(settings, nCS), fastMode(fastMode) {
    #ifdef INTEGER_ANGLE
    steps_per_revolution = AS5047U_CPR;
    #endif
}


MagneticSensorAS5047U::~MagneticSensorAS5047U(){ 

}


void MagneticSensorAS5047U::init(SPIClass* _spi) {
    this->AS5047U::init(_spi);
    this->Sensor::init();
}


angle_type MagneticSensorAS5047U::getSensorAngle() {
    angle_type angle_data = readRawAngle();
    if (!fastMode) // read again to ensure current value
        angle_data = readRawAngle();
    #ifndef INTEGER_ANGLE
    angle_data = ( angle_data / (float)AS5047U_CPR) * _2PI;
    #endif
    // return the shaft angle
    return angle_data;
}
