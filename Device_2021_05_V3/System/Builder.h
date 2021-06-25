#pragma once
#include "Buffer.h"
class Builder : public Buffer {
public:
    Builder() {}
    Builder(int size) : Buffer(size) {}
    Builder(LPCHAR s) { Copy(s); }

public:
    bool Contains(byte c) const { return IndexOf(c) >= 0; }
    bool Contains(LPCHAR s) const { return IndexOf(s) >= 0; }

    int IndexOf(byte c, int startIndex = 0) const;
    int IndexOf(LPCHAR s, int startIndex = 0) const;
    
    Builder& ToUpper();
    Builder& ToLower();

    static int Compare(LPCHAR s1, LPCHAR s2);

    void operator=(LPCHAR s) { Seek(0).Copy(s); }
    Builder& operator << (LPCHAR s) {
        Copy(s);
        return *this;
    }
    Builder& operator << (int number) {
        Copy(Convert(number));
        return *this;
    }
    
    void CopyTo(byte* dst);
    void CopyTo(PCHAR dst) { CopyTo((byte*)dst); }

public:
    virtual LPCHAR ToString() {
        return LPCHAR(Handle());
    }
    operator LPCHAR () {
        return ToString();
    }
};

class ListBuilder : public Builder {
protected:
    void* end_param() { *it = ','; return this; }
    void* add(LPCHAR param) {
        *(++it) = '\"';
        it++;
        Copy(param);
        *it++ = '\"';
        return end_param();
    }
    void* add(int param) {
        it++;
        Copy(Convert(param));
        return end_param();
    }
    virtual char get_close_tag() = 0;
    virtual void set_open_tag() {}
public:
    LPCHAR ToString() override {
        if (*it != ',') {
            it++;
        }
        *it++ = get_close_tag();
        *it = 0;

        set_open_tag();
        return (LPCHAR)Handle();
    }
};

class FunctionBuilder : public ListBuilder {
protected:
    char get_close_tag() override { return ')'; }
public:
    FunctionBuilder& operator()(LPCHAR name) {
        it = Handle();
        Copy(name);

        *it = '(';
        return *this;
    }
    FunctionBuilder& operator<<(LPCHAR param) {
        return *(FunctionBuilder*)add(param);
    }
    FunctionBuilder& operator<<(int param) {
        return *(FunctionBuilder*)add(param);
    }
};

class ObjectBuilder : public ListBuilder {
protected:
    char get_close_tag() override { return '}'; }
    void set_open_tag() override { *Handle() = '{'; }
public:
    ObjectBuilder& operator<<(LPCHAR value) {
        if (*it != ':') {
            return this->operator[](value);
        }
        add(value);
        return *this;
    }
    ObjectBuilder& operator<<(int value) {
        if (*it != ':') {
            return this->operator[](Convert(value));
        }
        add(value);
        return *this;
    }
    ObjectBuilder& SetValue(LPCHAR key, Builder& value) {
        this->operator[](key);

        it++;
        Copy(LPCHAR(value.Handle()));
        end_param();

        return *this;
    }

    ObjectBuilder& operator[](LPCHAR name) {
        add(name);
        *it = ':';
        return *this;
    }
    void operator=(LPCHAR param) {
        add(param);
    }
    void operator=(int param) {
        add(param);
    }
};

class ArrayBuilder : public ListBuilder {
protected:
    char get_close_tag() override { return ']'; }
    void set_open_tag() override { *Handle() = '['; }
public:
    ArrayBuilder& operator<<(LPCHAR param) {
        return *(ArrayBuilder*)add(param);
    }
    ArrayBuilder& operator<<(int param) {
        return *(ArrayBuilder*)add(param);
    }
};

#include "Clock.h"
class TimeBuilder : public Builder {
    byte* date_time() { return data + 10; }
    void set_value(int value, int pos);

public:
    TimeBuilder();

    TimeBuilder& SetDate(int year, int month, int day) {
        set_value(year, 0);
        set_value(month, 1);
        set_value(day, 2);

        return *this;
    }
    TimeBuilder& SetTime(int hour, int minute, int second) {
        set_value(hour, 3);
        set_value(minute, 4);
        set_value(second, 5);

        return *this;
    }
    TimeBuilder& FormatCurrentTime(const SysClock& clock) {
        SetDate(clock.GetYear(), clock.GetMonth(), clock.GetDay());
        SetTime(clock.GetHour(), clock.GetMinute(), clock.GetSecond());

        return *this;
    }
public:

    LPCHAR Time() { return (LPCHAR)(date_time() + 1); }
    LPCHAR Date(char seperator = 0) {
        *(date_time()) = seperator;
        return (LPCHAR)data;
    }
    LPCHAR DateTime() { return Date(' '); }
    LPCHAR DateTimeODA() { return Date('T'); }
};
