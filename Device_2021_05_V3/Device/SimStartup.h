#pragma once
#include "Startup.h"
class SimStartup : public Startup
{
protected:
	void on_count_down() override {}
	void begin() override {
		main_title = "SIM CARD";
		duration = 3;
	}
};
