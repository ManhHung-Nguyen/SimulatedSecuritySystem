#pragma once
#include "../System/System.h"

class HardDisk : public Builder {
public:
	HardDisk(int size = 512)
		: Builder(size) {}

public:
	virtual HardDisk& Read(LPCHAR file_name, int size = 0);
	virtual void Write(LPCHAR file_name, int offset = 0, int size = 0);
	virtual void Write(LPCHAR file_name, LPCHAR s);
	virtual void Append(LPCHAR file_name, int size = 0);
};

