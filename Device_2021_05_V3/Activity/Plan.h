#pragma once
#include "Setting.h"

class Plan :
    public ListSetting {
protected:
    int get_items_count() override { return 8; }
    int get_item_data_size() override { return 2; }
    void show_main_title(LPCHAR s) override {
        ListSetting::show_join_title(Parent->main_title);
    }
    LPCHAR get_input_mask() override;
    void copy_data_to_buffer(byte* dst);
    bool can_update() {
        return _editor.IsFull() || _editor.IsEmpty();
    }
    void update_editing_data() override;
};

