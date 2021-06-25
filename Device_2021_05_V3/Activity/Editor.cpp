#include "Editor.h"
#include "Activity.h"

LPCHAR Mask::Password = "----";
LPCHAR Mask::Phone = "+84 --- --- ---";
LPCHAR Mask::Date = "--/--/--";
LPCHAR Mask::Time = "--:--";
LPCHAR Mask::ACT = " 1  2  3  4 ";

byte* Editor::data_buffer;

bool Editor::is_space(byte c) {
	return c < '0' || c > '9';
}

void Editor::BeginEdit() {

	byte* p = data_buffer;
	
	int i = 0;
	for (i = first_index; i < length; i++) {
		byte& c = data[i];
		if (c == 0) { 
			break; 
		}
		if (c == MASK_CHAR) {
			byte b = *p++;
			if (is_space(b)) { 
				break; 
			}

			c = b;
		}
	}
	cursor_pos = i;
	_screen_builder.UpdateContent(0, 10);
}

byte* Editor::EndEdit(byte* dst) { 

	_set_modify(false);
	if (IsFull()) {
		if (dst == 0) dst = data_buffer;
		byte* p = dst;
		for (int i = first_index; i < length; i++) {
			byte b = data[i];
			if (!is_space(b)) {
				*p++ = b;
			}
		}
		*p = 0;
		return dst;
	}
	return 0;
}
void Editor::Mark(int code) {
	data_buffer[code] = '1';
	
	int i = get_mark_screen_pos(code);
	data[i - 1] = '[';
	data[i + 1] = ']';
}
void Editor::Unmark(int code) {
	data_buffer[code] = '0';

	int i = get_mark_screen_pos(code);
	data[i - 1] = ' ';
	data[i + 1] = ' ';
}
void Editor::ToggleMark(int code) {
	int i = get_mark_screen_pos(code);
	if (data[i - 1] == ' ') {
		Mark(code);
	}
	else {
		Unmark(code);
	}
	_edit_line(i - 1) << (char)data[i - 1];
	_edit_line(i + 1) << (char)data[i + 1];
	_set_modify(true);
}
void Editor::SetInputMask(LPCHAR mask) {

	is_valid = 0;
	get_screen_char = 0;

	_content.Restart();
	if (mask) { _content.Copy(mask); }

	data = _content.Handle();
	data_buffer = data + LCD_COLS;
	data_buffer[0] = EMPTY_BYTE;


	length = _content.Position();
	for (int i = 0; i < length; i++) {
		if (data[i] == MASK_CHAR) {
			first_index = i;
			return;
		}
	}
}
int Editor::Peek() {
	int i = cursor_pos - 1;
	if (i >= first_index && !is_space(data[i])) {
		return data[i] & 15;
	}
	return 0;
}
void Editor::Push(int code) {
	register int i = cursor_pos;
	if (i >= length || (is_valid && !is_valid(code & 15, Peek(), i - first_index))) {
		return;
	}

	char c = byte(code);
	if (get_screen_char) { c = get_screen_char(c); }

	_set_modify(true);
	_edit_line(i) << c;

	data[i++] = code;
	if (i < length) {
		c = data[i];
		if (c != MASK_CHAR && is_space(c)) { 
			i++;
		}
	}
	cursor_pos = i;
}
void Editor::Pop() {
	register int i = cursor_pos;
	if (i == first_index) { return; }

	if (is_space(data[--i])) {
		--i;
	}

	_set_modify(true);
	_edit_line(i) << MASK_CHAR;

	cursor_pos = i;
}
