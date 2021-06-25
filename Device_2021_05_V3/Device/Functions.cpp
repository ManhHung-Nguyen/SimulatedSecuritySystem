#include "Device.h"
#include "../System/System.h"
#include "../Activity/Config.h"

/*
>> DIS()
>> ARM(1)
>> ARM(2)
>> DIS()
>> ARM(1)
>> DIS()
>> DIS()
>> TIME(2021,3,15,4,20,0)
>> PLAN(0,255,255)
>> PLAN(1,0,255,255)
>> PLAN(1,0,255,255)
>> PLAN(1,0,255,255)
>> PLAN(1,0,255,255)
>> PLAN(1,0,255,255)
>> PLAN(1,1,255,255)
>> PLAN(1,1,12,30)
>> PLAN(1,2,15,0)
>> AACT(1,1100)
>> IACT(0,1000)
>> IACT(1,0100)
>> IACT(2,0010)
>> IACT(3,0001)
>> IACT(0,1000)
>> AACT(1,1100)
>> IACT(2,0010)
>> IACT(1,0100)
>> IACT(2,0010)
>> IACT(3,0001)
>> TIME(2021,3,16,2,47,0)
>> SMS(1,-)
>> SMS(1,-)
>> SMS(1,989154248)
>> CALL(1,989154248)
>> CALL(2,123456789)
>> CALL(3,987654321)
>> CALL(2,-)
>>
*/


#define _eu System::EU
#define _args System::EU.Args()

/// <summary>
/// Tham so: 1 - ARM AWAY, 2 - ARM HOME
/// </summary>
void Device::ArmON()
{
    //int index = eu();
    //Arm::Activate(Arm::GetArmMode((arms)index));
}

void Device::ArmOFF()
{
    //Arm::Activate(DISARM_MODE);
}

/// <summary>
/// Nam, Thang, Ngay, Gio, Phut, Giay
/// </summary>
void Device::Time()
{
    int y, M, d, h, m, s;
    _eu >> y >> M >> d >> h >> m >> s;

    System::Clock.SetDate(d, M, y);
    System::Clock.SetTime(h, m, s);
}


/// <summary>
/// Tham so 1: mode (1 - ARM AWAY, 2 - ARM HOME, 3 - DISARM)
/// Tham so 2: thu (1 - CN, 2 - 7: CN, T2 - T7)
/// Tham so 3: Gio
/// Tham so 4: Phut
/// </summary>
void Device::PLAN()
{
    //Arm* mode = Arm::GetArmMode((arms)(int)eu());
    //Plan* plan = (Plan*)(mode->Schedule);

    //plan->SetTime(eu(1), eu(2), eu(3));
    //Config::Save();
}

void set_act(byte* it, const char* s) {
    for (int i = 0; char c = s[i]; i++) {
        *it++ = c == '0' ? 0 : 255;
    }
    ConfigManager::Save();
}

/// <summary>
/// Tham so 1: 1 - ARM AWAY, 2 - ARM HOME
/// Tham so 2: chuoi 01
/// </summary>
void Device::ArmInputAction() {
    //Arm* mode = Arm::GetArmMode((arms)(int)eu());
    //set_act(mode->Setting->Handle(), eu(1));
}

/// <summary>
/// Tham so 1: INPUT index (tu 1 - 4)
/// Tham so 2: chuoi 01
/// </summary>
void Device::InputOutputAction() {
    //InputSetting* setting = (InputSetting*)inputScanner.Setting;
    //byte* it = setting->Seek(OUTPUT_COUNT * ((int)eu() - 1));
    //set_act(it, eu(1));
}

/// <summary>
/// Tham so 1: (1 - 5)
/// Tham so 2: chuoi 9 so hoac - de xoa
/// </summary>
void setPhoneNumber(void* setting) {
    //char* s = eu(1);
    //if (s[0] == '-') { s = 0; }
    //(*(PhoneNumber*)setting).SetNumber((int)eu() - 1, s);
}

void Device::SetSmsNumber() {
    //setPhoneNumber(Config::SmsSetting);
}

void Device::SetCallNumber() {
    //setPhoneNumber(Config::CallSetting);
}