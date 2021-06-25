#include "Sensors.h"
//#include "../Activity/ARM.h"

//extern BaseARM* CURRENT_ARM;
//bool Sensors::CheckAlarm() {
//	int v = GetValue();
//	if (v < 0) {
//		return false;
//	}
//
//	BaseARM::Input* act = CURRENT_ARM->GetInputSetting();
//	if (v == 0) {
//		for (int i = 0; i < ACT_LENGTH; i++) {
//			Device::LEDS.SetBit(i + 4, act->IsActive(i) ? 1 : 0);
//		}
//		return false;
//	}
//
//	int a = act->CheckValue(v);
//	if (a == 0) { return false; }
//
//	LineBuilder line(1); 
//	line.Copy("INPUT ");
//	for (int i = 0; i < ACT_LENGTH; i++) {
//		if (a & (1 << i)) {
//			Device::LEDS.SetBlink(i + 4);
//			line << (i + 1) << ",";
//
//
//		}
//		else {
//			Device::LEDS.SetBit(i + 4, 0);
//		}
//	}
//
//	(--line) = 0;
//	Device::ProcessAlarm(LPCHAR(line.Handle()));
//	return true;
//}
//
//bool Beam::CheckAlarm() {
//	int v = GetValue();
//	if (v > 0) {
//		BaseARM::Zone* act = CURRENT_ARM->GetZoneSetting();
//		if (act->CheckValue(v) >= 0) {
//			LineBuilder line(1);
//			line.Copy("BEAM ");
//			line << v;
//
//			Device::ProcessAlarm(LPCHAR(line.Handle()));
//			return true;
//		}
//	}
//	return false;
//}

int Sensors::scan_all_bit(int thresold)
{
	int v = InPort::scan_all_bit(thresold);
	if (v) {
		interrupt(2, v);
	}
	else if (v = get_beam()) {
		interrupt(1, v);
	}
	return 0;
}
