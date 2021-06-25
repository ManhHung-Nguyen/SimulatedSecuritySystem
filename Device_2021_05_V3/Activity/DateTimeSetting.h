#pragma once
#include "Setting.h"

#define _split_decimal(p, v) *p++=byte((v/10)|48);*p++=byte((v%10)|48)

class DateTimeSetting :
    public Setting {
protected:

    void copy_data_core(byte* dst, int v1, int v2, int v3, bool for_date = false) {
        if (v3 == 0) {
            dst[0] = 0;
            return;
        }
        _split_decimal(dst, v1);
        _split_decimal(dst, v2);
        if (for_date) {
            v3 /= 100;
            _split_decimal(dst, v3);
        }
    }
public:
    static byte* merge(byte* src);
};

class DateSetting : public DateTimeSetting {
protected:
    void update_editing_data() override;
    void copy_data_to_buffer(byte* dst);
    LPCHAR get_input_mask() { return Mask::Date; }

};

class TimeSetting : public DateTimeSetting {
protected:
    void update_editing_data() override;
    void copy_data_to_buffer(byte* dst);

    LPCHAR get_input_mask() { return Mask::Time; }
    virtual void set_time(byte hour, byte minute);
};


