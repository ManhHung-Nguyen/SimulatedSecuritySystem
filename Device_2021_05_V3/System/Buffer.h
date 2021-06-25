#pragma once
#include "Types.h"

class Buffer {
protected:
	byte* data;
	int capacity;
	static	byte* it;
public:
	Buffer();
	Buffer(int size);
	Buffer(byte* handle, int size)
		: data(handle)
		, capacity(size) {
		it = data;
	}
	Buffer(const Buffer& src)
		: data(src.data)
		, capacity(src.capacity) {
		it = data;
	}
public:
	int Position() const { return it - data; }
	byte* Seekp(int position) { return it = data + position; }
	byte* Handle() const { return data; }

	int Capacity() const { return capacity; }
	void Reset(byte value = 0);
	Buffer& Restart() {
		it = data;
		*it = 0;

		return *this;
	}
	Buffer& Seek(int position) {
		it = data + position;
		return *this;
	}
	Buffer& Offset(int disp) { it = (data += disp); return *this; }
	Buffer& Resize(int size) { capacity = size; return *this; }
	Buffer& Mapping(const Buffer& src) {
		it = data = src.data;
		capacity = src.capacity;
		
		return *this;
	}
	Buffer& Mapping(byte* handle) {
		it = data = handle;
		return *this;
	}
public:
	void Copy(const byte* source, int length);
	void Copy(LPCHAR source);
public:
	byte& operator++() { return *(++it); }
	byte& operator++(int) { return *it++; }
	byte& operator--() { return *(--it); }
	byte& operator--(int) { return *it--; }
	byte& operator*() { return *it; }
	byte& operator[](int index) { return *(Handle() + index); }

public:
	template<class T> LPCHAR Convert(T number) {
		byte* p = data + capacity;
		T a = number < 0 ? -number : number;

		*(--p) = 0;
		do {
			*(--p) = (a % 10) | 0x30;
			a /= 10;
		} while (a);
		if (number < 0) *(--p) = '-';

		return LPCHAR(p);
	}
	friend byte* begin(const Buffer& obj) { return obj.data; }
	friend byte* end(const Buffer& obj) { return obj.data + obj.capacity; }
};

class Memory : public Buffer {
	int available;
public:
	Memory();
	Memory(int size);
	Memory(byte* src, int size) 
		: Buffer(src, size)
		, available(size) {}
	Memory(const Memory& src) 
		: Buffer(src)
		, available(src.capacity) {}
public:
	int Available() const { return available; }
public:
	byte* Malloc(int size) {
		return data + (available -= size);
	}
	byte* Malloc(Buffer& buffer) {
		int sz = buffer.Capacity();
		byte* handle = Malloc(sz);
		buffer.Mapping(handle);

		return handle;
	}
};

class Array : Buffer {
public:
	Array(int length) : Buffer(length << 2) {
		it = data;
	}
	Array(byte* handle, int length) 
		: Buffer(handle, length << 2) {
		it = data;
	}
	Array(const Array& src) : Buffer(src) {
		it = data;
	}

	int Size() const { return capacity >> 2; }
	void Resize(int length) { capacity = (length << 2); }
	void Reset() { Buffer::Reset(); }
public:
	int GetAt(int index) const { return *(int*)(data + (index << 2)); }
	void SetAt(int index, int value) {
		*(int*)(data + (index << 2)) = value;
	}
	int& operator++() { return *(int*)(it += 4); }
	int& operator++(int) {
		int& v = *(int*)it;
		it += 4;
		return v;
	}
	int& operator[](int index) {
		return *(int*)(data + (index << 2));
	}

	void operator+=(void* item);
	void operator-=(void* item);
	
	template <class T> static T& Cast(int value) {
		return *(T*)value;
	}
	static int Cast(void* value) {
		return int((int*)value);
	}

	friend int* begin(const Array& obj) { return (int*)obj.data; }
	friend int* end(const Array& obj) { return (int*)(obj.data + obj.capacity); }
};