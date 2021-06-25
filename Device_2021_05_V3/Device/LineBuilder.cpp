#include "LineBuilder.h"
#include "Device.h"

byte LineBuilder::LineWidth = 16;
LineBuilder::LineBuilder(int index)
	: Builder(LineWidth + 1)
	, line_index(index) {
	Mapping(data + (capacity * line_index));
}
LPCHAR LineBuilder::ToString() {
	int len = LineWidth;
	byte* handle = Handle();
	byte* end = handle + len;
	while (it < end) {
		*it++ = 32;
	}
	handle[len] = 0;
	return LPCHAR(handle);
}

void LineBuilder::Write() {
	Device::SCREEN(line_index) << ToString();
}
