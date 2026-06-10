
#include "MagneticSensorMT6826S.h"
#include "common/foc_utils.h"


MagneticSensorMT6826S::MagneticSensorMT6826S(int nCS, SPISettings settings) : Sensor(), MT6826S(settings, nCS) {
    #ifdef INTEGER_ANGLE
    steps_per_revolution = MT6826S_CPR;
    #endif
};


MagneticSensorMT6826S::~MagneticSensorMT6826S() {
    // nix
};


angle_type MagneticSensorMT6826S::getSensorAngle() {
    #ifdef INTEGER_ANGLE
    return getCurrentAngle();
    #else
    return getCurrentAngle() * _2PI / (float)MT6826S_CPR;
    #endif
};


void MagneticSensorMT6826S::init(SPIClass* _spi) {
    this->MT6826S::init(_spi);
    this->Sensor::init();
};

