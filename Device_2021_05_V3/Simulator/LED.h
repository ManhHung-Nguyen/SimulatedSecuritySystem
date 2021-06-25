#pragma once
#ifdef WIN32
class LED {
protected:
	int x, y;
	bool high;
	virtual void draw();
public:
	LED(int x = 0, int y = 0) : x(x), y(y), high(false) { }
	void operator=(bool value) {
		high = value;
		draw();
	}
	void operator=(char value) {
		high = value == '1';
		draw();
	}
};
class RELAY : public LED {
protected:
	void draw() override;
public:
	RELAY(int x = 0, int y = 0) : LED(x, y) { }
};
#endif // WIN32

