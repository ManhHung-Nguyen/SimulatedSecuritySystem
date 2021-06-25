#pragma once

#ifdef ARDUINO

#include "LiquidCrystal.h"

#define LCD_POWER    6

class LCD : public LiquidCrystal {
public:
    LCD() : LiquidCrystal(A0, A1, A2, A3, A4) {
        pinMode(LCD_POWER, OUTPUT);
    }
    void ligth(bool b) {
        digitalWrite(LCD_POWER, b);
    }
};
#endif // ARDUINO

