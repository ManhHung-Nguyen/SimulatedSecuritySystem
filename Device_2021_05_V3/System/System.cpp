#include "System.h"

interrupt_ptr int_table[16];

Memory System::DRAM;
SysClock System::Clock;
ExecUnit System::EU;

void System::IReg(int number, interrupt_ptr proc) {
	int_table[number] = proc;
}

void System::ICall(int number, int w, int l) {
	interrupt_ptr proc = int_table[number];
	proc(w, l);
}
