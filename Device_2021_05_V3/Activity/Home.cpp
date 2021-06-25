#include "Home.h"
#include "ARM.h"
#include "Activity.h"

void HomePage::go_home() {
	if (current_mode_index == 0) { // DISARM
		current_mode_index = current_arm_index;
		unlocked = false;

		Redirect(this);
	}
	else {
		Activity::Login(this);
	}
}

void HomePage::go_up() {
	if (!unlocked) {
		Activity::Login();
	}
	else {
		Redirect(Activity::FirstMenu);
	}
}

void HomePage::select_item(int dir) {
	current_arm_index += dir;
	if (current_arm_index == 0) {
		current_arm_index = ARM_MODE_COUNT - 1;
	}
	else if (current_arm_index == ARM_MODE_COUNT) {
		current_arm_index = 1;
	}
	current_mode_index = -1;
	current_arm_index;
	
	Redirect(this);
}

HomePage::HomePage() {
	unlocked = false;
	current_arm_index = current_mode_index = ARM_MODE_COUNT - 1;
}

PMODE HomePage::GetArm(int index) {
	if (index == 0) {
		if (current_mode_index == 0) { return 0; }
		return arms[current_arm_index];
	}
	return arms[ARM_MODE_COUNT - index];
}

void HomePage::Activate() {

	if (current_mode_index < 0) { // Lan dau
		current_mode_index = current_arm_index;
	}

	if (current_mode_index > 0) { // ARMED
		current_arm_index = current_mode_index;
	}


	BaseARM* mode = (BaseARM*)arms[current_mode_index];
	Device::Update(mode->GetInputMask(), current_mode_index);

	show_main_title(mode->main_title);
	_screen_builder.UpdateContent(System::Clock.Time(), -5);
}

void HomePage::Activate(int index) {
	current_mode_index = index;
	Redirect(this);
}

void HomePage::Lock() {
	Redirect(this);
	unlocked = false;
}

void HomePage::Unlock() {
	current_mode_index = 0;
	unlocked = true;
}
