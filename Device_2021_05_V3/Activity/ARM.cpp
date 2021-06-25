#include "ARM.h"
#include "Activity.h"
#include "Home.h"

PMODE arm_modes[] = {
	new Disarm(),
	new Arm(),
	new Arm(),
};
PMODE* HomePage::arms = arm_modes;

void check_plan() {
	byte m = byte(System::Clock.GetMinute());
	byte h = byte(System::Clock.GetHour());
	int d = System::Clock.GetWeekDay();

	for (int i = 0; i < ARM_MODE_COUNT; i++) {
		Plan& p = *(Plan*)arm_modes[i]->Child;
		byte* it = p.Handle() + ((d + 1) << 1);

		if (h == *it && m == *(it + 1)) {
			_home.Activate(i);
			return;
		}
	}
}