#include "Device.h"
#include "SimStartup.h"
#include "SDStartup.h"
#include "Internet.h"

SimCard Device::SIM;
MqttEngine Device::MQTT;
Monitor Device::SCREEN;
Keyboard Device::KEYBOARD(16);
DigitalPort Device::RELAYS(4);
OutPort Device::LEDS(8);
Sensors Device::INPUTS;
Beam Device::BEAM;
ScreenBuilder Device::ScreenBuilder;

#pragma region STARTUP
#include "../Activity/Activity.h"

class Done : public Startup {
protected:
	void on_count_down() override {}
	void begin() override {}

	int CountDown() override {
		Activity::GoHome();
		return 0;
	}
} startup_done;

Internet internet;
SimStartup sim_card;
SDStartup sd_card;
#pragma endregion

#define _eu(n,s) System::EU.Insert(n, s)

ClientID Device::CLIENT_ID;

void Device::SetClientId() {
	LPCHAR id;
	System::EU >> id;

	CLIENT_ID.SetValue(id);
}

void Device::TurnOn() {

	_eu("ARM", Device::ArmON);
	_eu("DIS", Device::ArmOFF);
	_eu("TIME", Device::Time);
	_eu("PLAN", Device::PLAN);
	_eu("AACT", Device::ArmInputAction);
	_eu("IACT", Device::InputOutputAction);
	_eu("SMS", Device::SetSmsNumber);
	_eu("CALL", Device::SetCallNumber);
	_eu("CID", Device::SetClientId);

	SCREEN.Begin();
	SCREEN.WakeUp();
	on_power(true);

	KEYBOARD.SetInterruptNumber(INT_KEYBOARD);
	INPUTS.SetInterruptNumber(INT_INPUT);

	SCREEN(0) << "START UP ...";
	Startup::Execute();
}

#include "../Activity/ARM.h"
bool is_alarm_detect = false;

#define _sys_led(i) i
#define _inp_led(i) i + 4

void Device::Update(int input_mask, int mode_index) {

	LEDS.SetBit(2, 0);
	LEDS.SetBit(3, 0);
	if (is_alarm_detect = mode_index > 0) {
		LEDS.SetBit(4 - mode_index, 1);
	}
	else {
		UpdateRelays(0);
	}
	for (int i = 0; i < ACT_LENGTH; i++, input_mask >>= 1) {
		LEDS.SetBit(_inp_led(i), input_mask);
	}

	_clock.SetEvent(MILIS, Device::OnMilis);
	_clock.SetEvent(SECOND, Device::OnSecond);
}

void Device::UpdateInputs(int mask) {
	for (int i = 0; i < ACT_LENGTH; i++, mask >>= 1) {
		if (mask & 1) {
			LEDS.SetBlink(_inp_led(i));
		}
		else {
			LEDS.SetBit(_inp_led(i), 0);
		}
	}
}

void Device::UpdateRelays(int mask) {
	for (int i = 0; i < RELAYS.Capacity(); i++, mask >>= 1) {
		RELAYS.SetBit(i, mask);
	}
}

void Device::ProcessAlarm(LPCHAR content) {
	Message::Show("ALARM", content);
}

void Device::OnMilis() {
	int milis = _clock.GetMilis();
	if ((milis & 7) == 0) {
		if (is_alarm_detect) {
			init_scanner();
			INPUTS.Scan(5);
		}
		KEYBOARD.Scan(2);
	}
	//if ((milis & 127) == 0) {
	//	if (is_alarm_detect) {
	//		if (Activity::ALARM.CheckInput(INPUTS.GetValue())) { return; }
	//		if (Activity::ALARM.CheckZone(BEAM.GetValue())) { return; }
	//	}

	//	//int key = KEYBOARD.GetIndex(2);
	//	//if (key >= 0) {
	//	//	System::ICall(INT_KEYBOARD, key);
	//	//}
	//}
}

void Device::OnSecond() {
	ScreenBuilder.CountDown();
}
