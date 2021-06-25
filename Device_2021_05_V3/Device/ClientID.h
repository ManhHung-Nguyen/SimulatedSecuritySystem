#pragma once
#include "../System/Builder.h"

class ClientID : public Builder {
public:
	ClientID();
	bool IsEmpty();
	void GetExisting();
	void SetValue(LPCHAR id);
public:
	LPCHAR GetTopic();
};

