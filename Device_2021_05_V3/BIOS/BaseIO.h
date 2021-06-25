#pragma once
class BaseIO {
protected:
	bool is_busy;
	int interrupt_number;
	virtual void interrupt(int wparam, int lparam);
	void interrupt(int param);
public:
	BaseIO() : interrupt_number(0), is_busy(false) {}
	void SetInterruptNumber(int i) {
		interrupt_number = i;
	}
};