#include "ScreenBuilder.h"
#include "Device.h"

int wakeup_timeout = 5;
char content_template[32];

//int ContentBuilder::find_next_word() {
//	int i = first_index + 1;
//	while (i < total) {
//		switch (data[i++]) {
//		case 0: return 0;
//		case 32: return i;
//		}
//	}
//	return 0;
//}

ContentBuilder& ContentBuilder::Restart() {
	Mapping((byte*)content_template);
	total = 0;
	first_index = 0;

	return *this;
}
void ContentBuilder::AddMenu(int index, LPCHAR s) {
	if (index == 1) {
		Restart();
	}
	else {
		*it++ = ' ';
	}
	(*this) << index << "-" << s;
	total = it - data;
}

void ContentBuilder::Next() {
	int i = IndexOf(32, first_index + 1);
	first_index = i < 0 ? -1 : i;

	LineBuilder line;
	line.Copy((LPCHAR)(data + first_index + 1));

	Device::SCREEN(1) << line.ToString();
}

LPCHAR ContentBuilder::ToString() {
	LineBuilder line = LineBuilder(1);
	line.Copy(content_template);

	return line.ToString();
}

bool is_long_text(LPCHAR s) {
	for (int i = 0; i < LCD_COLS; i++) {
		if (s[i] == 0) return false;
	}
	return true;
}

ScreenBuilder::ScreenBuilder() {
}

void ScreenBuilder::SetModified(bool b) {
	Device::SCREEN(15, 0) << (b ? '*' : ' ');
}

void ScreenBuilder::UpdateTitle(LPCHAR s) {
	LineBuilder line;
	line.Copy(s);
	UpdateTitle(line);
}

void ScreenBuilder::UpdateTitle(LineBuilder& line) {
	Device::SCREEN(0) << line.ToString();
}

void ScreenBuilder::UpdateContent(LPCHAR s, int timeout) {
	if (s != 0) {
		content.SetText(s);
	}

	Device::SCREEN(1) << content.ToString();
	Device::SCREEN.WakeUp();

	if (timeout == 0) {
		timeout = content.TooLong() ? 8 : 4;
	}
	Wait(timeout);
}

void ScreenBuilder::Wait(int timeout) {
	wakeup_timeout = timeout;
}

void ScreenBuilder::CountDown() {

	if (wakeup_timeout < 0) {
		if (++wakeup_timeout == 0) {
			System::ICall(INT_MONITOR, -1);
		}
		show_time(false);
		return;
	}
	if (wakeup_timeout == 0) {
		show_time(false);
		return;
	}
	if (--wakeup_timeout == 0) {
		content.Clear();

		System::ICall(INT_MONITOR, -1);
		show_time(true);
		return;
	}

	if (content.TooLong()) {
		content.Next();
	}
}

void ScreenBuilder::show_time(bool clear) {
	LPCHAR s = System::Clock.Time();
	if (clear) {
		content.Restart().Copy(s);
		s = content.ToString();
	}
	Device::SCREEN(1) << s;
}
