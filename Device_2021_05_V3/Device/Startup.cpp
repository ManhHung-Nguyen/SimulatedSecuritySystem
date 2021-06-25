#include "Startup.h"
#include "../Device/Device.h"

Startup* _current_startup = 0;
void run_startup() {

	if (_current_startup->CountDown() == 0) {
		PMODE next = _current_startup->Sibling;
		if (next) {
			_current_startup = (Startup*)next;
		}
	}

	Device::SCREEN(1) << System::Clock.Time();
}

Startup::Startup()
	: duration(-1) {
	Sibling = _current_startup;
	_current_startup = this;
}

int Startup::CountDown() {
	if (duration < 0) {
		begin();
		show_main_title(main_title);
		return duration;
	}

	on_count_down();
	if (--duration == 0) {
		exit();
	}
	return duration;
}
void Startup::Execute() {
	System::Clock.SetEvent(SECOND, run_startup);
}
