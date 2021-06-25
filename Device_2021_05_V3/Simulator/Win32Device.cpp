

#include "Simulator.h"
#include "../Device/Device.h"

int inputs = 0;
int beam = 0;

int digitalRead(int pin) {
	int i = pin - 100;
	return ((inputs & (1 << i)) == 0 ? 0 : 1);
}

int Beam::GetValue()
{
	if (beam == value) {
		return -1;
	}
	return value = beam;
}

int Sensors::get_beam() {
	return beam;
}

void NET() {
	
}
void ON_INPUT() {
	inputs = _args[0];
}
void ON_BEAM() {
	beam = _args[0];
}
void Device::init_scanner() {
	Simulator::Receive();
}
void Device::on_power(bool on) {

	_eu.Insert("NET", NET);
	_eu.Insert("INP", ON_INPUT);
	_eu.Insert("BEAM", ON_BEAM);

	int len = Device::LEDS.Capacity();
	for (int i = 0; i < len; i++) {
		Device::LEDS.SetPinMode(i, 0);
	}
	Device::LEDS.Write();
	for (int i = 0; i < Device::RELAYS.Capacity(); i++) {
		Device::RELAYS.SetPinMode(i + len, 0);
	}
	Device::RELAYS.Write();

	for (int i = 0, k = i + 100; i < Device::INPUTS.Capacity(); i++) {
		Device::INPUTS.SetPinMode(k++, 1);
	}
}

