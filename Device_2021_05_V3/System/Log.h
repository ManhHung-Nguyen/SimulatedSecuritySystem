#pragma once

#ifdef ARDUINO

#include <Arduino.h>

#define log		Debug()
#define endl	'\n'

class Debug {
	HardwareSerial* _port;
public:
	Debug();
	template <class T>
	Debug& operator<<(T value) {
		_port->print(value);
		return *this;
	}
};

#else

#include <iostream>
#include <Windows.h>

#define log std::cout

#endif

