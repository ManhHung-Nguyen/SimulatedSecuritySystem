#pragma once
#include "../BIOS/BIOS.h"
#include "LineBuilder.h"

class ContentBuilder : public Builder {
protected:
	int total;
	int first_index;
public:
	ContentBuilder()
		: total(0)
		, first_index(0)
		, Builder(32) {}
	ContentBuilder& operator+=(LPCHAR s) {
		if (it > data) {
			*it++ = 32;
		}
		Copy(s);
		*it = 0;

		return *this;
	}
	ContentBuilder& Restart();
public:
	bool TooLong() { return total > LCD_COLS; }
	void Clear() { total = 0; }
	void SetText(LPCHAR text) {
		Restart();
		Copy(text);

		total = it - data;
	}
	void AddMenu(int index, LPCHAR s);

	void Next();
	LPCHAR ToString() override;
};

class ScreenBuilder {
protected:
	void show_time(bool clear);
public:
	ScreenBuilder();
	ContentBuilder content;

public:
	void SetModified(bool b);
	void UpdateTitle(LPCHAR s);
	void UpdateTitle(LineBuilder& line);
	void UpdateContent(LPCHAR s = 0, int timeout = 0);
	
	void CountDown();
	void Wait(int timeout);
};

