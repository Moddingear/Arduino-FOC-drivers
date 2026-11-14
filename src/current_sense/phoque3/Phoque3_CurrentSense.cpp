#if defined(ARDUINO_PHOQUE3)

#include "Phoque3_CurrentSense.hpp"
#include "communication/SimpleFOCDebug.h"
#include "current_sense/hardware_specific/stm32/stm32_adc_utils.h"



Phoque3_CurrentSense::Phoque3_CurrentSense(float _shunt_resistor, float _gain, bool _read_bemf)
	:Phoque_CurrentSense(_shunt_resistor, _gain, _read_bemf)
{
	pinA = A_CURRU;
	pinB = A_CURRV;
	pinC = A_CURRW;
}

Phoque3_CurrentSense::Phoque3_CurrentSense(float mVpA, bool _read_bemf)
	:Phoque_CurrentSense(mVpA, _read_bemf)
{
	pinA = A_CURRU;
	pinB = A_CURRV;
	pinC = A_CURRW;
}

Phoque3_CurrentSense::~Phoque3_CurrentSense()
{
}

#define SAMPLETIME_IMPORTANT HAL_ADC_SAMPLING_TIME_5CYCLES
#define SAMPLETIME_PERIPHERAL HAL_ADC_SAMPLING_TIME_48CYCLES

int Phoque3_CurrentSense::get_adc1_important_duration()
{
	return (read_bemf ? 2:0) * get_conversion_duration(5) + 5;
}

int Phoque3_CurrentSense::get_adc2_important_duration()
{
	return (read_bemf ? 2:1) * get_conversion_duration(5) + 5;
}


int Phoque3_CurrentSense::ADC1_Init(ADC_HANDLE_TYPE* hadc1, uint8_t sequence_length)
{
	hal_adc_channel_config_t sConfig = {
		.group = HAL_ADC_GROUP_REGULAR,
		.sequencer_rank = 0,
		.sampling_time = SAMPLETIME_IMPORTANT,
		.input_mode = HAL_ADC_IN_SINGLE_ENDED,
	};
	hal_adc_channel_t channel;

	Phoque_CurrentSense::ADC1_Init(hadc1, 3+read_bemf*2+sequence_length);

	
	if (read_bemf)
	{
		// Configure Regular Channel (PA4 / BEMFU / Phase U)
		channel = _getADCChannel(analogInputToPinName(A_BEMFU), ADC1); //ADC_CHANNEL_4;
		sConfig.sequencer_rank++;
		if (HAL_ADC_SetConfigChannel(hadc1, channel, &sConfig) != HAL_OK)
		{
			SimpleFOCDebug::println("HAL_ADC_ConfigChannel failed!");
		}

		// Configure Regular Channel (PA5 / BEMFV / Phase V)
		channel = _getADCChannel(analogInputToPinName(A_BEMFV), ADC1); //ADC_CHANNEL_5;
		sConfig.sequencer_rank++;
		if (HAL_ADC_SetConfigChannel(hadc1, channel, &sConfig) != HAL_OK)
		{
			SimpleFOCDebug::println("HAL_ADC_ConfigChannel failed!");
		}

		// Configure Regular Channel (PA7 / BEMFW / Phase W)
		channel = _getADCChannel(analogInputToPinName(A_BEMFW), ADC1); //ADC_CHANNEL_7;
		sConfig.sequencer_rank++;
		if (HAL_ADC_SetConfigChannel(hadc1, channel, &sConfig) != HAL_OK)
		{
			SimpleFOCDebug::println("HAL_ADC_ConfigChannel failed!");
		}
	}
	else
	{
		channel = _getADCChannel(analogInputToPinName(A_CURRU), ADC1); //ADC_CHANNEL_1;
		sConfig.sequencer_rank++;
		if (HAL_ADC_SetConfigChannel(hadc1, channel, &sConfig) != HAL_OK)
		{
			SimpleFOCDebug::println("HAL_ADC_ConfigChannel failed!");
		}
	}
	

	//******************************************************************
	// Aux analog readings
	// Configure Regular Channel (PA6, potentiometer)
	channel = _getADCChannel(analogInputToPinName(A_POTENTIOMETER), ADC1); //ADC_CHANNEL_6;
	sConfig.sequencer_rank++;
	sConfig.sampling_time = SAMPLETIME_PERIPHERAL;
	if (HAL_ADC_SetConfigChannel(hadc1, channel, &sConfig) != HAL_OK)
	{
		SimpleFOCDebug::println("HAL_ADC_ConfigChannel failed!");
	}

	// Configure Regular Channel (PA0 / Bus voltage monitor)
	channel = _getADCChannel(analogInputToPinName(A_VBUS), ADC1); //ADC_CHANNEL_0;
	sConfig.sequencer_rank++;
	if (HAL_ADC_SetConfigChannel(hadc1, channel, &sConfig) != HAL_OK)
	{
		SimpleFOCDebug::println("HAL_ADC_ConfigChannel failed!");
	}
	return sConfig.sequencer_rank;
}

