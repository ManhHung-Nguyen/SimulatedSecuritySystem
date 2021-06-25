#include "Constants.h"
#include "Clock.h"
#include "Builder.h"

#define _value(i)	items[i].value
#define _event(i)	items[i].callback
#define _lim(i)		items[i].limit
#define _milis		_value(MILIS)
#define _sec		_value(SECOND)
#define _min		_value(MINUTE)
#define _hour		_value(HOUR)
#define _day		_value(DAY)
#define _month		_value(MONTH)
#define _year		_value(YEAR)

#define CENTURY			2000
#define MAX_COUNTERS	16

//byte counter_address[MAX_COUNTERS << 2];
//class CounterList : public Array {
//public:
//	CounterList() : Array(counter_address, MAX_COUNTERS) {}
//} counters;

Counter* counters[MAX_COUNTERS];
int n_counter = 0;

void SysClock::increase_item(int index) {
	int v = _value(index) + 1;
	if (v == _lim(index)) {
		v = 0;
		if (index == HOUR) {
			if (++week_day == 7) {
				week_day = 0;
			}
		}
		else if (index == MONTH && v == 1) { // thang 2
			_lim(DAY) = days_of_month(GetYear(), GetMonth());
		}
	}
	_value(index) = v;
	if (v == 0) {
		increase_item(index - 1);
	}
	if (_event(index)) {
		_event(index)();
	}
}

void SysClock::on_milisecond() {
	/*for (auto x : counters) {
		if (x == 0) return;

		--Array::Cast<Counter>(x);
	}*/

	for (int i = 0; i < n_counter; i++) {
		counters[i]->operator--();
	}
}

SysClock::SysClock()
	: on_one_circle(0)
	, week_day(-1) {

	items[YEAR] = { -1, 0, 0 };
	items[MONTH] = { 12, 0, 0 };
	items[DAY] = { 0, 0, 0 };
	items[HOUR] = { 24, 0, 0 };
	items[MINUTE] = { 60, 0, 0 };
	items[SECOND] = { 60, 0, 0 };
	items[MILIS] = { MILISECOND_LIMIT, 0, 0 };
}

#include "Log.h"
void SysClock::operator+=(Counter* counter) {
	//CounterList lst;
	//lst += (void*)counter;
	counters[n_counter++] = counter;
}

void SysClock::operator-=(const Counter* counter) {
	//counters -= (void*)counter;
}

int SysClock::days_of_month(int year, int month) {
	switch (month) {
	case 2: return year & 3 ? 28 : 29;
	case 4: case 6: case 9: case 11: return 30;
	}
	return 31;
}

int SysClock::day_of_week(int year, int month, int day) {
	int d = year - CENTURY;
	int i = (d + ((d - 1) >> 2));

	while (--month) {
		i += days_of_month(year, month);
	}
	return (i + day - 1) % 7;
}
LPCHAR SysClock::Time() const {
	TimeBuilder builder;
	builder.SetTime(_hour, _min, _sec);
	return builder.Time();
}
LPCHAR SysClock::Date() const {
	TimeBuilder builder;
	builder.SetDate(_year, _month, _day);
	return builder.Date();
}
void SysClock::SetTime(int h, int m, int s) {
	_hour = h;
	_min = m;
	_sec = s;
}
void SysClock::SetDate(int day, int month, int year) {
	if (year < CENTURY) { year += CENTURY; }
	_day = day - 1;
	_month = month - 1;
	_year = year;

	if (month == 2) {
		_lim(DAY) = year & 3 ? 29 : 28;
	}
	week_day = day_of_week(year, month, day);
}

bool SysClock::TrySetDate(int day, int month, int year)
{
	if (0 >= month || month > 12 || 0 >= day || year < 0) {
		return false;
	}

	if (days_of_month(year, month) >= day) {
		SetDate(day, month, year);
		return true;
	}
	return false;
}
int SysClock::GetYear() const { return _year; }
int SysClock::GetMonth() const { return _month + 1; }
int SysClock::GetDay() const { return _day + 1; }
int SysClock::GetHour() const { return _hour; }
int SysClock::GetMinute() const { return _min; }
int SysClock::GetSecond() const { return _sec; }
int SysClock::GetMilis() const { return _milis; }

void SysClock::SetEvent(int index, ins_ptr event) { 
	_event(index) = event; 
}

