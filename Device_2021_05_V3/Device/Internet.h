#pragma once
#include "Startup.h"
class Internet : public Startup
{
protected:
	void on_count_down() override;
	void begin() override {
		main_title = "INTERNET";
		duration = 5;
	}

	void on_reveived(LPCHAR content);
	void start_listener();
	bool is_connected();
public:
	void Disconnect() {}
	void Connect();
	void Send(LPCHAR content);
	void Request(LPCHAR url, LPCHAR value = 0);
};
