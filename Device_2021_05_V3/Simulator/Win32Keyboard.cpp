#include "../BIOS/BIOS.h"
#include "Simulator.h"

#define KEYS_COUNT 16

#ifdef WIN32
void Keyboard::start_scanner() {
	byte* keyCodes = get_pins();
	if (keyCodes[0] == 0) {
		int i = 0;
		for (; i < 10; i++) {
			keyCodes[i] = '0' + i; //48 49 50 51 52 53 54 55 56 57
		}
		keyCodes[i++] = VK_CONTROL; //17
		keyCodes[i++] = VK_TAB; //9
		keyCodes[i++] = VK_UP; //38
		keyCodes[i++] = VK_DOWN; //40
		keyCodes[i++] = 8;
		keyCodes[i++] = 13;
	}
}
int Keyboard::scan_all_bit(int threshold) {
	InPort::scan_all_bit(threshold);
	return 0;
}
byte Keyboard::read_bit(int index) {
	SHORT v = GetAsyncKeyState(get_pins()[index]);
	return (v && (v & 0x8000) ? 1 : 0);
}
void Keyboard::on_input_active(int index) {
	interrupt(index);
}
#endif // WIN32
