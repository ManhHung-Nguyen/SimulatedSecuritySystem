#pragma once
#include "Mode.h"
#include "Editor.h"
#include "../System/Buffer.h"

class Setting :
	public Mode, public Buffer {
public:
	Setting(LPCHAR main = 0);

protected:
	virtual int get_full_data_size() { return 0; }
	virtual int get_item_data_size() {
		return get_full_data_size();
	}
	virtual int get_edit_data_size() {
		return get_item_data_size();
	}
	virtual byte* get_edit_data_handle() { return data; }
	void load_config() override;
	void show_content(LPCHAR content) override;
	virtual void copy_data_to_buffer(byte* dst) {
		int sz = get_item_data_size();
		Buffer src(sz);
		src.Mapping(dst);
		src.Copy(get_edit_data_handle(), sz);
	}
	virtual LPCHAR get_input_mask() { return 0; }

	void ProcessKey(int code) override;
	void go_down(int index) override {}
	void on_del_key() override;
	void on_number_key(int code) override;

	bool can_update() override;
	void update_editing() override;
	virtual void update_editing_data() {}
	virtual void save_to_disk();
};

class ListSetting : public Setting {
protected:
	int current_index;
protected:
	virtual int get_items_count() = 0;
	int get_full_data_size() {
		current_index = 0;
		return get_items_count() * get_item_data_size();
	}
	void select_item(int dir) override {
		int n = get_items_count();
		current_index += dir;

		if (current_index < 0) {
			current_index = n - 1;
		}
		else if (current_index >= n) {
			current_index = 0;
		}

		this->Activate();
	}
	byte* get_edit_data_handle() override {
		return data + current_index * get_item_data_size();
	}
	void update_editing_data() override;
};