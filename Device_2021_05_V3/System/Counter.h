#pragma once
#include "Types.h"

class Counter {
protected:
	int value;
	int duration;
protected:
	virtual void on_milisecond() {
		if (--value == 0) {
			on_tick();
			value = duration;
		}
	}
	virtual bool is_running() { return value > 0; }
	virtual void on_tick() {}
public:
	Counter();
	~Counter();
public:
	void operator--() {
		if (is_running()) {
			on_milisecond();
		}
	}
	void Reset(int interval = 0) { value = duration = interval; }
	void Stop() { value = -1; }
};

