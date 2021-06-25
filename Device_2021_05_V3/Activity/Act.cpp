#include "Act.h"
#include "Editor.h"
#include "../Device/Device.h"

void Act::copy_data_to_buffer(byte* dst) {
	for (int i = 0; i < get_item_data_size(); i++) {
		if (it[i] != '0') {
			_editor.Mark(i);
		}
	}
}

void Act::on_number_key(int code) {
	if (code > Keys::N0 && ACT_LENGTH >= code) {
		_editor.ToggleMark(code - 1);
	}
}

void Act::update_editing() {
	_set_modify(false);
	ListSetting::update_editing_data();
	ListSetting::save_to_disk();
}

int Act::GetValueMask() {
	int a = 0;
	for (int i = 0; i < ACT_LENGTH; i++) {
		if (IsActive(i)) {
			a |= 1 << i;
		}
	}
	return a;
}
