#include "./MagneticSensorAEAT8800Q24.h"
#include "common/foc_utils.h"
#include "common/time_utils.h"

MagneticSensorAEAT8800Q24::MagneticSensorAEAT8800Q24(int nCS, int pinNSL, SPISettings spiSettings, SPISettings ssiSettings) : AEAT8800Q24(nCS, pinNSL, spiSettings, ssiSettings) {
    #ifdef INTEGER_ANGLE
    steps_per_revolution = AEAT8800Q24_CPR;
    #endif
};


MagneticSensorAEAT8800Q24::~MagneticSensorAEAT8800Q24(){ 
};


void MagneticSensorAEAT8800Q24::init(SPIClass* _spi) {
    this->AEAT8800Q24::init(_spi);
    this->Sensor::init();
};


angle_type MagneticSensorAEAT8800Q24::getSensorAngle() {
    angle_type angle_data = readRawAngle();
    #ifdef INTEGER_ANGLE
    return angle_data;
    #else
    angle_data = ( angle_data / (float)AEAT8800Q24_CPR) * _2PI;
    // return the shaft angle
    return angle_data;
    #endif
};
