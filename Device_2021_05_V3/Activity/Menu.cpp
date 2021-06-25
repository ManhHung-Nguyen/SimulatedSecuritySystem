#include "Menu.h"
#include "Activity.h"
#include "../Device/Device.h"

void Menu::show_content(LPCHAR content) {
	PMODE p = Child;
	int index = 0;
	while (p) {
		LPCHAR text = p->sub_title;
		if (!text) { text = p->main_title; }
		if (!text) { text = "NULL"; }

		_content.AddMenu(++index, text);
		NEXT(p);
	}
	_screen_builder.UpdateContent();
}

void Menu::on_number_key(int code) {
	if (code > Keys::N0) {
		go_down(code - Keys::N1);
	}
}

MainMenu::MainMenu() : Menu("MENU") {
	//Prepend(new Menu(), "DISARM");
	//Prepend(new Menu(), "ARM 2", "ARM2");
	//Prepend(new Menu(), "ARM 1", "ARM1");
	//Append(new Menu(), "INPUT");
}
void MainMenu::MappingData() {
	load_config();
}
