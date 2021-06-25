#pragma once
#include "DigitalPort.h"
class Keyboard : public InPort {
public:
	Keyboard(int length) : InPort(length) {}

protected:
	byte read_bit(int index) override;
	int scan_all_bit(int threshold) override;
	void start_scanner() override;
	void on_input_active(int index) override;
};