int Phoque3_CurrentSense::ADC2_Init(ADC_HANDLE_TYPE* hadc2, uint8_t sequence_length)
{
	hal_adc_channel_config_t sConfig = {
		.group = HAL_ADC_GROUP_REGULAR,
		.sequencer_rank = 0,
		.sampling_time = SAMPLETIME_IMPORTANT,
		.input_mode = HAL_ADC_IN_SINGLE_ENDED,
	};
	hal_adc_channel_t channel;

	Phoque_CurrentSense::ADC2_Init(hadc2, 3+read_bemf+sequence_length);

	if (read_bemf)
	{
		/** Configure Regular Channel (PA1 / phase U current)
		*/
		channel = _getADCChannel(analogInputToPinName(A_CURRU), ADC2); //ADC_CHANNEL_1;
		sConfig.sequencer_rank++;
		if (HAL_ADC_SetConfigChannel(hadc2, channel, &sConfig) != HAL_OK)
		{
			SimpleFOCDebug::println("HAL_ADC_ConfigChannel failed!");
		}
	}
	

	// Configure Regular Channel (PA2 / phase V current)
	channel = _getADCChannel(analogInputToPinName(A_CURRV), ADC2); //ADC_CHANNEL_2;
	sConfig.sequencer_rank++;
	if (HAL_ADC_SetConfigChannel(hadc2, channel, &sConfig) != HAL_OK)
	{
		SimpleFOCDebug::println("HAL_ADC_ConfigChannel failed!");
	}
	// Configure Regular Channel (PA3 / phase W current)
	channel = _getADCChannel(analogInputToPinName(A_CURRW), ADC2); //ADC_CHANNEL_3;
	sConfig.sequencer_rank++;
	if (HAL_ADC_SetConfigChannel(hadc2, channel, &sConfig) != HAL_OK)
	{
		SimpleFOCDebug::println("HAL_ADC_ConfigChannel failed!");
	}

	// Configure Regular Channel (PB0 / Temperature sensor)
	channel = _getADCChannel(analogInputToPinName(A_TEMPERATURE), ADC2); //ADC_CHANNEL_6;
	sConfig.sequencer_rank++;
	sConfig.sampling_time = SAMPLETIME_PERIPHERAL;
	if (HAL_ADC_SetConfigChannel(hadc2, channel, &sConfig) != HAL_OK)
	{
		SimpleFOCDebug::println("HAL_ADC_ConfigChannel failed!");
	}
	return sConfig.sequencer_rank;
}

inline uint16_t Phoque3_CurrentSense::readRaw(const int pin) const
{
	switch (pin)
	{
	case A_CURRU:
	case -1:
		if (read_bemf)
		{
			return adc2_buffer[0];
		}
		else
		{
			return adc1_buffer[0];
		}
	case A_CURRV:
	case -2:
		return adc2_buffer[0+read_bemf];
	case A_CURRW:
	case -3:
		return adc2_buffer[1+read_bemf];

	case A_BEMFU:
		return adc1_buffer[0];
	case A_BEMFV:
		return adc1_buffer[1];
	case A_BEMFW:
		return adc1_buffer[2];

	case A_POTENTIOMETER:
		return adc1_buffer[1+read_bemf*2];
	case A_TEMPERATURE:
		return adc2_buffer[2+read_bemf];
	case A_VBUS:
		return adc1_buffer[2+read_bemf*2];
	default:
		return 0;
	}
}

inline void Phoque3_CurrentSense::clear_currents()
{
	adc2_buffer[0] = UINT16_MAX;
	adc2_buffer[1] = UINT16_MAX;
	if (read_bemf)
	{
		adc2_buffer[2] = UINT16_MAX;
	}
	else
	{
		adc1_buffer[0] = UINT16_MAX;
	}
}

#endif