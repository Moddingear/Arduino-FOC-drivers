#pragma once

#if defined(ARDUINO_PHOQUE3)

#include <current_sense/phoque/Phoque_CurrentSense.hpp>

class Phoque3_CurrentSense : public Phoque_CurrentSense
{
	//Current sense for the Phoque2 board
	//for best performance, center modulation should be off
public:
	Phoque3_CurrentSense(float shunt_resistor, float gain, bool read_bemf=false);
	Phoque3_CurrentSense(float mVpA, bool read_bemf=false);
	virtual ~Phoque3_CurrentSense();

	virtual uint16_t readRaw(const int pin) const override;

private:

	virtual int get_adc1_important_duration() override;
	virtual int get_adc2_important_duration() override;
	virtual int ADC1_Init(ADC_HANDLE_TYPE* hadc1, uint8_t sequence_length) override;
	virtual int ADC2_Init(ADC_HANDLE_TYPE* hadc2, uint8_t sequence_length) override;

	void clear_currents() final;
};

#endif