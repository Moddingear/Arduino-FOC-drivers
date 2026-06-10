
#include "./HysteresisSensor.h"


HysteresisSensor::HysteresisSensor(Sensor& wrapped, float amount) : _amount(amount), _wrapped(wrapped) {
    // empty
    #ifdef INTEGER_ANGLE
    steps_per_revolution = wrapped.steps_per_revolution;
    _amount = steps_per_revolution * amount / _2PI;
    #endif
};


void HysteresisSensor::init() {
    _wrapped.update();
    _window = _wrapped.getMechanicalAngle();
    this->Sensor::init();
};

angle_type HysteresisSensor::getSensorAngle() {
    _wrapped.update();
    angle_type raw = _wrapped.getMechanicalAngle();

    angle_type d_angle = raw - _window;
    #ifdef INTEGER_ANGLE
    #define FULL_REV steps_per_revolution
    if(abs(d_angle) > steps_per_revolution/2) {
    #else
    #define FULL_REV _2PI
    if(abs(d_angle) > (0.8f*_2PI)) {
    #endif
        if (d_angle > 0) {
            if (raw < (FULL_REV - _amount + _window)) {
                _window = _normalizeAngle(raw + _amount);
                return raw;
            }
        } else {
            if (raw > (_amount - (FULL_REV - _window))) {
                _window = _normalizeAngle(raw - _amount);
                return raw;
            }
        }
    }
    else  {
        if (raw > (_window + _amount)) {
            _window = _normalizeAngle(raw - _amount);
            return raw;
        }
        if (raw < (_window - _amount)) {
            _window = _normalizeAngle(raw + _amount);
            return raw;
        }
    }
    return angle_prev; // no change
};

