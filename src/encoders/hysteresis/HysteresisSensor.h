
#pragma once


#include "Arduino.h"
#include "common/base_classes/FOCMotor.h"
#include "common/base_classes/Sensor.h"

class HysteresisSensor : public Sensor {
public:
    HysteresisSensor(Sensor& wrapped, float amount = 0.0125f);

    angle_type getSensorAngle() override;

    void init() override;

    angle_type _amount;
protected:
    Sensor& _wrapped;
    angle_type _window;

};

