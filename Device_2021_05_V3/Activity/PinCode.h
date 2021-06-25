#pragma once
#include "Setting.h"

#define PIN_CODE_LEN    4

class PinCode :
    public Setting {
public:
    PinCode() {
        data = 0;
        capacity = PIN_CODE_LEN;
    }
protected:
    LPCHAR get_input_mask() { return Mask::Password; }
    void copy_data_to_buffer(byte* dst) override;
    bool check_pin(byte* src = 0);
};

class ConfirmPinCode : public PinCode {
protected:
    int get_full_data_size() override { return PIN_CODE_LEN; }
    void update_editing_data() override;
    void load_config() override;

public:
    ConfirmPinCode() {}
};

class ChangePinCode : public PinCode {
protected:
    void update_editing_data() override;

public:
    ChangePinCode() {
        Prepend(new ConfirmPinCode(), "CONFIRM");
    }
};

class EnterPinCode : public PinCode {
protected:
    void update_editing_data() override;
    void go_up() override {}
public:
    EnterPinCode() {
        main_title = "PASSWORD";
        Prepend(new ChangePinCode(), "CHANGE PASS");
    }
};

