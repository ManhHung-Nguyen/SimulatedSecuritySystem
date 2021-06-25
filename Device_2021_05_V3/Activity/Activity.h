#pragma once

#include "Menu.h"
#include "Alarm.h"
#include "Config.h"
#include "Constants.h"
#include "../System/System.h"
#include "../Device/Device.h"


#define _screen_builder	Device::ScreenBuilder
#define _content _screen_builder.content
#define _edit_line(x) (Device::SCREEN(x, 1))
#define _clock System::Clock
#define _set_modify(b) _screen_builder.SetModified(b)

#define _home (*(HomePage*)Activity::Home)
#define _current_mode (Activity::CurrentMode)

class Activity {
public:
	static PMODE CurrentMode;
	static PMODE FirstMenu;
	static PMODE LoginForm;
	static PMODE Home;
	static Alarm ALARM;
public:
	static void Begin();
	static void Select(PMODE mode);
	static void GoHome() { Select(Home); }
	static void Login(PMODE next = 0);
public:
};