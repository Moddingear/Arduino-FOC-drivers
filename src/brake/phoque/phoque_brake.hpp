#pragma once

#if defined(ARDUINO_PHOQUE) 
#include "brake/stm32/stm32_brake.hpp"
#if defined(HAL_DAC_MODULE_ENABLED) && defined(HAL_COMP_MODULE_ENABLED)

class phoque_brake : public stm32_brake
{
public:
    phoque_brake();
    void init(float threshold);
    HAL_STATUS_TYPE set_threshold(float trigger_voltage);
};

#endif
#endif