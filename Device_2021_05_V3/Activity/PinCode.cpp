#include "PinCode.h"
#include "Activity.h"
#include "Home.h"

byte set_password_char(byte b) {
	return '*';
}
void PinCode::copy_data_to_buffer(byte* dst) {
	_editor.get_screen_char = set_password_char;
}

bool PinCode::check_pin(byte* src) {
	for (int i = 0; i < PIN_CODE_LEN; i++) {
		if (Editor::data_buffer[i] != src[i])
			return false;
	}
	return true;
}

void EnterPinCode::update_editing_data() {
	if (check_pin((*(Setting*)Child->Child).Handle())) {
		_home.Unlock();
		Redirect(Sibling);
	}
	else {
		show_message("INVALID");
	}
}

byte* pin_code_template = 0;
void ChangePinCode::update_editing_data() {
	if (pin_code_template == 0) {
		pin_code_template = System::DRAM.Malloc(PIN_CODE_LEN);
	}
	_editor.EndEdit(pin_code_template);
	Redirect(Child);
}

void ConfirmPinCode::update_editing_data() {
	if (check_pin(pin_code_template)) {
		Seek(0).Copy(pin_code_template, PIN_CODE_LEN);
		Message::Show(Parent->main_title, "SAVED");
	}
	else {
		show_message("NOT MATCH");
	}
}

LPCHAR default_password = "1111";
void ConfirmPinCode::load_config() {
	PinCode::load_config();
	if (data[0] == EMPTY_BYTE) {
		Seek(0).Copy((byte*)default_password, PIN_CODE_LEN);
	}
}
