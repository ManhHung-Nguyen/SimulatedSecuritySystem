#pragma once
#include "Act.h"

class InputSetting : public Act {
public:
	int GetOutputMask(int index);
protected:
	int get_items_count() override { return ACT_LENGTH; }
	int get_item_data_size() override { return ACT_LENGTH; }
	void show_main_title(LPCHAR title) { 
		show_item_index(current_index); 
	}
};

