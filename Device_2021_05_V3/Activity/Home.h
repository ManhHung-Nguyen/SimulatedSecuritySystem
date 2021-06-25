#pragma once
#include "Mode.h"
#include "Constants.h"
#include "../System/Clock.h"

class HomePage : public Mode
{
    static PMODE* arms;
    int current_arm_index;
    int current_mode_index;
    bool unlocked;

    byte* zone_config;
    byte* input_config;

protected:
    void go_home() override;
    void go_up() override;
    void select_item(int dir) override;
    
public:
    HomePage();
    PMODE* Handle() { return arms; }

public:
    PMODE GetDisarm() { return arms[0]; }
    PMODE GetArm(int index = 0);
    void Activate() override;
    void Activate(int index);
    void Lock();
    void Unlock();
};

