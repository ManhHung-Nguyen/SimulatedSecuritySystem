#pragma once

#include "../System/Builder.h"

#ifdef WIN32
class HardwareSerial {
public:
	HardwareSerial() {}
public:
	void begin(int baud) {}
	void begin(int baud, int rx, int tx) {}
	void begin(int baud, int mode, int rx, int tx) {}
	virtual bool available() { return false; }
	virtual byte read() { return 0; }
	virtual void write(byte b) {}
};
class SoftwareSerial : public HardwareSerial {
public:
	SoftwareSerial() {}
	SoftwareSerial(int rx, int tx) {}
};
#endif // WIN32


template <class T>
class SerialPort {
protected:

	T port;

	Builder input;
	Builder output;
	byte* di;
public:
public:
	Builder& GetInputBuffer() { return input; }
	Builder& SetInputBuffer(byte* handle, int size = 0) {
		if (size) { input.Resize(size); }
		return input.Mapping(handle);
	}
	Builder& SetInputBuffer(const Buffer& buffer) {
		input.Mapping(buffer);
		return input;
	}
	virtual bool ReadOneByte() {
		if (!port.available()) { return false; }
		*di++ = port.read();

		return false;
	}
	LPCHAR ReadAll() {
		di = input.Handle();
		byte* end = di + input.Capacity();
		while (di < end) {
			if (!ReadOneByte()) {
				*di = 0;
				break;
			}
		}
		return LPCHAR(input.Handle());
	}

	Builder& GetOutputBuffer() { return input; }
	Builder& SetOutputBuffer(byte* handle, int size = 0) {
		if (size) { output.Resize(size); }
		return output.Mapping(handle);
	}
	Builder& SetOutputBuffer(const Buffer& buffer) {
		output.Mapping(buffer);
		return output;
	}
	virtual bool WriteOneByte() {
		byte b = *di++;
		if (b == 0) { return false; }

		port.write(*di++);
		return true;
	}
	void WriteAll() {
		di = output.Handle();
		byte* end = di + output.Capacity();
		while (di < end) {
			if (!WriteOneByte()) {
				break;
			}
		}
	}
};
