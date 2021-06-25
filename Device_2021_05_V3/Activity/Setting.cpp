#include "Setting.h"
#include "Editor.h"
#include "Activity.h"
#include "../Device/Device.h"

Editor _editor;

Setting::Setting(LPCHAR main)
	: Mode(main)
	, Buffer(-1) {
}

void Setting::load_config() {
	int len = get_full_data_size();
	if (len > 0) {
		capacity = len;
		data = ConfigManager::GetBuffer(len);
	}
	Mode::load_config();
}

void Setting::show_content(LPCHAR content) {
	_editor.SetInputMask(get_input_mask());

	it = get_edit_data_handle();
	copy_data_to_buffer(_editor.data_buffer);
	_editor.BeginEdit();
}

void Setting::ProcessKey(int code) {
	_screen_builder.Wait(5);
	Mode::ProcessKey(code);
}

void Setting::on_del_key() {
	_editor.Pop();
}

void Setting::on_number_key(int code) {
	_editor.Push(code | 48);
}

bool Setting::can_update() {
	return _editor.IsFull();
}

void Setting::update_editing() {
	_editor.EndEdit();

	it = get_edit_data_handle();
	update_editing_data();

	if (get_full_data_size() > 0) {
		save_to_disk();
	}
}

void Setting::save_to_disk() {
	ConfigManager::Save();
}

void ListSetting::update_editing_data() {
	int sz = get_item_data_size();
	Buffer buffer(sz);
	buffer.Mapping(get_edit_data_handle());
	buffer.Copy(Editor::data_buffer, sz);
}
