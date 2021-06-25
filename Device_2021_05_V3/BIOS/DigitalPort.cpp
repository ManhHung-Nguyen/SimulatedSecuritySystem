#include "DigitalPort.h"

#ifdef WIN32
void pinMode(int pin, int mode) {}
#endif // WIN32

DigitalPort::DigitalPort(int length)
	: Buffer(length) {
	pins = 0;
}

// Đặt pin mode và gắn chân tín hiệu vào tập các pins của port
void DigitalPort::SetPinMode(int pin, int mode) {

	get_pins();
	//digitalWrite(pin, 0);
	pinMode(pin, mode);

	pins[Position()] = pin;
	it++;
}

byte* DigitalPort::get_pins()
{
	if (pins == 0) {
		Mapping(System::DRAM.Malloc(capacity << 1)).Reset();
		pins = data + capacity;
	}
	return pins;
}

void DigitalPort::write_bit(int index) {
	digitalWrite(pins[index], data[index] & 1);
}

byte DigitalPort::read_bit(int index) {
	return digitalRead(pins[index]);
}

void DigitalPort::Write(int start, int length) {
	if (length == 0) { length = capacity; }
	for (int i = start; i < length; i++) {
		write_bit(i);
	}
}

int DigitalPort::Read(int start, int length) {
	int v = 0;
	if (length == 0) { length = capacity; }
	for (int i = start; i < length; i++) {
		int a = read_bit(i);
		v |= (a << i);
	}
	return v;
}

void OutPort::on_tick() {
	for (int i = 0; i < capacity; i++) {
		byte& bit = data[i];
		if (bit & 0x80) {
			bit ^= 1;
			write_bit(i);
		}
	}
}

void OutPort::StopBlink() {
	Counter::Reset();
	for (int i = 0; i < capacity; i++) {
		byte& bit = data[i];
		if (bit & 0x80) {
			bit = 1;
			write_bit(i);
		}
	}
}

int InPort::scan_all_bit(int threshold) {
	int v = 0;
	for (int i = 0; i < capacity && !is_busy; i++) {
		if ((data[i] += read_bit(i)) > threshold) {
			on_input_active(i);
			v |= (1 << i);
		}
	}
	return v;
}
void InPort::Scan(int threshold) {

	if (is_busy) { return; }
	start_scanner();
	int result = scan_all_bit(threshold);
	if (result) {
		interrupt(result);
	}
}
int InPort::GetValue() {
	int v = 0;
	for (int i = 0; i < capacity; i++) {
		if (data[i]) {
			v |= (1 << i);
		}
	}
	return v;
}

//int InPort::GetIndex(byte threshold) {
//	int m = 0;
//	for (int i = 0; i < capacity; i++) {
//		byte b = data[i];
//		if (b > data[m]) {
//			m = i;
//		}
//	}
//	if (data[m] < threshold) m = -1;
//	Buffer::Reset();
//	return m;
//}
