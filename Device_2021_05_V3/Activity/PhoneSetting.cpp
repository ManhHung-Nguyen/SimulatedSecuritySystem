#include "PhoneSetting.h"

void PhoneSetting::show_main_title(LPCHAR title) {
	show_item_index(current_index);
}

void PhoneSetting::copy_data_to_buffer(byte* dst) {
	it = get_edit_data_handle();
	for (int i = 0; i < PHONE_NUMBER_LENGTH; i++) {
		byte b = it[i];
		if (b == EMPTY_BYTE) { break; }

		dst[i] = b;
	}
}

PhoneSetting* current_phone_mode = 0;
LPCHAR current_number = 0;
int phone_circle = 0;
int phone_duration = 0;

bool PhoneSetting::GetNumber() {
	while (current_index < PHONE_NUMBER_COUNT) {
		byte* p = get_edit_data_handle();

		current_index++;
		if (*p >= '0' && '9' >= *p) {
			current_number = LPCHAR(p);
			return true;
		}
	}

	current_index = 0;
	if (--phone_circle) {
		return GetNumber();
	}
	PhoneSetting* mode = (PhoneSetting*)Sibling;
	if (mode) {
		mode->OnAlarm();
	}
	else {
		Activity::GoHome();
	}
	return false;
}


void PhoneSetting::OnAlarm() {
	current_index = 0;
	phone_duration = -1;
	current_phone_mode = this;
}


#include "../Device/Device.h"
#include "../Communication/SimCard.h"

#define _sim	Device::SIM
#define _sender Device::SIM.AT

#pragma region SMS
void sending_sms() {
	if (phone_duration < 0) {
		if (current_phone_mode->GetNumber()) {
			phone_duration = 3;

			_screen_builder.UpdateTitle(LineBuilder() << "SMS " << current_number);

			_sender.Start();
			_sender << "AT+CMGF=1"
				<< 15 & "AT+CMGS=\"+84" & current_number & '\"';
			_sender << 15 & Activity::ALARM.GetContent() & 26;

			_sim.SendAT();
		}
	}
	--phone_duration;
}

void SmsSetting::OnAlarm() {
	PhoneSetting::OnAlarm();
	phone_circle = 1;

	_clock.SetEvent(SECOND, sending_sms);
}
#pragma endregion

#pragma region CALL
void end_call() {
	_sim.SendAT("ATH");
	Activity::GoHome();
}
void calling() {
	if (phone_duration < 0) {
		if (current_phone_mode->GetNumber()) {
			phone_duration = 20;

			_screen_builder.UpdateTitle(LineBuilder() << "CALL " << current_number);
			_sender.Start();
			_sender << "ATD+84" & current_number & ';';

			_sim.SendAT(); // _sender.Execute();
		}
	}
	if (--phone_duration > 15) { // cho 5 giay de ket noi cuoc goi
		return;
	}

	if (phone_duration & 1) {
		_sim.SendAT("AT+CPAS");
		return;
	}

	Builder& input = _sim.GetInputBuffer();

	_sim.ReadAll();
	int i = input.IndexOf("+CPAS");
	if (i >= 0) {
		byte v = input[i + 7] & 15;
		if (v != 4) {
			end_call();
		}
		return;
	}
	if (input.Contains("BUSY") || input.Contains("NO CARRY")) {
		end_call();
	}
}

void CallSetting::OnAlarm() {
	PhoneSetting::OnAlarm();
	phone_circle = 2;

	_clock.SetEvent(SECOND, calling);
}
#pragma endregion
