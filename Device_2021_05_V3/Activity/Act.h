#pragma once
#include "Setting.h"

class Act : public ListSetting {
protected:
	int get_items_count() override { return 1; }
	int get_item_data_size() override { return ACT_LENGTH; }
	void show_main_title(LPCHAR s) override {
		Setting::show_join_title(Parent->main_title);
	}
	LPCHAR get_input_mask() { return Mask::ACT; }
	void copy_data_to_buffer(byte* dst);
	void on_number_key(int code) override;
	void update_editing() override;
public:
	virtual bool IsActive(int value) {
		return data[value] != '0';
	}
	int GetValueMask();
};