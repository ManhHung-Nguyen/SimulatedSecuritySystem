#include "BIOS.h"
#include "../System/System.h"
void BaseIO::interrupt(int wparam, int lparam) {
	if (interrupt_number) {
		is_busy = true;
		System::ICall(interrupt_number, wparam, lparam);
	}
}

void BaseIO::interrupt(int param) {
	interrupt(int((int*)this), param);
}
