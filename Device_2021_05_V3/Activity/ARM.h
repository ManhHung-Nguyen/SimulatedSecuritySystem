#pragma once
#include "Menu.h"
#include "Plan.h"
#include "Act.h"

class BaseARM : public Menu {
public:
	class Input : public Act { };
	class Zone : public Act { };
public:
	BaseARM() {
		Prepend(new Plan(), "PLAN");
	}
public:
	virtual Input* GetInputSetting() { return 0; }
	virtual Zone* GetZoneSetting() { return 0; }
	virtual int GetInputMask() { return 0; }
};

class Disarm : public BaseARM {
};

class Arm : public BaseARM {
public:
	Arm() {
		Append(new Zone(), "ZONE");
		Append(new Input(), "INPUT");
	}
public:
	Input* GetInputSetting() override { return ((Input*)Child->Sibling->Sibling); }
	Zone* GetZoneSetting() override { return ((Zone*)Child->Sibling); }

	int GetInputMask() override { return GetInputSetting()->GetValueMask(); }
};