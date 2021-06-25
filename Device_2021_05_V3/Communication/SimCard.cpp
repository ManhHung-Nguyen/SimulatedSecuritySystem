#include "SimCard.h"

//ATBuilder SimCard::SENDER;
//SerialBuffer SimCard::RECEIVER;
//
//void ATBuilder::on_tick() {
//	byte* end = data + capacity;
//	while (di < end) {
//		byte b = *di++;
//		send_byte(b);
//		if (b == '\n') {
//			value = duration = *di++;
//			if (duration == 0) {
//				on_completed();
//			}
//			break;
//		}
//	}
//}

ATBuilder::ATBuilder() {
	di = data = 0;
}

void ATBuilder::Start() {
	if (data == 0) {
		data = System::DRAM.Malloc(capacity = 64);
	}
	*(di = data) = 0;
}

void ATBuilder::Ready() {
	*this & '\n';
	di = data;
}
ATBuilder& ATBuilder::operator<<(int delay) {
	*di++ = '\n';
	return *this & delay;
}

ATBuilder& ATBuilder::operator<<(LPCHAR content) {
	if (*di == 0 && di > data) {
		*di++ = '\n';
		*di++ = 1;
	}
	return (*this) & content;
}

ATBuilder& ATBuilder::operator&(int value)
{
	*di++ = byte(value);
	*di = 0;
	return *this;
}

ATBuilder& ATBuilder::operator&(LPCHAR content) {
	while (*content) {
		*di++ = *content++;
	}
	*di = 0;
	return *this;
}
