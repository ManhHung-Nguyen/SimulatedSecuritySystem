#pragma once

typedef unsigned char byte;
typedef char* PCHAR;
typedef const char* LPCHAR;

typedef void(*ins_ptr)();
typedef void (*interrupt_ptr)(int, int);