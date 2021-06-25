#pragma once
#include "Setting.h"
#include "Menu.h"

#define PHONE_NUMBER_LENGTH 9
#define PHONE_NUMBER_COUNT  5
class PhoneSetting :
    public ListSetting {
protected:
    int get_items_count() override { return PHONE_NUMBER_COUNT; }
    int get_item_data_size() override { return 10; }

    void show_main_title(LPCHAR title) override;
    void copy_data_to_buffer(byte* dst) override;
    LPCHAR get_input_mask() { return Mask::Phone; }
public:
    bool GetNumber();
    virtual void OnAlarm();
};

class SmsSetting : public PhoneSetting {
public:
    void OnAlarm() override;
};

class CallSetting : public PhoneSetting {
public:
    void OnAlarm() override;
};