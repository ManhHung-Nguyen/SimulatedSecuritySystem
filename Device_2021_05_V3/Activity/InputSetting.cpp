#include "InputSetting.h"
#include "Act.h"

int InputSetting::GetOutputMask(int index) {
	byte* org = data;
	data += index * get_item_data_size();

	int mask = GetValueMask();
	data = org;
	return mask;
}
