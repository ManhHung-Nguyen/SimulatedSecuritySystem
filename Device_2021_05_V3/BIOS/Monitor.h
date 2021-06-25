#pragma once
#include "Constants.h"

class Monitor {
public:
	Monitor();

public:
	static void Begin();
	static void Sleep();
	static void WakeUp(int timeout = 5);

	Monitor& operator()();
	Monitor& operator()(int line);
	Monitor& operator()(int x, int y);

	Monitor& operator<<(const char* s);
	Monitor& operator<<(const char c);
};
