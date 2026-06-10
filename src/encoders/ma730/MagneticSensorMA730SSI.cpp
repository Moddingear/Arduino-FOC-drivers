#include "./MagneticSensorMA730SSI.h"
#include "common/foc_utils.h"
#include "common/time_utils.h"

MagneticSensorMA730SSI::MagneticSensorMA730SSI(SPISettings settings) : settings(settings) {
    #ifdef INTEGER_ANGLE
    steps_per_revolution = MA730_CPR;
    #endif
}


MagneticSensorMA730SSI::~MagneticSensorMA730SSI() {

}

void MagneticSensorMA730SSI::init(SPIClass* _spi) {
    this->spi=_spi;
    this->Sensor::init();
}

// check 40us delay between each read?
angle_type MagneticSensorMA730SSI::getSensorAngle() {
    angle_type angle_data = readRawAngleSSI();
    #ifdef INTEGER_ANGLE
    angle_data = ( angle_data / (float)MA730_CPR ) * _2PI;
    #endif
    // return the shaft angle
    return angle_data;
}


uint16_t MagneticSensorMA730SSI::readRawAngleSSI() {
    spi->beginTransaction(settings);
    uint16_t value = spi->transfer16(0x0000);
    //uint16_t parity = spi->transfer(0x00);
    spi->endTransaction();
    return (value<<1); //>>1)&0x3FFF;
}; // 14bit angle value
