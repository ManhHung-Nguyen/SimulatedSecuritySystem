#pragma once
#include "../BIOS/BIOS.h"
#include "../Communication/Communication.h"
#include "ScreenBuilder.h"
#include "ClientID.h"
#include "Sensors.h"

#define INT_INPUT	7
#define INT_BEAM	8

enum Keys { N0, N1, N2, N3, N4, N5, N6, N7, N8, N9, STAR, SHARP, UP, DOWN, DEL, ENTER };

class Device {
public:
	static SimCard SIM;
	static MqttEngine MQTT;
	static Monitor SCREEN;
	static Keyboard KEYBOARD;
	static DigitalPort RELAYS;
	static OutPort LEDS;
	static Sensors INPUTS;
	static Beam BEAM;
public:
	static ScreenBuilder ScreenBuilder;
protected:
	static void on_power(bool on);
	static void init_scanner();
public:
	static void TurnOn();
	static void TurnOff() {}
	static void Update(int input_mask, int mode_index);
	static void UpdateInputs(int mask);
	static void UpdateRelays(int mask);
	static void ProcessAlarm(LPCHAR content);

public:
	static ClientID CLIENT_ID;
	static void SetClientId();
	static void OnMilis();
	static void OnSecond();

	static void ArmON();
	static void ArmOFF();
	static void Time();
	static void PLAN();
	static void ArmInputAction();
	static void InputOutputAction();
	static void SetSmsNumber();
	static void SetCallNumber();
};