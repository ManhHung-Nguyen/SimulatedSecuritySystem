#pragma once
#include "Types.h"
#include "Counter.h"

extern int get_milisecond_circle();

enum ClockItem { YEAR, MONTH, DAY, HOUR, MINUTE, SECOND, MILIS };
class SysClock {
    struct clock_item {
        int limit;
        int value;
        ins_ptr callback;
    } items[7];

protected:
    void increase_item(int index);
    void on_milisecond();
public:
    ins_ptr on_one_circle;
public:
    SysClock();
    void Loop() {
        int value = get_milisecond_circle();

        while (true) {
            if (on_one_circle) {
                on_one_circle();
            }
            if (--value == 0) {
                on_milisecond();

                increase_item(MILIS);
                value = get_milisecond_circle();
            }
        }
    }
public:
    void operator+=(Counter* counter);
    void operator-=(const Counter* counter);

protected:
    int week_day;
public:
    static int days_of_month(int year, int month);
    static int day_of_week(int year, int month, int day);
public:
    LPCHAR Time() const;
    LPCHAR Date() const;

    void SetEvent(int index, ins_ptr event);

    void SetDate(int day, int month, int year);
    bool TrySetDate(int day, int month, int year);
    void SetTime(int hour, int minute, int second);

    int GetWeekDay() const { return week_day; }
    int GetYear() const;
    int GetMonth()const;
    int GetDay() const;
    int GetHour()const;
    int GetMinute()const;
    int GetSecond() const;
    int GetMilis() const;

};

