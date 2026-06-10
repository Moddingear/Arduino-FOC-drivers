#include "./MagneticSensorMA735SSI.h"
#include "common/foc_utils.h"
#include "common/time_utils.h"

MagneticSensorMA735SSI::MagneticSensorMA735SSI(SPISettings settings) : settings(settings) {

    #ifdef INTEGER_ANGLE
    steps_per_revolution = MA735_16BIT;
    #endif
}


MagneticSensorMA735SSI::~MagneticSensorMA735SSI() {

}

void MagneticSensorMA735SSI::init(SPIClass* _spi) {
    this->spi=_spi;
    this->Sensor::init();
}

// check 40us delay between each read?
angle_type MagneticSensorMA735SSI::getSensorAngle() {
    angle_type angle_data = readRawAngleSSI();
    #ifndef INTEGER_ANGLE
    angle_data = ( angle_data / (float)MA735_16BIT ) * _2PI;//It doesn't matter that it is divided by 65536, because the raw angle fills empty data bits with empty zeros so sensor resolution doesn't affect angle calculation
    #endif
    // return the shaft angle
    return angle_data;
}


uint16_t MagneticSensorMA735SSI::readRawAngleSSI() {
    spi->beginTransaction(settings);
    uint16_t value = spi->transfer16(0x0000);
    //uint16_t parity = spi->transfer(0x00);
    spi->endTransaction();
    return (value<<1); //>>1)&0x3FFF;
}; // 9-13bit angle value
