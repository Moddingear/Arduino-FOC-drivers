
#include "./MagneticSensorAS5047.h"
#include "common/foc_utils.h"
#include "common/time_utils.h"

MagneticSensorAS5047::MagneticSensorAS5047(int nCS, bool fastMode, SPISettings settings) : AS5047(settings, nCS), fastMode(fastMode) {
    #ifdef INTEGER_ANGLE
    steps_per_revolution = AS5047_CPR;
    #endif
}


MagneticSensorAS5047::~MagneticSensorAS5047(){ 

}


void MagneticSensorAS5047::init(SPIClass* _spi) {
    this->AS5047::init(_spi);
    this->Sensor::init();
}


angle_type MagneticSensorAS5047::getSensorAngle() {
    angle_type angle_data = readRawAngle();
    if (!fastMode) // read again to ensure current value
        angle_data = readRawAngle();
    #ifdef INTEGER_ANGLE
    angle_data = ( angle_data / (float)AS5047_CPR) * _2PI;
    #endif
    // return the shaft angle
    return angle_data;
}
