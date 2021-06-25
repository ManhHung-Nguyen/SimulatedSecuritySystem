#include "SerialBuffer.h"
#include "../System/System.h"

byte* SerialPort::default_handle = 0;
SerialPort::SerialBuffer() : Builder(128) {
	if (default_handle == 0) {
		default_handle = System::DRAM.Malloc(capacity);
	}
	di = data = default_handle;
}

void SerialBuffer::Clear() {
	di = data;
}

LPCHAR SerialBuffer::ReadToEnd() {
	while (is_available()) {
		*di++ = Read();
	}
	*di = 0;
	return LPCHAR(data);
}
