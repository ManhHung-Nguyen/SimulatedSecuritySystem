#include "Plan.h"
#include "DateTimeSetting.h"

const char* days_of_week = "ALLSUNMONTUEWEDTHUFRISAT";
extern bool check_time_item(byte, byte, int);

LPCHAR Plan::get_input_mask() {

	int i = current_index * 3;

	LineBuilder temp;
	temp("#---:  ");
	for (int k = 0; k < 3; k++) {
		temp[k + 1] = days_of_week[i++];
	}
	temp << Mask::Time;
	temp[temp.Position()] = 0;

	return LPCHAR(temp.Handle());
}

void Plan::copy_data_to_buffer(byte* dst)
{
	_editor.is_valid = check_time_item;
	if (*it != EMPTY_BYTE) {
		_split_decimal(dst, it[0]);
		_split_decimal(dst, it[1]);
	}
	else {
		Buffer(dst, 4).Reset(EMPTY_BYTE);
	}
}

void Plan::update_editing_data() {
	byte h = EMPTY_BYTE;
	byte m = EMPTY_BYTE;
	byte* data = Handle();

	if (_editor.IsFull()) {
		byte* v = DateTimeSetting::merge(Editor::data_buffer);
		h = v[0];
		m = v[1];
	}

	if (it == data) {
		int i = 1;
		while (i < capacity) {
			data[++i] = h;
			data[++i] = m;
		}
		h = m = EMPTY_BYTE;
	}
	*it = h;
	*(it + 1) = m;
}
