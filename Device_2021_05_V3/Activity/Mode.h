#pragma once
#include "../System/BTree.h"
#include "Constants.h"

#define PMODE	Mode*
#define NEXT(mode) mode = mode->Sibling

class Mode {
public:
	LPCHAR main_title;
	LPCHAR sub_title;
	PMODE Child;
	PMODE Sibling;
	PMODE Parent;
public:
	Mode(LPCHAR title = 0, LPCHAR sub = 0)
		: main_title(title)
		, sub_title(sub) {
		Parent = Child = Sibling = 0;
	}
public:
	PMODE LastChild() const;
	void Prepend(PMODE mode, LPCHAR main = 0, LPCHAR sub = 0);
	void Append(PMODE mode, LPCHAR main = 0, LPCHAR sub = 0);
protected:
	virtual void go_home();
	virtual void go_up();
	virtual void go_down(int index);
	virtual void select_item(int direction);
	virtual void on_number_key(int code);
	virtual void on_del_key();
	virtual void on_enter_key();
	virtual bool can_update();
	virtual void update_editing();

	virtual void on_activated();
	virtual void show_main_title(LPCHAR title = 0);
	virtual void show_join_title(LPCHAR postfix = 0, LPCHAR prefix = 0);
	virtual void show_item_index(int index, LPCHAR prefix = 0);
	virtual void show_content(LPCHAR content);
	virtual void load_config();

	void show_message(LPCHAR content, Mode* next = 0);
public:
	virtual void ProcessKey(int code);
	virtual void Activate();
	virtual void Redirect(PMODE mode = 0);
};

class Message : public Mode {
	static Message form;
protected:
	void on_enter_key() override { Redirect(Sibling); }
public:
	static void Show(LPCHAR title, LPCHAR content, Mode* next = 0);
};