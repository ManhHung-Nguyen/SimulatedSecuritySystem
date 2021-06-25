#include "Internet.h"
#include "../System/Buffer.h"
#include "../Device/Device.h"

void Internet::on_count_down() {
	_with_duration{
		case 5: Connect(); return;
		
		case 4: if (is_connected()) {
			Device::LEDS.SetBit(1);

			start_listener();

			if (Device::CLIENT_ID.IsEmpty()) {
				Request("manage/deviceID");
			}
		} return;

		case 3: return;

		case 2:
			Request("manage/time");
			return;
	}
}

void Internet::Request(LPCHAR url, LPCHAR value) {
	ObjectBuilder js;
	js << "url" << url;
	if (value) {
		js << "value" << value;
	}
	Send(js);
}