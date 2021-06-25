#pragma once
#include "../System/System.h"
#include "SerialPort.h"

class ATBuilder : public Builder {
	byte* di;
public:
	//void on_tick() override;
	void send_byte(byte b);
	void on_completed();
public:
	ATBuilder();
	void Start();
	void Ready();
public:
	ATBuilder& operator<<(int delay);
	ATBuilder& operator<<(LPCHAR content);

	ATBuilder& operator&(int value);
	ATBuilder& operator&(LPCHAR content);

};

//template <class T>
class SimCard : public SerialPort<SoftwareSerial>, public Counter {
protected:
	void on_tick() override {
		byte* end = AT.Handle() + AT.Capacity();

		while (di < end) {
			byte b = *di++;
			port.write(b);
			if (b == '\n') {
				Counter::Reset(*di++);
				if (duration == 0) {
					AT.on_completed();
				}
				break;
			}
		}
	}

public:
	ATBuilder AT;
	void SendAT() {
		AT.Ready();
		di = AT.Handle();

		Counter::Reset(1);

	}
	void SendAT(LPCHAR command) {
		AT.Start();
		AT << command;
		SendAT();

	}
public:
	void Init() {}
};

