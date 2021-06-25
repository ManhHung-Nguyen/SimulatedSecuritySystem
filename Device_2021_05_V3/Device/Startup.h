#pragma once
#include "../Activity/Mode.h"

#define _with_duration switch(duration)

class Startup : public Mode {
protected:
	int duration;
	virtual void on_count_down() = 0;
	virtual void begin() = 0;
	virtual void exit() {}

public:
	Startup();
	virtual int CountDown();

	static void Execute();
};
