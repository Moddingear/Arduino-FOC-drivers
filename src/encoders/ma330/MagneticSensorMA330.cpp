#include "./MagneticSensorMA330.h"
#include "common/foc_utils.h"
#include "common/time_utils.h"

MagneticSensorMA330::MagneticSensorMA330(int nCS, SPISettings settings) : MA330(settings, nCS) {
    #ifdef INTEGER_ANGLE
    steps_per_revolution = MA330_CPR;
    #endif
}


MagneticSensorMA330::~MagneticSensorMA330(){ 

}


void MagneticSensorMA330::init(SPIClass* _spi) {
    this->MA330::init(_spi);
    this->Sensor::init();
}


angle_type MagneticSensorMA330::getSensorAngle() {
    angle_type angle_data = readRawAngle();
    #ifndef INTEGER_ANGLE
    angle_data = ( angle_data / (float)MA330_CPR) * _2PI;
    #endif
    // return the shaft angle
    return angle_data;
}
