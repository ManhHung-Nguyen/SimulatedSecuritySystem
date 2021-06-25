#pragma once
#include "Mode.h"
#include "../System/Builder.h"

class Alarm : public Mode {
public:
	PMODE SMS;
	PMODE CALL;
	PMODE OUTPUTS;
	Builder BUILDER;
public:
	Alarm();

	bool CheckInput(int value);
	bool CheckZone(int value);
public:
	void Activate() override;
	void ProcessKey(int code) override;
	LPCHAR GetContent();
};

