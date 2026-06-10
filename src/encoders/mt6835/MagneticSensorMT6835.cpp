
#include "MagneticSensorMT6835.h"
#include "common/foc_utils.h"


MagneticSensorMT6835::MagneticSensorMT6835(int nCS, SPISettings settings) : Sensor(), MT6835(settings, nCS) {
    #ifdef INTEGER_ANGLE
    steps_per_revolution = MT6835_CPR;
    #endif
};


MagneticSensorMT6835::~MagneticSensorMT6835() {
    // nix
};


angle_type MagneticSensorMT6835::getSensorAngle() {
    #ifdef INTEGER_ANGLE
    return getCurrentAngle();
    #else
    return getCurrentAngle() * _2PI / (float)MT6835_CPR;
    #endif
};


void MagneticSensorMT6835::init(SPIClass* _spi) {
    this->MT6835::init(_spi);
    this->Sensor::init();
};

