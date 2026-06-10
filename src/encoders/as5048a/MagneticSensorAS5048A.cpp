
#include "./MagneticSensorAS5048A.h"
#include "common/foc_utils.h"
#include "common/time_utils.h"

MagneticSensorAS5048A::MagneticSensorAS5048A(int nCS, bool fastMode, SPISettings settings) : AS5048A(settings, nCS), fastMode(fastMode) {
    #ifdef INTEGER_ANGLE
    steps_per_revolution = AS5048A_CPR;
    #endif
}

MagneticSensorAS5048A::~MagneticSensorAS5048A(){ 

}
void MagneticSensorAS5048A::init(SPIClass* _spi) {
    this->AS5048A::init(_spi);
    this->Sensor::init();
}

angle_type MagneticSensorAS5048A::getSensorAngle() {
    angle_type angle_data = readRawAngle();
    if (!fastMode) // read again to ensure current value
        angle_data = readRawAngle();

    #ifndef INTEGER_ANGLE
    angle_data = ( angle_data / (float)AS5048A_CPR ) * _2PI;
    #endif
    // return the shaft angle
    return angle_data;
}
