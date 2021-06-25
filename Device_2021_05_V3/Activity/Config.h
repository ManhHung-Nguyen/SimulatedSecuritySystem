#pragma once
#include "../System/System.h"

class ConfigManager
{
public:
	static byte* GetBuffer(int size);
	//static void Save(Buffer* buffer);
public:
	static void Load();
	static void Save();
};

