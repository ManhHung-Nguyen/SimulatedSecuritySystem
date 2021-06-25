//#include "../simulator/LCD.h"
//#include "../System/System.h"
//
//#ifdef WIN32
//#include "LED.h"
//#include "../BIOS/BIOS.h"
//#include <Windows.h>
//
//#define LCD_LEN	(LCD_COLS + 2) * (LCD_ROWS + 2)
//
//#define	X0			4
//#define	Y0			2
//#define LCD_X0		X0 + 5
//#define LCD_Y0		Y0 + 1
//
//
//HANDLE handle;
//
//int textColor, backColor;
//void show_cursor(bool b) {
//	CONSOLE_CURSOR_INFO info;
//	GetConsoleCursorInfo(handle, &info);
//
//	info.dwSize = 100;
//	info.bVisible = b;
//	SetConsoleCursorInfo(handle, &info);
//}
//void move_cursor(int x, int y) {
//	COORD coord;
//	coord.X = x;
//	coord.Y = y;
//
//	SetConsoleCursorPosition(handle, coord);
//}
//void begin_write() {
//	SetConsoleTextAttribute(handle, (backColor << 4) | textColor);
//}
//
//void write_led(int r, int c, int v) {
//	int x = X0 - 2 + c * 4;
//	int y = Y0 + r * 2;
//	move_cursor(x, y);
//	if (v) {
//		SetConsoleTextAttribute(handle, 10);
//	}
//	SetConsoleTextAttribute(handle, 7);
//}
//void set_color(int t, int b) {
//	textColor = t;
//	backColor = b;
//	begin_write();
//}
//
//const int default_text_color = 15;
//const int default_back_color = 9;
//
//void LCD::drawRow(int y, int left, int mid, int right) {
//	if (right == 0) { right = left; }
//
//	setCursor(-1, y - 1); log << (char)left;
//	for (int i = 0; i < 16; i++) log << (char)mid;
//	log << (char)right;
//}
//void LCD::clear_gui() {
//	begin_write();
//	drawRow(0, 201, 205, 187);
//	for (int i = 0; i < LCD_ROWS; i++) {
//		clear(i);
//	}
//	drawRow(3, 200, 205, 188);
//}
//void LCD::init() {
//	handle = GetStdHandle(STD_OUTPUT_HANDLE);
//	textColor = default_text_color;
//	backColor = default_back_color;
//	clear_gui();
//}
//void LCD::setCursor(int x, int y) {
//	move_cursor(LCD_X0 + x, LCD_Y0 + y);
//}
//void LCD::clear() {
//	clear_gui();
//	setCursor(0, 0);
//}
//void LCD::clear(int y) {
//	drawRow(y + 1, 186, 32);
//}
//void LCD::print(LPCHAR s) {
//	begin_write();
//	log << s;
//}
//void LCD::print(const char c) {
//	begin_write();
//	log << c;
//}
//void LCD::blink() { show_cursor(true); }
//void LCD::noBlink() { show_cursor(false); }
//
//void LCD::light(bool on) {
//	int fg = default_text_color;
//	int bg = default_back_color;
//	if (!on) {
//		fg = 15 - fg;
//		bg = 15 - bg;
//	}
//
//	if (textColor != fg) {
//
//		textColor = fg;
//		backColor = bg;
//
//		CHAR_INFO buffer[LCD_LEN];
//		COORD size = { LCD_COLS + 2, LCD_ROWS + 2 };
//		COORD coord = { 0, 0 };
//		SMALL_RECT rc = { LCD_X0 - 1, LCD_Y0 - 1,
//			LCD_X0 + size.X - 1, LCD_Y0 + size.Y - 1 };
//
//		bool res = ReadConsoleOutput(
//			handle,
//			buffer,
//			size,
//			coord,
//			&rc
//		);
//
//		int a = (bg << 4) | fg;
//		for (int i = 0; i < LCD_LEN; i++) {
//			buffer[i].Attributes = a;
//		}
//
//		WriteConsoleOutput(handle, buffer, size, coord, &rc);
//	}
//}
//
//void LED::draw() {
//	move_cursor(X0 + x, Y0 + y);
//	SetConsoleTextAttribute(handle, high ? 10 : 7);
//	log << (char)254;
//}
//
//void RELAY::draw() {
//	move_cursor(X0 + x, Y0 + y);
//	SetConsoleTextAttribute(handle, high ? 12 : 9);
//	log << (char)219 << (char)219;
//}
//LED* leds[] = {
//	new LED(1, 0),
//	new LED(1, 1),
//	new LED(1, 2),
//	new LED(1, 3),
//	new LED(24, 0),
//	new LED(24, 1),
//	new LED(24, 2),
//	new LED(24, 3),
//	new RELAY(8, 5),
//	new RELAY(11, 5),
//	new RELAY(14, 5),
//	new RELAY(17, 5),
//};
//
//#define LEFT_LED_COUNT	4
//#define RIGHT_LED_COUNT	4
//#define RELAY_COUNT		4
//
//void digitalWrite(int pin, int value) {
//	*leds[pin] = (value != 0);
//}
//#endif
