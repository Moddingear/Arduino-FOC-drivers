

#include "./MagneticSensorAS5600.h"
#include "common/foc_utils.h"

MagneticSensorAS5600::MagneticSensorAS5600(uint8_t _address) : AS5600(_address) {
  #ifdef INTEGER_ANGLE
  steps_per_revolution = AS5600_CPR;
  #endif
};
MagneticSensorAS5600::~MagneticSensorAS5600() {};

void MagneticSensorAS5600::init(TwoWire* wire) {
  AS5600::init(wire);
  Sensor::init();
};


angle_type MagneticSensorAS5600::getSensorAngle() {
    uint16_t raw = angle();
    #ifdef INTEGER_ANGLE
    return raw;
    #else
    return raw / AS5600_CPR * _2PI;
    #endif
};