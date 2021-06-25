#include "../BIOS/Keyboard.h"

#ifdef ARDUINO

byte analogValues[] = { 11, 105, 101, 96, 69, 75, 81, 62, 55, 47, 0, 21, 91, 86, 39, 31 };
short keyboard_input = 1000;
void Keyboard::start_scanner() {
    keyboard_input = analogRead(A7);
}
int Keyboard::scan_all_bit(int threshold) {
    if (keyboard_input > 500) return 0;
    for (int i = 0; i < capacity; i++) {
        short e = (analogValues[i] << 2) - keyboard_input;
        if (e < 0) e = -e;
        if (e < 8) {
            return (++data[i] > threshold) ? i : 0;
        }
    }
    return 0;
}
byte Keyboard::read_bit(int index) {
    return 0;
}
#endif // ARDUINO

 