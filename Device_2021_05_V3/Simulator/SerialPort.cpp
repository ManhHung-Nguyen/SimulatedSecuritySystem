#include "../Communication/SimCard.h"
#include "Simulator.h"

void ATBuilder::send_byte(byte b) {
}

char to_hex(byte b) {
	if (b >= 10) {
		return char(b + 55);
	}
	return char(b | 48);
}
void ATBuilder::on_completed() {
	char* temp = new char[256];

	for (int i = 0, k = 0; i < capacity; i++) {
		byte b = data[i];
		if (b == 0) {
			temp[k] = 0;
			break;
		}

		temp[k++] = to_hex(b >> 4);
		temp[k++] = to_hex(b & 15);
	}

	Simulator::Send("ATCommand", LPCHAR(temp));

	delete[] temp;
}