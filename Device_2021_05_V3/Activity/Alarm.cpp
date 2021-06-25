#include "Alarm.h"
#include "ARM.h"
#include "Home.h"
#include "PhoneSetting.h"
#include "InputSetting.h"
#include "../Activity/Activity.h"

#define ALARM_BUILDER_SIZE	128

Alarm::Alarm() {
	BUILDER.Resize(ALARM_BUILDER_SIZE);
	System::DRAM.Malloc(BUILDER);
}

bool Alarm::CheckInput(int value) {
	if (value <= 0) { return false; }
	Arm* mode = (Arm*)_home.GetArm();
	if (value &= mode->GetInputMask()) {
		Device::UpdateInputs(value);

		BUILDER.Seek(0).Copy("INPUT");

		int count = 0;
		int outputs = 0;
		for (int i = 0; i < ACT_LENGTH; i++) {
			if (value & (1 << i)) {
				BUILDER++ = count++ == 0 ? ' ' : ',';
				BUILDER++ = byte(i + 49);

				outputs |= (*(InputSetting*)OUTPUTS).GetOutputMask(i);
			}
		}
		*BUILDER = 0;

		sub_title = LPCHAR(BUILDER.Handle());

		Device::UpdateRelays(outputs);
		Activity::Select(this);
		(*(PhoneSetting*)SMS).OnAlarm();
		return true;
	}
	return false;
}

bool Alarm::CheckZone(int value) {
	if (value <= 0) { return false; }
	Arm* mode = (Arm*)_home.GetArm();
	if (mode->GetZoneSetting()->IsActive(value >> 6)) {

		BUILDER.Seek(0).Copy("BEAM ");
		BUILDER << value;

		sub_title = LPCHAR(BUILDER.Handle());

		Device::UpdateRelays((*(InputSetting*)OUTPUTS).GetOutputMask(0));
		Activity::Select(this);
		(*(PhoneSetting*)SMS).OnAlarm();
		return true;
	}
	return false;
}

void Alarm::Activate() {
	_screen_builder.UpdateTitle("ALARM");
	_screen_builder.UpdateContent(sub_title, 10);
}

void Alarm::ProcessKey(int code) {
	if (code == Keys::STAR) {
		Activity::Login(_home.GetDisarm());
	}
}

LPCHAR Alarm::GetContent()
{
	return LPCHAR(BUILDER.Handle());
}