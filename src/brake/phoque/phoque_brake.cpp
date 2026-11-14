

#if defined(ARDUINO_PHOQUE) 
#include "phoque_brake.hpp"
#if !defined(HAL_DAC_MODULE_ENABLED)
#pragma message("DAC module missing for brake")
#endif
#if !defined(HAL_COMP_MODULE_ENABLED)
#pragma message("COMP module missing for brake")
#endif
#if defined(HAL_DAC_MODULE_ENABLED) && defined(HAL_COMP_MODULE_ENABLED)

#include "pins_arduino.h"

phoque_brake::phoque_brake()
	:stm32_brake(digitalPinToPinName(A_VBUS), digitalPinToPinName(BRAKE_RESISTOR), BRAKE_AF)
{

}

void phoque_brake::init(float threshold)
{
	#ifdef STM32G4
	#ifdef DAC1
	if (BRAKE_DAC == DAC1)
	{
		__HAL_RCC_DAC1_CLK_ENABLE();
	}
	#endif
	#ifdef DAC2
	if (BRAKE_DAC == DAC2)
	{
		__HAL_RCC_DAC2_CLK_ENABLE();
	}
	#endif
	#ifdef DAC3
	if (BRAKE_DAC == DAC3)
	{
		__HAL_RCC_DAC3_CLK_ENABLE();
	}
	#endif
	#ifdef DAC4
	if (BRAKE_DAC == DAC4)
	{
		__HAL_RCC_DAC4_CLK_ENABLE();
	}
	#endif
	
	hdac.Instance = BRAKE_DAC;
	dac_channel = BRAKE_DAC_CHAN;
	hcomp.Instance = BRAKE_COMP;
	hcomp.Init = {
		.InputPlus = BRAKE_COMP_PLUS,
		.InputMinus = BRAKE_COMP_MINUS,
		.Hysteresis = COMP_HYSTERESIS_10MV,
		.OutputPol = COMP_OUTPUTPOL_NONINVERTED,
		.BlankingSrce = COMP_BLANKINGSRC_NONE,
		.TriggerMode = COMP_TRIGGERMODE_NONE,
	};
	start_brake(threshold / VBUS_MUL_FACTOR / 3.3f);
	#endif
	#ifdef STM32C5
	HAL_RCC_DAC1_EnableClock();
	HAL_DAC_Init(&hdac, BRAKE_DAC);
	dac_channel = BRAKE_DAC_CHAN;

	hal_comp_t comp_instance = BRAKE_COMP;
	hal_comp_config_t comp_config = {
		.power_mode = HAL_COMP_POWER_MODE_HIGH_SPEED,
		.input_plus = BRAKE_COMP_PLUS,
		.input_minus = BRAKE_COMP_MINUS,
		.input_hysteresis = HAL_COMP_INPUT_HYSTERESIS_LOW,
		.output_polarity = HAL_COMP_OUTPUT_POLARITY_NONINVERTED,
	};
	HAL_COMP_Init(&hcomp, comp_instance);
	HAL_COMP_SetConfig(&hcomp, &comp_config);
	#endif
}

HAL_STATUS_TYPE phoque_brake::set_threshold(float trigger_voltage)
{
	return set_raw_threshold(trigger_voltage / VBUS_MUL_FACTOR / 3.3f);
}

#endif
#endif