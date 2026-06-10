#include "./MagneticSensorMA735.h"
#include "common/foc_utils.h"
#include "common/time_utils.h"

MagneticSensorMA735::MagneticSensorMA735(int nCS, SPISettings settings) : MA735(settings, nCS) {
    #ifdef INTEGER_ANGLE
    steps_per_revolution = MA735_16BIT;
    #endif
}


MagneticSensorMA735::~MagneticSensorMA735(){ 

}


void MagneticSensorMA735::init(SPIClass* _spi) {
    this->MA735::init(_spi);
    this->Sensor::init();
}


angle_type MagneticSensorMA735::getSensorAngle() {
    angle_type angle_data = readRawAngle();
    #ifndef INTEGER_ANGLE
    angle_data = ( angle_data / (float)MA735_16BIT) * _2PI;//It doesn't matter that it is divided by 65536, because the raw angle fills empty data bits with empty zeros so sensor resolution doesn't affect angle calculation
    #endif
    // return the shaft angle
    return angle_data;
}
