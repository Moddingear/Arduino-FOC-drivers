#include "./MagneticSensorMA730.h"
#include "common/foc_utils.h"
#include "common/time_utils.h"

MagneticSensorMA730::MagneticSensorMA730(int nCS, SPISettings settings) : MA730(settings, nCS) {
    #ifdef INTEGER_ANGLE
    steps_per_revolution = MA730_CPR;
    #endif
}


MagneticSensorMA730::~MagneticSensorMA730(){ 

}


void MagneticSensorMA730::init(SPIClass* _spi) {
    this->MA730::init(_spi);
    this->Sensor::init();
}


angle_type MagneticSensorMA730::getSensorAngle() {
    angle_type angle_data = readRawAngle();
    #ifndef INTEGER_ANGLE
    angle_data = ( angle_data / (float)MA730_CPR) * _2PI;
    #endif
    // return the shaft angle
    return angle_data;
}
