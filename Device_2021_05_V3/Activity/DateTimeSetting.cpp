#include "DateTimeSetting.h"
#include "Activity.h"

bool check_time_item(byte code, byte last, int position) {
	switch (position) {
	case 0: return code < 3;
	case 1: return code < 4 || last < 2;
	case 3: return code < 6;
	}
	return true;
}

byte date_edit_template[3];
bool check_date_item(byte code, byte last, int position) {
	date_edit_template[position / 3] = last * 10 + code;
	switch (position) {
	case 0: return code < 4;
	case 1: return code < 2 || last < 3;
	case 3: return code < 2;
	case 4: return code < 3 || last == 0;
	case 7:
		byte* it = date_edit_template;
		return SysClock::days_of_month(it[2], it[1]) >= it[0];
	}
	return true;
}
void TimeSetting::set_time(byte hour, byte minute) {
	System::Clock.SetTime(hour, minute, 0);
}

void TimeSetting::update_editing_data() {
	byte* v = merge(Editor::data_buffer);
	set_time(v[0], v[1]);
}
void TimeSetting::copy_data_to_buffer(byte* dst) {
	_editor.is_valid = check_time_item;
	copy_data_core(dst, _clock.GetHour(), _clock.GetMinute(), _clock.GetYear());
}
void DateSetting::update_editing_data() {
	byte* v = merge(Editor::data_buffer);
	System::Clock.SetDate(v[0], v[1], v[2]);
}

void DateSetting::copy_data_to_buffer(byte* dst) {
	_editor.is_valid = check_date_item;
	copy_data_core(dst, _clock.GetDay(), _clock.GetMonth(), _clock.GetYear());
}

byte* DateTimeSetting::merge(byte* src) {
	byte* p = src;
	byte* q = p;

	while (byte b = *p++) {
		*q++ = (b & 15) * 10 + (*p++ & 15);
	}
	return src;
}
