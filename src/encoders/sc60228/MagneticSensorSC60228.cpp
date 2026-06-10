
#include "./MagneticSensorSC60228.h"
#include "common/foc_utils.h"
#include "common/time_utils.h"

MagneticSensorSC60228::MagneticSensorSC60228(int nCS, SPISettings settings) : SC60228(settings, nCS){
    #ifdef INTEGER_ANGLE
    steps_per_revolution = SC60228_CPR;
    #endif
};
MagneticSensorSC60228::~MagneticSensorSC60228(){ };



angle_type MagneticSensorSC60228::getSensorAngle(){
    SC60228Angle angle_data = readRawAngle();
    #ifdef INTEGER_ANGLE
    return angle_data.angle;
    #else
    float result = ( angle_data.angle / (float)SC60228_CPR ) * _2PI;
    return result;
    #endif
};



void MagneticSensorSC60228::init(SPIClass* _spi){
    this->SC60228::init(_spi);
    this->Sensor::init();
};