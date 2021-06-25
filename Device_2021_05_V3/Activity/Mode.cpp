#include "Activity.h"
//#include "ARM.h"
#include "Mode.h"
#include "Constants.h"
#include "../Device/Device.h"

PMODE Mode::LastChild() const {
	PMODE p = Child;
	PMODE last = 0;

	while (p) {
		last = p;
		NEXT(p);
	}
	return last;
}

void Mode::Prepend(PMODE mode, LPCHAR main, LPCHAR sub) {
	if (main) mode->main_title = main;
	if (sub) mode->sub_title = sub;

	mode->Parent = this;
	mode->Sibling = Child;
	Child = mode;
}

void Mode::Append(PMODE mode, LPCHAR main, LPCHAR sub) {
	if (main) mode->main_title = main;
	if (sub) mode->sub_title = sub;

	mode->Parent = this;
	LastChild()->Sibling = mode;
}

void Mode::go_home() {
	Redirect(Activity::Home);
}

void Mode::go_up() {
	PMODE p = Parent;
	//if (p && p->Child->Sibling == 0) {
	//	p = p->Parent;
	//}
	Redirect(p);
}

void Mode::go_down(int index) {
	PMODE p = Child;
	while (p && index) {
		--index;
		NEXT(p);
	}
	if (p) { Redirect(p); }
}

void Mode::select_item(int direction) {
}

void Mode::on_number_key(int code) {
}

void Mode::on_del_key() {
}

void Mode::on_enter_key() {
	if (can_update()) {
		update_editing();
	}
}

bool Mode::can_update() {
	return false;
}

void Mode::update_editing() {
}

void Mode::on_activated() {
}

void Mode::show_main_title(LPCHAR title) {
	_screen_builder.UpdateTitle(title);
}

void Mode::show_join_title(LPCHAR postfix, LPCHAR prefix) {
	LineBuilder builder;
	if (prefix) {
		builder << prefix << " ";
	}
	builder << main_title;
	if (postfix) {
		builder << " " << postfix;
	}
	_screen_builder.UpdateTitle(builder);
}

void Mode::show_item_index(int index, LPCHAR prefix) {
	char num[3] = "#-";
	num[1] = (index + 1) | 48;

	show_join_title(num, prefix);
}

void Mode::show_content(LPCHAR content) {
	_screen_builder.UpdateContent(content);
}

void Mode::load_config() {
	if (Child) { Child->load_config(); }
	if (Sibling) { Sibling->load_config(); }
}

void Mode::show_message(LPCHAR content, Mode* next) {
	Message::Show(main_title, content, next == 0 ? this : next);
}

void Mode::ProcessKey(int code) {
	switch (code) {
	case Keys::STAR: go_home(); return;
	case Keys::SHARP: go_up(); return;
	case Keys::ENTER: on_enter_key(); return;
	case Keys::DEL: on_del_key(); return;
	case Keys::UP: select_item(-1); return;
	case Keys::DOWN: select_item(1); return;
	}
	on_number_key(code);
}

void Mode::Activate() {
	show_main_title(main_title);
	if (sub_title == 0) {
		sub_title = main_title;
	}
	show_content(sub_title);

	on_activated();
}

void Mode::Redirect(PMODE mode) {
	Activity::Select(mode);
}

Message Message::form;
void Message::Show(LPCHAR title, LPCHAR content, Mode* next) {
	form.Sibling = next;
	form.main_title = title;
	form.sub_title = content;
	form.Redirect(&form);
}
