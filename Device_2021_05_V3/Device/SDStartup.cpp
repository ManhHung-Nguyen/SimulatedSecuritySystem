#include "SDStartup.h"
#include "Device.h"

void SDStartup::on_count_down() {
	_with_duration{
		case 1:
			Device::CLIENT_ID.GetExisting();
			return;
	}
}
