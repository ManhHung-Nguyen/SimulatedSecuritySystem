#pragma once
#include "Startup.h"
class SDStartup : public Startup
{
protected:
	void on_count_down();
	void begin() override {
		main_title = "SD CARD";
		duration = 1;
	}
};

