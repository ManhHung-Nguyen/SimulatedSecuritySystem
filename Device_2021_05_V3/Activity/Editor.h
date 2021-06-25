#pragma once
#include "Mode.h"
#include "../System/Builder.h"
#include "../Device/ScreenBuilder.h"
#include "Activity.h"

#define _editor Editor::Builder
#define _modified(b) (*Activity::MainDevice->Monitor)(LCD_COLS-1,0)<<(b?'*':' ')

class Mask {
public:
	static LPCHAR Password;
	static LPCHAR Phone;
	static LPCHAR Date;
	static LPCHAR Time;
	static LPCHAR ACT;
};

typedef byte (*screen_character)(byte);
typedef bool (*is_key_valid)(byte, byte, int);

class Editor {
	int first_index;
	int cursor_pos;
	int length;
	byte* data;
protected:
	virtual bool is_space(byte c);
	byte last_code() { return data[cursor_pos - 1] & 15; }
public:
	screen_character get_screen_char;
	is_key_valid is_valid;

	static Editor Builder;
	static byte* data_buffer;
public:
	Editor() {
		get_screen_char = 0;
		is_valid = 0;
	}
public:
	bool IsFull() {
		return cursor_pos >= length; 
	}
	bool IsEmpty() { return cursor_pos == first_index; }
public:
	void SetInputMask(LPCHAR mask);
	virtual void BeginEdit();
	
	int Peek();
	void Push(int code);
	void Pop();
	virtual byte* EndEdit(byte* dst = 0);
protected:
	int get_mark_screen_pos(int code) { return (code << 1) + code + 1; }
public:
	void Mark(int code);
	void Unmark(int code);
	void ToggleMark(int code);
};
