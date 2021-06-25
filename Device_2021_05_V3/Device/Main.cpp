#include "Device.h"

Device device;

#define _screen_builder	device.ScreenBuilder
#define _content _screen_builder.content

int main() {

	//device = new Device();

	Device::SCREEN.Begin();
	Device::SCREEN.WakeUp();


	_screen_builder.UpdateTitle("TEST");
	_content.AddMenu(1, "ACT");
	_content.AddMenu(2, "PHONE");
	_content.AddMenu(3, "INPUT");
	_content.AddMenu(4, "PIN");
	_screen_builder.UpdateContent();
//	_screen_builder.Wait(30);

	System::Clock.Loop();
}