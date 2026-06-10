
#include "MagneticSensorKTH7812.h"


MagneticSensorKTH7812::MagneticSensorKTH7812(int nCS, bool withcrc, bool fastmode, SPISettings settings) : Sensor(), KTH7812(settings, nCS, fastmode, withcrc) {
    #ifdef INTEGER_ANGLE
    steps_per_revolution = KTH7812_CPR;
    #endif
};


MagneticSensorKTH7812::~MagneticSensorKTH7812() {
    // nix
};


angle_type MagneticSensorKTH7812::getSensorAngle() {
    #ifdef INTEGER_ANGLE
    if (checkcrc)
    {
        return readRawAngle12WithCRC();
    }
    else
    {
        return readRawAngle16();
    }
    #else
    return getCurrentAngle();
    #endif
};


void MagneticSensorKTH7812::init(SPIClass* _spi) {
    this->KTH7812::init(_spi);
    this->Sensor::init();
};

