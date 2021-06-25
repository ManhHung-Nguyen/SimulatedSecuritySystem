#pragma once
#pragma once
#include "../BIOS/BIOS.h"
#include "../System/System.h"
#include <Windows.h>

#define _eu System::EU
#define _args System::EU.Args()


class Simulator {
	static LPCHAR bin_path(LPCHAR name);
public:
	static byte* Read(LPCHAR name, int size = 0);
	static void Write(LPCHAR name, LPCHAR content);

	static HardDisk& File(LPCHAR name);

	static bool Receive();
	static void Send(LPCHAR action, LPCHAR value = 0, LPCHAR id = 0);
};
