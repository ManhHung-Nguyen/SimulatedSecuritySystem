#pragma once
#include "../System/System.h"
#include "BaseIO.h"

#ifdef WIN32
void digitalWrite(int pin, int val);
int digitalRead(int pin);
#endif // WIN32

class DigitalPort : public Buffer, public BaseIO {
	byte* pins;
protected:
	byte* get_pins();
	virtual void write_bit(int index);
	virtual byte read_bit(int index);
public:
	DigitalPort(int length);
	void SetPinMode(int pin, int mode);
public:
	void SetBit(int index, byte value = 1) {
		(*this)[index] = (value & 1);
		write_bit(index);
	}
	void Write(int start = 0, int length = 0);
	int Read(int start = 0, int length = 0);
};

class OutPort : public DigitalPort, public Counter {
protected:
	void on_tick() override;
public:
	OutPort(int length) : DigitalPort(length) {}
public:
	void SetBlink(int index) {
		(*this)[index] = 0x81;
		write_bit(index);

		if (!is_running()) {
			Counter::Reset(MILISECOND_LIMIT / 2);
		}
	}
	void StopBlink();
};

class InPort : public DigitalPort {
protected:
	virtual void start_scanner() {}
	virtual int scan_all_bit(int threshold);
	virtual void on_input_active(int index) {}
public:
	InPort(int length) : DigitalPort(length) {}
public:
	void Refresh() {
		Buffer::Reset();
		is_busy = false;
	}
	virtual void Scan(int threshold);
	virtual int GetValue();
	//virtual int GetIndex(byte threshold);
};
