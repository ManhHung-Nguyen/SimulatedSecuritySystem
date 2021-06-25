#pragma once
#include "../BIOS/DigitalPort.h"

class Sensors : public InPort {
	int value;
protected:
	int scan_all_bit(int thresold) override;
	int get_beam();
public:
	Sensors() : InPort(4), value(0) {}
	int GetValue() override {
		int v = InPort::GetValue();
		if (v == value) {
			return -1;
		}
		return value = v;
	}
};

class Beam {
	int value;
public:
	Beam() : value(0) {}
	int GetValue();
	//bool CheckAlarm();
};
