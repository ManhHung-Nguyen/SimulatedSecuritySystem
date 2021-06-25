#pragma once
#include "Types.h"
#include "Clock.h"
#include "ExecUnit.h"
#include "Buffer.h"
#include "Constants.h"
#include "Log.h"

#define INT_MONITOR		5
#define INT_KEYBOARD	6

class System {
public:
	static Memory DRAM;	
	static SysClock Clock;
	static ExecUnit EU;
public:
	static void IReg(int number, interrupt_ptr proc);
	static void ICall(int number, int w, int l = 0);
public:
	static void Reset() {}
};

