#include "Activity.h"
#include "Home.h"
#include "ARM.h"
#include "Editor.h"
#include "InputSetting.h"
#include "PinCode.h"
#include "PhoneSetting.h"
#include "Plan.h"
#include "DateTimeSetting.h"
#include "../Device/Device.h"

PMODE Activity::CurrentMode = 0;
PMODE Activity::FirstMenu = 0;
PMODE Activity::LoginForm = 0;
PMODE Activity::Home;
Alarm Activity::ALARM;

void key_action(int code, int param) {
	Device::SCREEN.WakeUp();
	Activity::CurrentMode->ProcessKey(param);

	Device::KEYBOARD.Refresh();
}
void monitor_action(int code, int param) {
	switch (code) {
	case -1:
		_home.Lock();
		Device::SCREEN.Sleep();	
		return;
	}
	
}
void on_input_action(int wparam, int lparam) {
	switch (wparam)
	{
	case 1:
		Activity::ALARM.CheckZone(lparam);
		break;
	case 2:
		Activity::ALARM.CheckInput(lparam);
		break;
	}
}
void on_beam_action(int addres, int param) {

}


void Activity::Begin() {

	System::Reset();
	System::IReg(INT_KEYBOARD, key_action);
	System::IReg(INT_MONITOR, monitor_action);
	System::IReg(INT_INPUT, on_input_action);

	Device::TurnOn();

	ConfigManager::Load();

	FirstMenu = new MainMenu();
	LoginForm = new EnterPinCode();
	Home = new HomePage();

	
	FirstMenu->Prepend(LoginForm->Child, 0, "PIN");
	PMODE phone = new Menu();
	FirstMenu->Prepend(phone, "PHONE");
	phone->Prepend(ALARM.CALL = new CallSetting(), "CALL");
	phone->Prepend(ALARM.SMS = new SmsSetting(), "SMS");


	PMODE date_setting = new Menu("DATE TIME", "TIME");
	date_setting->Prepend(new TimeSetting(), "TIME");
	date_setting->Prepend(new DateSetting(), "DATE");		
	FirstMenu->Prepend(date_setting);

	PMODE act = new Menu("ACT");
	act->Prepend(ALARM.OUTPUTS = new InputSetting(), "INPUT");
	act->Prepend(_home.GetDisarm(), "DISARM");
	act->Prepend(_home.GetArm(2), "ARM 2", "ARM2");
	act->Prepend(_home.GetArm(1), "ARM 1", "ARM1");
	FirstMenu->Prepend(act);

	(*(MainMenu*)FirstMenu).MappingData();


	//Login();
	//Select(Home);

	System::Clock.Loop();
}

void Activity::Select(PMODE mode) {
	
	if (mode == 0) { mode = FirstMenu; }
	CurrentMode = mode;
	mode->Activate();
}

void Activity::Login(PMODE next) {
	LoginForm->Sibling = next;
	Select(LoginForm);
}